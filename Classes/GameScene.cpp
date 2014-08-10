#include "GameScene.h"
 
GameScene::GameScene(void)
{
    _gameLayer=NULL;
}

GameScene* GameScene::createWithPhysics()
{
	GameScene *ret = new GameScene();
	if (ret && ret->initWithPhysics())
	{
		ret->init();
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}
GameScene::~GameScene(void)
{
}
 
bool GameScene::init()
{
    bool bRet=false;
    do
    {
        //CC_BREAK_IF(!Scene::init());
        _gameLayer=GameLayer::create();//�������ȡGameLayerʵ��
        CC_BREAK_IF(!_gameLayer);
		//this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
        this->addChild(_gameLayer);//add _gameLayer��������
        bRet=true;
    } while (0);
 
    return bRet;
}