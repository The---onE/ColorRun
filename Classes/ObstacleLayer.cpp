#include "ObstacleLayer.h"

bool Obstacle::checkColor(int c)
{
	if (Ri(color))
	{
		return false;
	}
	if (c != color)
	{
		if (R(c)!=color && G(c)!=color && B(c)!=color)
		{
			return false;
		}
	}
	return true;
}

bool ObstacleLayer::init()
{
	Layer::init();
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	blockArray = std::make_shared<Vector<Obstacle*>>();
	speed = 0;

	scheduleUpdate();
	return true;
}

float ObstacleLayer::getSpeed()
{
	return speed;
}

void ObstacleLayer::setSpeed(float speed)
{
	this->speed = speed;
}

bool ObstacleLayer::checkCollision(Sprite* s, float speed, int color)
{
	bool flag = false;
	for (int i=blockArray->size()-1; i>=0; --i)
	{
		Obstacle* block = (Obstacle*)blockArray->at(i);
		if (!block->checkColor(color))
		{
			Rect blockRect = block->wall->getBoundingBox();
			float minY = s->getBoundingBox().getMinY();
			float minX = s->getBoundingBox().getMinX();
			float maxX = s->getBoundingBox().getMaxX();
			if (minX<=blockRect.getMaxX() && maxX>=blockRect.getMinX())
			{
				if (minY<=blockRect.getMaxY())
				{
					if (minY>=blockRect.getMaxY()+speed)
					{
						s->setPositionY(blockRect.getMaxY());
						flag = true;
					}
					else if (minY<blockRect.getMaxY() && minY<blockRect.getMaxY()+speed && minX<blockRect.getMinX())
					{
						s->setPositionX(blockRect.getMinX());
					}
				}
			}
		}
	}
	return flag;
}

void ObstacleLayer::update(float dt)
{
	for (int i=blockArray->size()-1; i>=0; --i)
	{
		Obstacle* block = (Obstacle*)blockArray->at(i);
		Sprite* wall = block->wall;
		float x = wall->getPositionX();
		if (x < -wall->getBoundingBox().size.width)
		{
			blockArray->eraseObject(block);
			this->removeChild(wall);
		}
		else
		{
			wall->setPositionX(x - speed);
		}
	}
}