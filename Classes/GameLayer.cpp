#include "GameLayer.h"
#include "GameResource.h"
#include "PlaneLayer.h"
#include "BulletLayer.h"

USING_NS_CC;

Sprite* GameLayer::background1 = NULL;
Sprite* GameLayer::background2 = NULL;
//背景滚动
void GameLayer::backgroundMove(float dt)
{
    background1->setPositionY(background1->getPositionY()-2);
    background2->setPositionY(background1->getPositionY()+background1->getContentSize().height-2);
    if (background2->getPositionY()==0)//要注意因为背景图高度是842，所以每次减去2最后可以到达0，假如背景高度是841，那么这个条件永远达不到，滚动失败
    {
        background1->setPositionY(0);
    }
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
	bool bRet=false;
    do
    {
        CC_BREAK_IF(!Layer::init());
		this->setTouchEnabled(true); 
 
        //png加入全局cache中
		SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(ResourceGame::back_ground_list);
         
        //加载background1，background1和background2是Sprite*型成员变量
		//background1=Sprite::createWithSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
		background1=Sprite::create(ResourceGame::back_ground_path);
        background1->setAnchorPoint(ccp(0,0));
        background1->setPosition(ccp(0,0));
        this->addChild(background1);
 
        //加载background2
        //background2=Sprite::createWithSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
        background2 = Sprite::create(ResourceGame::back_ground_path);
		background2->setAnchorPoint(ccp(0,0));
        background2->setPosition(ccp(0,background2->getContentSize().height-2));//这里减2的目的是为了防止图片交界的黑线
 
        this->addChild(background2);

		this->planeLayer=PlaneLayer::create();
        this->addChild(planeLayer);

		this->bulletLayer=BulletLayer::create();
		this->addChild(bulletLayer);
 
        //执行任务计划，实现背景滚动
        this->schedule(schedule_selector(GameLayer::backgroundMove),0.01f);
 
        bRet=true;
    } while (0);
    return bRet;
}


void GameLayer::menuCloseCallback(Object* pSender)
{
#if (_TARGET_PLATFORM == _PLATFORM_WINRT) || (_TARGET_PLATFORM == _PLATFORM_WP8)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    Director::sharedDirector()->end();
#if (_TARGET_PLATFORM == _PLATFORM_IOS)
    exit(0);
#endif
#endif
}

 void GameLayer::onEnter() 
 {
   	Layer::onEnter();
	auto listener =  EventListenerTouchOneByOne::create();//创建一个触摸监听
    listener->setSwallowTouches(true);//设置是否想下传递触摸

    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::OnContactBegin, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameLayer::OnTouchMoved, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener,10);
 }

bool GameLayer::OnContactBegin(Touch* touch, Event* event)  
{  
    return true;//表示当前层接收触摸事件处理  
}  
void GameLayer::OnTouchMoved(Touch* touch, Event* event)  
{  
	  if (this->planeLayer->isAlive)
	  {
		  Point beginPoint=touch->getLocationInView(); 
		  beginPoint=Director::sharedDirector()->convertToGL(beginPoint); 
		  //juggle the area of drag 
		  Rect planeRect=this->planeLayer->getChildByTag(ResourceGame::AIRPLANE)->boundingBox();
		  planeRect.origin.x-=15;
		  planeRect.origin.y-=15;
		  planeRect.size.width+=30;
		  planeRect.size.height+=30;
		  if(planeRect.containsPoint(this->getParent()->convertTouchToNodeSpace(touch))) 
		  { 
			  Point endPoint=touch->getPreviousLocationInView(); 
			  endPoint=Director::sharedDirector()->convertToGL(endPoint); 

			  Point offSet =ccpSub(beginPoint,endPoint);
			  Point toPoint=ccpAdd(this->planeLayer->getChildByTag(ResourceGame::AIRPLANE)->getPosition(),offSet); 
			  this->planeLayer->MoveTo(toPoint); 
		  } 
	  } 
}  
