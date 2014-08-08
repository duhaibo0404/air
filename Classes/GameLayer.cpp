#include "GameLayer.h"
#include "GameResource.h"
#include "PlaneLayer.h"
#include "BulletLayer.h"

USING_NS_CC;

Sprite* GameLayer::background1 = NULL;
Sprite* GameLayer::background2 = NULL;
//��������
void GameLayer::backgroundMove(float dt)
{
    background1->setPositionY(background1->getPositionY()-2);
    background2->setPositionY(background1->getPositionY()+background1->getContentSize().height-2);
    if (background2->getPositionY()==0)//Ҫע����Ϊ����ͼ�߶���842������ÿ�μ�ȥ2�����Ե���0�����米���߶���841����ô���������Զ�ﲻ��������ʧ��
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
 
        //png����ȫ��cache��
		SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(ResourceGame::back_ground_list);
         
        //����background1��background1��background2��Sprite*�ͳ�Ա����
		//background1=Sprite::createWithSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
		background1=Sprite::create(ResourceGame::back_ground_path);
        background1->setAnchorPoint(ccp(0,0));
        background1->setPosition(ccp(0,0));
        this->addChild(background1);
 
        //����background2
        //background2=Sprite::createWithSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
        background2 = Sprite::create(ResourceGame::back_ground_path);
		background2->setAnchorPoint(ccp(0,0));
        background2->setPosition(ccp(0,background2->getContentSize().height-2));//�����2��Ŀ����Ϊ�˷�ֹͼƬ����ĺ���
 
        this->addChild(background2);

		this->planeLayer=PlaneLayer::create();
        this->addChild(planeLayer);

		this->bulletLayer=BulletLayer::create();
		this->addChild(bulletLayer);
 
        //ִ������ƻ���ʵ�ֱ�������
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
	auto listener =  EventListenerTouchOneByOne::create();//����һ����������
    listener->setSwallowTouches(true);//�����Ƿ����´��ݴ���

    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::OnContactBegin, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameLayer::OnTouchMoved, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener,10);
 }

bool GameLayer::OnContactBegin(Touch* touch, Event* event)  
{  
    return true;//��ʾ��ǰ����մ����¼�����  
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
