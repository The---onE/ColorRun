#pragma once

#include "cocos2d.h"
#include "Global.h"
USING_NS_CC;

class Obstacle : public Node
{
public:
	static Obstacle* create()
	{
		Obstacle *pRet = new Obstacle();
		if (pRet)
		{
			pRet->autorelease();
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = NULL;
			return NULL;
		}
	}
	bool checkColor(int c);
	Sprite* wall;
	int color;
};

class ObstacleLayer : public Layer
{
public:
	bool init();
	float getSpeed();
	void setSpeed(float speed);
	bool checkCollision(Sprite* s, float speed, int color);
	void update(float dt);

	std::shared_ptr<Vector<Obstacle*>> blockArray;
	float speed;
	Size visibleSize;
	Point origin;
};
