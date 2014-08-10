#include "StartScene.h"
#include "cocostudio\CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"

using namespace cocos2d::ui;
using namespace cocostudio;

StartScene::StartScene(void)
{
}

StartScene::~StartScene(void)
{
}

bool StartScene::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Scene::init());

		auto UI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("airplan_1.ExportJson");

		Button* Button_start = (Button*)Helper::seekWidgetByName(UI, "Button_start");
		Button_start->addTouchEventListener(this, toucheventselector(StartScene::StartGame));

		this->addChild(UI);
		bRet = true;
	} while (0);

	return bRet;
}

void StartScene::StartGame(Ref* sender, TouchEventType type)
{
	Director* pDirector = Director::getInstance();
	Scene *pScene = GameScene::createWithPhysics();

	float t = 1.2f;
	TransitionScene * reScene = TransitionJumpZoom::create(t, pScene);

	pDirector->replaceScene(pScene);
}