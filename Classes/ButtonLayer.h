#pragma once

#include "cocos2d.h"
#include "XMX_Button.h"
#include "Global.h"
USING_NS_CC;

class ButtonLayer : public XMX_Button
{
public:
	CREATE_FUNC(ButtonLayer);
	bool init();
	void onEnter();
	void RGBMode();
	void RGBRGBMode();
	void WhiteMode();
	int getState();
	void changeHand();

private:
	void setUpRightButton(float pX, int color);
	void setDownRightButton(float pX, int color);
	void setUpLeftButton(float pX, int color);
	void setDownLeftButton(float pX, int color);
	void changeSprite(Sprite* s, int color);
	void checkPress();
	void update(float dt);
	KEYBOARD_FUNCTION;

	int rState;
	int lState;
	float left;
	float right;
	float up;
	float down;
	Sprite* rS;
	Sprite* lS;
	bool leftButtonFlag;
	bool rightButtonFlag;
	bool rightHandFlag;

	Size visibleSize;
	Point origin;
};

