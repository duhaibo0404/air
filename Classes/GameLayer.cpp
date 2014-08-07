#include "GameLayer.h"
#include "GameResource.h"
#include "PlaneLayer.h"
#include "BulletLayer.h"

USING_NS_CC;

CCSprite* GameLayer::background1 = NULL;
CCSprite* GameLayer::background2 = NULL;
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
        CC_BREAK_IF(!CCLayer::init());
		this->setTouchEnabled(true); 
 
        //png加入全局cache中
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(ResourceGame::back_ground_list);
         
        //加载background1，background1和background2是CCSprite*型成员变量
		//background1=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
		background1=CCSprite::create(ResourceGame::back_ground_path);
        background1->setAnchorPoint(ccp(0,0));
        background1->setPosition(ccp(0,0));
        this->addChild(background1);
 
        //加载background2
        //background2=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
        background2 = CCSprite::create(ResourceGame::back_ground_path);
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


void GameLayer::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

//GameLayer.cpp  
bool GameLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)  
{  
    return true;//表示当前层接收触摸事件处理  
}  
  
void GameLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)  
{  
	if (this->planeLayer->isAlive)
	{
		CCPoint beginPoint=pTouch->getLocationInView(); 
		beginPoint=CCDirector::sharedDirector()->convertToGL(beginPoint); 
		//juggle the area of drag 
		CCRect planeRect=this->planeLayer->getChildByTag(ResourceGame::AIRPLANE)->boundingBox();
		planeRect.origin.x-=15;
		planeRect.origin.y-=15;
		planeRect.size.width+=30;
		planeRect.size.height+=30;
		if(planeRect.containsPoint(this->getParent()->convertTouchToNodeSpace(pTouch))) 
		{ 
			CCPoint endPoint=pTouch->getPreviousLocationInView(); 
			endPoint=CCDirector::sharedDirector()->convertToGL(endPoint); 

			CCPoint offSet =ccpSub(beginPoint,endPoint);
			CCPoint toPoint=ccpAdd(this->planeLayer->getChildByTag(ResourceGame::AIRPLANE)->getPosition(),offSet); 
			this->planeLayer->MoveTo(toPoint); 
		} 
	} 
}  

void GameLayer::registerWithTouchDispatcher()  
{  
    CCDirector *pDirector=CCDirector::sharedDirector();  
    pDirector->getTouchDispatcher()->addTargetedDelegate(this,0,true);  
} 

