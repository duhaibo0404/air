#include "GameLayer.h"
#include "GameResource.h"
#include "PlaneLayer.h"
#include "BulletLayer.h"

USING_NS_CC;

CCSprite* GameLayer::background1 = NULL;
CCSprite* GameLayer::background2 = NULL;
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
        CC_BREAK_IF(!CCLayer::init());
		this->setTouchEnabled(true); 
 
        //png����ȫ��cache��
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(ResourceGame::back_ground_list);
         
        //����background1��background1��background2��CCSprite*�ͳ�Ա����
		//background1=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
		background1=CCSprite::create(ResourceGame::back_ground_path);
        background1->setAnchorPoint(ccp(0,0));
        background1->setPosition(ccp(0,0));
        this->addChild(background1);
 
        //����background2
        //background2=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
        background2 = CCSprite::create(ResourceGame::back_ground_path);
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
    return true;//��ʾ��ǰ����մ����¼�����  
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

