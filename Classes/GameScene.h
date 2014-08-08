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
    static GameScene* createWithPhysics();//ʵ��create����
 
    virtual bool init();
 
    GameLayer* _gameLayer;//��GameLayer��¶��GameScene
 
};