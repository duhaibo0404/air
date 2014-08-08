#include "cocos2d.h"
#include "PlaneLayer.h"
#include "GameResource.h"

PlaneLayer* PlaneLayer::sharedPlane=NULL;//静态变量要在cpp外初始化
PlaneLayer* PlaneLayer::create() 
{ 
    PlaneLayer *pRet = new PlaneLayer();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        sharedPlane=pRet;//获得静态指针sharedPlane的值
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
 
        //创建飞机精灵前要先调用SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shoot.plist");加载全局资源
        //我把这个调用plist放到welcome.cpp中了。不然plane会空指针。 
		SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(ResourceGame::shoot_list);
        Sprite* plane=Sprite::create(ResourceGame::hero_path);
        plane->setPosition(ccp(winSize.width/2,plane->getContentSize().height/2));//飞机放置在底部中央
		this->addChild(plane,0,ResourceGame::AIRPLANE);//添加精灵，AIRPLANE是tag
 
        Blink *blink=Blink::create(1,3);//闪烁动画
 
        Animation* animation=Animation::create();
        animation->setDelayPerUnit(0.1f);
		SpriteFrame* sf_1 = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(ResourceGame::hero_1_key);
		SpriteFrame* sf_2 = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(ResourceGame::hero_2_key);
        animation->addSpriteFrame(sf_1);
        animation->addSpriteFrame(sf_2);
        Animate* animate=Animate::create(animation);//帧动画
         
        plane->runAction(blink);//执行闪烁动画
        plane->runAction(RepeatForever::create(animate));// 执行帧动画
 
        bRet=true;
    } while (0);
     
    return bRet;
}

void PlaneLayer::MoveTo(Point location)
{
	//飞机及游戏状态判断  
    if(isAlive && !Director::sharedDirector()->isPaused())  
    {  
        //进行边界判断,不可超出屏幕  
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