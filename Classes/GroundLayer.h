#pragma once

#include "cocos2d.h"
#include "ObstacleLayer.h"
#include "Global.h"
USING_NS_CC;

class GroundLayer : public ObstacleLayer
{
public:
	CREATE_FUNC(GroundLayer);
	bool init();
	bool isBlockOver();
	bool createBlock(int level, int color=RIGID);

protected:
	void createBlock(std::string filename, int level, int color);
	void createBlock(std::string filename, int level, int x, int color);

	Sprite* lastBlock;
};

