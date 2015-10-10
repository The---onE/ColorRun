#pragma once

#include "cocos2d.h"
#include "Global.h"
#include "BackGroundLayer.h"
#include "ControlLayer.h"
#include "GroundLayer.h"
#include "PlayerLayer.h"
#include "ColorWallLayer.h"
#include "ButtonLayer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;


class GameScene : public Scene
{
public:
	bool init();
	void setEffectFlag(bool effectFlag);
	void GameoverSchedule(float dt);

protected:
	virtual void initGame() = 0;
	virtual void Gameover() = 0;
	virtual void createRestart() = 0;
	void showScore(int delta);
	void setSpeed(float speed);
	void checkRestart();
	void checkChangeHand();

	void writeHigh(std::string mode, int score);
	int readHigh(std::string mode);

	char getGroundMapNode();
	char getColorMapNode();
	void randomGroundMap();
	void randomColorMap();
	const char* groundP;
	const char* colorP;
	virtual const char* getGroundMap(int m) = 0;
	virtual const char* getColorMap(int m) = 0;

	void update(float dt);

	Size visibleSize;
	Point origin;
	bool winFlag;
	bool effectFlag;
	bool playingFlag;
	bool overFlag;
	int groundProgress;
	int wallProgress;
	int wallCycle;
	int score;
	int giveHealthProgress;
	float wallTime;
	float speed;
	Label* gameover;
	Label* scoreLable;
	char text[64];

	BackGroundLayer* bg;
	ControlLayer* control;
	GroundLayer* ground;
	PlayerLayer* player;
	ColorWallLayer* color;
	ButtonLayer* button;
};

#define OX2 0,0
#define OX5 0,0,0,0,0
#define OX8 OX5,0,0,0
#define OX10 OX5,OX5
#define OX12 OX10,OX2
#define OX14 OX10,OX2,0,0
#define OX16 OX8,OX8
#define OX18 OX10,OX8
#define OX20 OX10,OX10

#define _1X2 -1,-1
#define _1X5 -1,-1,-1,-1,-1
#define _1X8 _1X5,-1,-1,-1
#define _1X10 _1X5,_1X5
#define _1X12 _1X10,_1X2
#define _1X14 _1X10,_1X2,-1,-1
#define _1X16 _1X8,_1X8
#define _1X18 _1X10,_1X8
#define _1X20 _1X10,_1X10

#define STOP -99