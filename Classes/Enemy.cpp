#include "Enemy.h"  
#include "GameResource.h"

Enemy::Enemy(void)
{
	m_sprite = NULL;//m_sprite是CCSprite指针，用来绑定敌机  
	m_life = 0;//生命值  
}


Enemy::~Enemy(void)
{
}

Enemy* Enemy::create()
{
	Enemy* pRet = new Enemy;
	pRet->autorelease();
	return pRet;
}


void Enemy::bindSprite(Sprite* sprite, int life, objecy_type ty)//绑定敌机，并传入生命值  
{
	m_sprite = sprite;
	m_life = life;

	Size sz = m_sprite->getContentSize();
	auto body = PhysicsBody::createCircle(sz.height/2);
	m_sprite->setPhysicsBody(body);
	m_sprite->setTag(ty);
	body->setDynamic(true);
	body->setCategoryBitmask(1);    // 0001
	body->setCollisionBitmask(1);   // 0001
	body->setContactTestBitmask(1); // 0001
	m_sprite->setUserData(this);

	this->addChild(m_sprite);
}


CCSprite* Enemy::getSprite()
{
	return m_sprite;
}


int Enemy::getLife()//获取生命  
{
	return m_life;
}


void Enemy::loseLife()//生命值-1  
{
	m_life--;
}


CCRect Enemy::getBoundingBox()//获取敌机大小  
{
	Rect rect = m_sprite->boundingBox();
	Point pos = this->convertToWorldSpace(rect.origin);
	Rect enemyRect(pos.x, pos.y, rect.size.width, rect.size.height);
	return enemyRect;
}