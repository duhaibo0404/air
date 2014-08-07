#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "PlaneLayer.h"
#include "BulletLayer.h"

USING_NS_CC;

class GameLayer : public CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    void backgroundMove(float dt);
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameLayer);
	//virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);//触摸开始调用  
	//virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);//触摸移动调用	
	//virtual void registerWithTouchDispatcher();

public:
	static cocos2d::CCSprite* background1;
	static cocos2d::CCSprite* background2;

	PlaneLayer* planeLayer;
	BulletLayer* bulletLayer;
};

#endif // __HELLOWORLD_SCENE_H__
