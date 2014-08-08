#include "cocos2d.h"
#include "BulletLayer.h"
#include "GameResource.h"
#include "PlaneLayer.h"

USING_NS_CC;

BulletLayer::BulletLayer(void)
{
	//bulletSpriteFrame=NULL;
	bulletBatchNode=NULL;

	m_pAllBullet=Array::create();
	m_pAllBullet->retain();
}

BulletLayer::~BulletLayer(void)
{
	m_pAllBullet->release();
	m_pAllBullet=NULL;
}

bool BulletLayer::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!Layer::init());

		//bulletSpriteFrame=SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bullet1.png");

		Texture2D *texture = TextureCache::sharedTextureCache()->textureForKey("ui/shoot.png");
		bulletBatchNode = SpriteBatchNode::createWithTexture(texture);
		this->addChild(bulletBatchNode);
		StartShoot(0.1);
		bRet=true;
	} while (0);
	return bRet;
}

void BulletLayer::StartShoot(float delay)
{
	this->schedule(schedule_selector(BulletLayer::AddBullet),0.20f,kRepeatForever,delay);
}

void BulletLayer::StopShoot()
{
	this->unschedule(schedule_selector(BulletLayer::AddBullet));
}

void BulletLayer::AddBullet(float dt)
{
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/bullet.mp3");
	Sprite* bullet=Sprite::createWithSpriteFrameName("bullet1.png");
	bulletBatchNode->addChild(bullet);
	//this->addChild(bullet);
	this->m_pAllBullet->addObject(bullet);

	Point planePosition=PlaneLayer::sharedPlane->getChildByTag(ResourceGame::AIRPLANE)->getPosition();
	Point bulletPosition=ccp(planePosition.x,planePosition.y+PlaneLayer::sharedPlane->getChildByTag(ResourceGame::AIRPLANE)->getContentSize().height/2);
	bullet->setPosition(bulletPosition);
    
	float length=Director::sharedDirector()->getWinSize().height+bullet->getContentSize().height/2-bulletPosition.y;
	float velocity=320/1;//320pixel/sec
	float realMoveDuration=length/velocity;

	FiniteTimeAction* actionMove=MoveTo::create(realMoveDuration,ccp(bulletPosition.x,Director::sharedDirector()->getWinSize().height+bullet->getContentSize().height/2));
	FiniteTimeAction* actionDone=CallFuncN::create(this,callfuncN_selector(BulletLayer::bulletMoveFinished));

	Sequence* sequence=Sequence::create(actionMove,actionDone,NULL);
	bullet->runAction(sequence);
}

void BulletLayer::bulletMoveFinished(Node* pSender)
{
	Sprite* bullet=(Sprite*)pSender;
	this->bulletBatchNode->removeChild(bullet,true);
	this->m_pAllBullet->removeObject(bullet);
}

void BulletLayer::RemoveBullet(Sprite* bullet)
{
	if (bullet!=NULL)
	{
		this->bulletBatchNode->removeChild(bullet,true);
		this->m_pAllBullet->removeObject(bullet);
	}
}