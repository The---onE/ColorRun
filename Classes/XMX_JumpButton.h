#pragma once

#include "cocos2d.h"
USING_NS_CC;

class XMX_JumpButton : public virtual Layer
{
public:
	XMX_JumpButton();
	void XMX_JumpButton_setJumpButton(Sprite* jumpButton, float size, int x, int y);
	void XMX_JumpButton_setJumpButton(Rect jumpRect);
	void XMX_JumpButton_setJumpSpeed(float jumpSpeed);
	void XMX_JumpButton_setVibratorTime(int time);
	void XMX_JumpButton_allowJump();
	void XMX_JumpButton_notAllowJump();
	void XMX_JumpButton_forbidden();
	void XMX_JumpButton_setGravity(float gravity);
	void XMX_JumpButton_setGravity(float lowGravity, float highGravity);
	float XMX_JumpButton_getSpeedY();
	void XMX_JumpButton_gravityEffect();
	void XMX_JumpButton_resume();
	void XMX_JumpButton_jumpBegan();
	void XMX_JumpButton_jumpEnded();
	void XMX_JumpButton_onTouchBegan(Touch *touch, Event *unused_event);
	void XMX_JumpButton_onTouchMoved(Touch *touch, Event *unused_event);
	void XMX_JumpButton_onTouchEnded(Touch *touch, Event *unused_event);

private:
	bool XMX_JumpButton_checkControler();
	void XMX_JumpButton_setHighGravity();
	void XMX_JumpButton_setLowGravity();
	Size visibleSize;
	Point origin;
	int XMX_JumpButton_datum;
	int XMX_JumpButton_vibratorTime;
	float XMX_JumpButton_jumpSpeed;
	float XMX_JumpButton_speedY;
	float XMX_JumpButton_gravity;
	float XMX_JumpButton_lowGravity;
	float XMX_JumpButton_highGravity;
	Sprite* XMX_JumpButton_jumpButton;
	Rect XMX_JumpButton_jumpRect;
	bool XMX_JumpButton_jumpButtonFlag;
	bool XMX_JumpButton_touchFlag;
	bool XMX_JumpButton_allowJumpFlag;
	bool XMX_JumpButton_allowJumpTwiceFlag;
	bool XMX_JumpButton_jumpOnceFlag;
	bool XMX_JumpButton_jumpTwiceFlag;
	bool XMX_JumpButton_highGravityFlag;
	bool XMX_JumpButton_jumpSpeedFlag;
	bool XMX_JumpButton_gravityEffectFlag;
};

