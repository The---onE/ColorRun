#pragma once

#include "cocos2d.h"
#include "Global.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

class MainScene : public Scene
{
public:
	CREATE_FUNC(MainScene);
	bool init();

protected:
	void RGBMode();
	void RGBRGBMode();
	void WhiteMode();
	void PlayStopBGM();
	void OpenCloseEffect();
	void QuitGame();
	void createBackGround(std::string filename);

	Size visibleSize;
	Point origin;
	bool effectFlag;
};
