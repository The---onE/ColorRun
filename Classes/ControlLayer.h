#pragma once

#include "cocos2d.h"
#include "Global.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;

class ControlLayer : public Layer
{
public:
	CREATE_FUNC(ControlLayer);
	bool isRestart();
	bool isChangeHand();

protected:
	bool init();
	void onEnter();
	void createCloseButton(std::string filenameN, std::string filenameS);
	void createPauseButton(std::string filenameN, std::string filenameS);
	void createRestartButton(std::string filenameN, std::string filenameS);
	void createChangeHandButton(std::string filenameN, std::string filenameS);
	void quitGame();
	void pauseGame();
	void restartGame();
	void changeHand();

	bool pauseFlag;
	bool restartFlag;
	bool changeHandFlag;
	Size visibleSize;
	Point origin;
};

