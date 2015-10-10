#include "GroundLayer.h"

bool GroundLayer::init()
{
	ObstacleLayer::init();

	float x = 0;
	do 
	{
		createBlock("sprites/block.png", 0, x, RIGID);
		x += lastBlock->getBoundingBox().size.width;
	} while (x < visibleSize.width);

	return true;
}

void GroundLayer::createBlock(std::string filename, int level, int color)
{
	createBlock(filename, level, lastBlock->getPositionX() + lastBlock->getBoundingBox().size.width, color);
}

void GroundLayer::createBlock(std::string filename, int level, int x, int color)
{
	Sprite* block;
	block = Sprite::create(filename);
	SETSIZE(block, 1);
	block->setAnchorPoint(Point(0, 1));
	if (level < 0)
		block->setPosition(Point(origin.x + x, origin.y -DATUM * 0.3));
	else
		block->setPosition(Point(origin.x + x, origin.y + DATUM * (0.3+level*0.1)));
	addChild(block);
	Obstacle* b = Obstacle::create();
	b->wall = block;
	b->color = color;

	blockArray->pushBack(b);
	lastBlock = block;
}

bool GroundLayer::createBlock(int level, int color)
{
	createBlock("sprites/block.png", level, color);
	return true;
}

bool GroundLayer::isBlockOver()
{
	return lastBlock->getPositionX() + lastBlock->getBoundingBox().size.width <= visibleSize.width;
}
