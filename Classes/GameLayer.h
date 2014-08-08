#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "PlaneLayer.h"
#include "BulletLayer.h"

USING_NS_CC;

class GameLayer : public Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    void backgroundMove(float dt);
    // a selector callback
    void menuCloseCallback(Ref* pSender);
    virtual void onEnter() override;
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameLayer); 
	void OnTouchMoved(Touch* touch, Event* event);//´¥ÃþÒÆ¶¯µ÷ÓÃ	
    bool OnContactBegin(Touch* touch, Event* event); 

public:
	static cocos2d::Sprite* background1;
	static cocos2d::Sprite* background2;

	PlaneLayer* planeLayer;
	BulletLayer* bulletLayer;
};

#endif // __HELLOWORLD_SCENE_H__
