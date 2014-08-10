#ifndef __BULLETLAYER_H__
#define __BULLETLAYER_H__

#include "cocos2d.h"

USING_NS_CC;

#pragma warning(disable:4996)
class BulletLayer :public Layer
{
public:

	BulletLayer(void);

	~BulletLayer(void);

	CREATE_FUNC(BulletLayer);

	virtual bool init();

	void AddBullet(float dt);

	void bulletMoveFinished(Node* pSender);

	void RemoveBullet(Sprite* bullet);

	void StartShoot(float delay=0.0f);

	void StopShoot();

public:

	Array* m_pAllBullet;

	//CCSpriteFrame* bulletSpriteFrame;

	SpriteBatchNode* bulletBatchNode;

};

#endif