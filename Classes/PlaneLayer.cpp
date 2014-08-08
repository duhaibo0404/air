#include "cocos2d.h"
#include "PlaneLayer.h"
#include "GameResource.h"

PlaneLayer* PlaneLayer::sharedPlane=NULL;//��̬����Ҫ��cpp���ʼ��
PlaneLayer* PlaneLayer::create() 
{ 
    PlaneLayer *pRet = new PlaneLayer();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        sharedPlane=pRet;//��þ�ָ̬��sharedPlane��ֵ
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool PlaneLayer::init()
{
    bool bRet=false;
    do
    {
        CC_BREAK_IF(!Layer::init());
         
        Size winSize=Director::sharedDirector()->getWinSize();
 
        //�����ɻ�����ǰҪ�ȵ���SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shoot.plist");����ȫ����Դ
        //�Ұ��������plist�ŵ�welcome.cpp���ˡ���Ȼplane���ָ�롣 
		SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(ResourceGame::shoot_list);
        Sprite* plane=Sprite::create(ResourceGame::hero_path);
        plane->setPosition(ccp(winSize.width/2,plane->getContentSize().height/2));//�ɻ������ڵײ�����
		this->addChild(plane,0,ResourceGame::AIRPLANE);//��Ӿ��飬AIRPLANE��tag
 
        Blink *blink=Blink::create(1,3);//��˸����
 
        Animation* animation=Animation::create();
        animation->setDelayPerUnit(0.1f);
		SpriteFrame* sf_1 = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(ResourceGame::hero_1_key);
		SpriteFrame* sf_2 = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(ResourceGame::hero_2_key);
        animation->addSpriteFrame(sf_1);
        animation->addSpriteFrame(sf_2);
        Animate* animate=Animate::create(animation);//֡����
         
        plane->runAction(blink);//ִ����˸����
        plane->runAction(RepeatForever::create(animate));// ִ��֡����
 
        bRet=true;
    } while (0);
     
    return bRet;
}

void PlaneLayer::MoveTo(Point location)
{
	//�ɻ�����Ϸ״̬�ж�  
    if(isAlive && !Director::sharedDirector()->isPaused())  
    {  
        //���б߽��ж�,���ɳ�����Ļ  
        Point actualPoint;  
        Size winSize=Director::sharedDirector()->getWinSize();  
        Size planeSize=this->getChildByTag(ResourceGame::AIRPLANE)->getContentSize();  
        if (location.x<planeSize.width/2)  
        {  
            location.x=planeSize.width/2;  
        }  
        if (location.x>winSize.width-planeSize.width/2)  
        {  
            location.x=winSize.width-planeSize.width/2;  
        }  
        if (location.y<planeSize.height/2)  
        {  
            location.y=planeSize.height/2;  
        }  
        if (location.y>winSize.height-planeSize.height/2)  
        {  
            location.y=winSize.height-planeSize.height/2;  
        }  
        this->getChildByTag(ResourceGame::AIRPLANE)->setPosition(location);  
    }  
}