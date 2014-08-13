//GameScene.h
#pragma once
 
#include "cocos2d.h"
#include "GameLayer.h"
 
USING_NS_CC;
 
class GameScene :public Scene
{
public:
     
    GameScene(void);
 
    ~GameScene(void);
 
	static GameScene* createWithPhysics();
 
    virtual bool init() override;
 
    GameLayer* _gameLayer;

    void authMenuItemClick(Ref* pSender);   
    void cancelAuthMenuItemClick(Ref* pSender);    
    void hasAuthMenuItemClick(Ref* pSender);    
    void getUserInfoMenuItemClick(Ref* pSender);
    void shareMenuItemClick(Ref* pSender);
    void menuCloseCallback(Ref* pSender);
};