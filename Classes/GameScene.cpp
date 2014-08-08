#include "GameScene.h"
 
GameScene::GameScene(void)
{
    _gameLayer=NULL;
}
GameScene* GameScene::createWithPhysics()
{
    GameScene *pRet = GameScene::createWithPhysics();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
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
        CC_BREAK_IF(!CCScene::init());
        _gameLayer=GameLayer::create();//�������ȡGameLayerʵ��
        CC_BREAK_IF(!_gameLayer);
        this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
        this->addChild(_gameLayer);//add _gameLayer��������
        bRet=true;
    } while (0);
 
    return bRet;
}