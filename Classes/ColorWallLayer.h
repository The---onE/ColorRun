#pragma once

#include "cocos2d.h"
#include "ObstacleLayer.h"
#include "Global.h"
USING_NS_CC;

class ColorWallLayer : public ObstacleLayer
{
public:
	CREATE_FUNC(ColorWallLayer);
	bool init();
	void createWall(int color);

private:
	Obstacle* createWall(std::string filename);
};

