#pragma once

#include "cocos2d.h"
#include "XMX_JumpButton.h"
#include "Global.h"
USING_NS_CC;

class PlayerLayer : public XMX_JumpButton
{
public:
	CREATE_FUNC(PlayerLayer);
	Sprite* getPlayerSprite();
	int getState();
	bool checkOutScreen();
	void colorAnimete(int color);
	void changeHand();

protected:
	bool init();
	void onEnter();
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);
	void createPlayer(std::string filename);
	void stopAnimete();
	void colorAnimete(std::string filename, int tag);
	void update(float dt);
	KEYBOARD_FUNCTION;

	Sprite* Player;
	int playerFrameNum;
	int state;
	float playerAnimateSpeed;
	bool rightHandFlag;
	Size visibleSize;
	Point origin;
};