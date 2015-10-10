#pragma once

#include "cocos2d.h"
#include "Global.h"
#include "GameScene.h"
USING_NS_CC;

class StageScene_1 : public GameScene
{
public:
	CREATE_FUNC(StageScene_1);
protected:
	bool init();
	void initGame();
	void Gameover();
	void createRestart();
	void restart();
	
	const char* getGroundMap(int m);
	const char* getColorMap(int m);
	const static char g_0[];
	const static char g_1[];
	const static char g_2[];
	const static char g_3[];
	const static char g_4[];
	const static char g_5[];
	const static char g_6[];
	const static char g_7[];
	const static char c_0[];
	const static char c_1[];
	const static char c_2[];
};

