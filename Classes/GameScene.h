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
};