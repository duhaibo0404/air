//GameScene.h
#pragma once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace cocos2d::ui;

class StartScene :public Scene
{
public:

	StartScene(void);

	~StartScene(void);

	CREATE_FUNC(StartScene);

	void StartGame(Ref* sender, TouchEventType type);

	virtual bool init();
};