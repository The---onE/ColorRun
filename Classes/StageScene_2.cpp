#include "StageScene_2.h"

#define initialSpeed 0.006

bool StageScene_2::init()
{
	GameScene::init();
	srand(time(NULL));

	randomGroundMap();
	randomColorMap();

	speed = initialSpeed * DATUM;

	return true;
}

void StageScene_2::initGame()
{
	button->RGBRGBMode();

	setSpeed(speed);
}

void StageScene_2::Gameover()
{
	int high = readHigh("rgbrgb");
	if (score <= high)
	{
		sprintf(text, "GAME OVER\nSCORE:%d\nBEST:%d", score, high);
	}
	else
	{
		sprintf(text, "GAME OVER\nSCORE:%d\nBEST:!%d!", score, score);
		writeHigh("rgbrgb", score);
	}
	gameover = Label::createWithSystemFont(text, "Arial", DATUM/10, Size(visibleSize.width*0.6, visibleSize.height*0.6),TextHAlignment::CENTER,TextVAlignment::CENTER);
	this->addChild(gameover,10000);
	gameover->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
	gameover->setScale(0.5);
	this->schedule(schedule_selector(GameScene::GameoverSchedule), 0.01f, UINT_MAX-1, 0);

	winFlag = true;
	overFlag = false;
}

void StageScene_2::createRestart()
{
	Label* gameoverLable = Label::createWithSystemFont(text, "Arial", DATUM/10, Size(visibleSize.width*0.6, visibleSize.height*0.6),TextHAlignment::CENTER,TextVAlignment::CENTER);
	MenuItemLabel* re = MenuItemLabel::create(gameoverLable, CC_CALLBACK_0(StageScene_2::restart, this));
	Menu* menu = Menu::create(re,NULL);
	gameoverLable->setAnchorPoint(Point::ANCHOR_MIDDLE);
	gameoverLable->setPosition(Point(visibleSize.width*0.3, visibleSize.height*0.3));
	gameoverLable->setScale(gameover->getScale());
	this->addChild(menu, 10000);
	this->removeChild(gameover);
}

void StageScene_2::restart()
{
	StageScene_2* game = StageScene_2::create();
	game->setEffectFlag(effectFlag);
	Director::getInstance()->replaceScene(game);
}

const char* StageScene_2::getGroundMap(int m)
{
	m = m % 8;
	switch (m)
	{
	case 0:
		return g_0;
		break;
	case 1:
		return g_1;
		break;
	case 2:
		return g_2;
		break;
	case 3:
		return g_3;
		break;
	case 4:
		return g_4;
		break;
	case 5:
		return g_5;
		break;
	case 6:
		return g_6;
		break;
	case 7:
		return g_7;
		break;
	}
	return NULL;
}

const char* StageScene_2::getColorMap(int m)
{
	m = m % 3;
	switch (m)
	{
	case 0:
		return c_0;
		break;
	case 1:
		return c_1;
		break;
	case 2:
		return c_2;
		break;
	}
	return NULL;
}


const char StageScene_2::g_0[] = 
{
	OX2, 1,1,1,1, -1,-1,-1, OX5, 2,2,2, 3,3,3, 1,1,1,1, -1,-1,-1,-1,-1, 0, STOP
};
const char StageScene_2::g_1[] = 
{
	OX2, 1,1,1,1,1, -1,-1,-1, 1,1,1,1, -1,-1, 2,2, 3,3,3,3, -1,-1,-1,-1, OX5, 1,1, 2,2,2, 1,1,1, 3,3,3, -1,-1,-1, 0, STOP
};
const char StageScene_2::g_2[] =
{
	OX2, 1,1, 2, 3,3,3, 1,1, -1,-1, 2,2, 3,3, OX2, -1,-1, 0, 1, 2,2, 3,3,3, 1,1, 2,2, -1,-1, 0,0, -1,-1, 0, STOP
};
const char StageScene_2::g_3[] =
{
	OX2, 1, 2,2, 3, -1,-1, 1, 1,1, 0,0 ,1,1,1, 3,3, 2,2, 1,1,1, -1,-1, 1,1, 2,2,2, 0, STOP
};
const char StageScene_2::g_4[] =
{
	OX2, 2,2, 3,3,3, 4, 1,1,1, 2,2,2,2, 3,3,3, -1,-1,-1, OX5, -1,-1, 0, STOP
};
const char StageScene_2::g_5[] =
{
	OX2, 1, 2,2, 3, 2, 1,1, 0, -1,-1, OX2, 1, 2,2, 1,1, 0, STOP
};
const char StageScene_2::g_6[] =
{
	OX2, 2, 2, 3,3, -1,-1, 1, 2,2, -1,-1, 1, 2,2,2, 3, 1,1, 2,2, -1,-1,-1, 0,0, STOP
};
const char StageScene_2::g_7[] =
{
	OX2, 1, 2,2,2, 3, 1,1,1, 2, 1, -1, 1, 2, -1, 3,3,3, 2, 1,1,1, 2,2, 0, STOP
};

const char StageScene_2::c_0[] = 
{
	_1X10, RED, _1X14, CYAN, _1X14, PINK, _1X12, YELLOW, _1X8, BLUE, _1X10, PINK, _1X8, RED, _1X5,-1, GREEN, _1X8, CYAN, _1X12, PINK, _1X5, BLUE, _1X10, CYAN, STOP
};
const char StageScene_2::c_1[] = 
{
	_1X5,-1, BLUE, _1X12, YELLOW, _1X10, CYAN, _1X12, YELLOW, _1X8, BLUE, _1X12, YELLOW, _1X8, BLUE, _1X5,-1, GREEN, _1X8, PINK, _1X12, CYAN, _1X5, BLUE, _1X10, YELLOW, STOP
};
const char StageScene_2::c_2[] = 
{
	_1X8, GREEN, _1X14, YELLOW, _1X10, PINK, _1X14, CYAN, _1X8, RED, _1X10, CYAN, _1X5,-1, RED, _1X5,-1, BLUE, _1X12, YELLOW, _1X10, PINK, _1X8, BLUE, _1X10, CYAN, STOP
};