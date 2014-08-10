#include "Enemy.h"  
#include "GameResource.h"

Enemy::Enemy(void)
{
	m_sprite = NULL;//m_sprite��CCSpriteָ�룬�����󶨵л�  
	m_life = 0;//����ֵ  
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


void Enemy::bindSprite(Sprite* sprite, int life, objecy_type ty)//�󶨵л�������������ֵ  
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


int Enemy::getLife()//��ȡ����  
{
	return m_life;
}


void Enemy::loseLife()//����ֵ-1  
{
	m_life--;
}


CCRect Enemy::getBoundingBox()//��ȡ�л���С  
{
	Rect rect = m_sprite->boundingBox();
	Point pos = this->convertToWorldSpace(rect.origin);
	Rect enemyRect(pos.x, pos.y, rect.size.width, rect.size.height);
	return enemyRect;
}