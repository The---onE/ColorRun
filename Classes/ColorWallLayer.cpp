#include "ColorWallLayer.h"

bool ColorWallLayer::init()
{
	ObstacleLayer::init();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites/color.plist", "sprites/color.png");

	return true;
}

Obstacle* ColorWallLayer::createWall(std::string filename)
{
	Sprite* wall;
	wall = Sprite::createWithSpriteFrameName(filename);
	SETSIZE(wall, 1);
	wall->setAnchorPoint(Point(0, 0));
	wall->setPosition(Point(origin.x + visibleSize.width, origin.y));
	addChild(wall);
	Obstacle* cw = Obstacle::create();
	cw->wall = wall;
	blockArray->pushBack(cw);

	return cw;
}

void ColorWallLayer::createWall(int color)
{
	switch (color)
	{
	case -1:
		break;
	case RED:
		createWall("red.png")->color = color;
		break;

	case GREEN:
		createWall("green.png")->color = color;
		break;

	case BLUE:
		createWall("blue.png")->color = color;
		break;

	case YELLOW:
		createWall("yellow.png")->color = color;
		break;;

	case PINK:
		createWall("pink.png")->color = color;
		break;

	case CYAN:
		createWall("cyan.png")->color = color;
		break;
	}
}
