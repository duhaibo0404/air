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
 
    CREATE_FUNC(GameScene);
    static GameScene* createWithPhysics();//实现create函数
 
    virtual bool init();
 
    GameLayer* _gameLayer;//把GameLayer暴露给GameScene
 
};