#pragma once
#include "cocos2d.h"
#include "GameResource.h"

USING_NS_CC;

class Enemy : public Node
{
public:
	Enemy(void);
	~Enemy(void);
	static Enemy* create();
	void bindSprite(Sprite* sprite, int life, objecy_type ty);
	Sprite* getSprite();
	int getLife();
	void loseLife();
	Rect getBoundingBox();

private:
	Sprite* m_sprite;
	int m_life;
};