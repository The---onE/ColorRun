#include "PlayerLayer.h"

#define PlayerSize 0.12
#define PlayerPositionY visibleSize.height*0.301
#define jumpSpeed 0.014
#define lowGravity 0.0007
#define highGravith 0.0009

bool PlayerLayer::init()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites/player.plist", "sprites/player.png");

	state = 0;
	playerFrameNum = 4;
	playerAnimateSpeed = 0.075f;
	createPlayer("black/b_0.png");

	XMX_JumpButton_setJumpButton(Rect(0, 0, visibleSize.width/2, visibleSize.height*0.8));
	XMX_JumpButton_setJumpSpeed(jumpSpeed * DATUM);
	XMX_JumpButton_setGravity(lowGravity * DATUM, highGravith * DATUM);
	XMX_JumpButton_allowJump();
	XMX_JumpButton_setVibratorTime(VibrateTime);
	rightHandFlag = true;

	this->scheduleUpdate();

	return true;
}

void PlayerLayer::onEnter()
{
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(false);
	listener->onTouchBegan = CC_CALLBACK_2(PlayerLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlayerLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PlayerLayer::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(PlayerLayer::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	KEYBOARD_LISTENER(PlayerLayer);
}

void PlayerLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_SPACE:
		XMX_JumpButton_jumpBegan();
		break;
	default:
		break;
	}
}

void PlayerLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_SPACE:
		XMX_JumpButton_jumpEnded();
		break;
	default:
		break;
	}
}

void PlayerLayer::changeHand()
{
	if (rightHandFlag)
	{
		XMX_JumpButton_setJumpButton(Rect(visibleSize.width/2, 0, visibleSize.width/2, visibleSize.height*0.8));
		rightHandFlag = false;
	}
	else
	{
		XMX_JumpButton_setJumpButton(Rect(0, 0, visibleSize.width/2, visibleSize.height*0.8));
		rightHandFlag = true;
	}
}

bool PlayerLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	XMX_JumpButton_onTouchBegan(touch, unused_event);
	return true;
}

void PlayerLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
	XMX_JumpButton_onTouchMoved(touch, unused_event);
}

void PlayerLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
	XMX_JumpButton_onTouchEnded(touch, unused_event);
}

void PlayerLayer::createPlayer(std::string filename)
{
	Player = Sprite::createWithSpriteFrameName(filename);
	colorAnimete(BLACK);
	Player->setPosition(Point(origin.x + PlayerPositionX, origin.y + PlayerPositionY));
	SETSIZE(Player, PlayerSize);
	Player->setAnchorPoint(Point(1, 0));
	this->addChild(Player);
}

void PlayerLayer::stopAnimete()
{
	Player->stopActionByTag(BLACK);
	Player->stopActionByTag(RED);
	Player->stopActionByTag(GREEN);
	Player->stopActionByTag(BLUE);
	Player->stopActionByTag(YELLOW);
	Player->stopActionByTag(PINK);
	Player->stopActionByTag(CYAN);
	Player->stopActionByTag(WHITE);
}

void PlayerLayer::colorAnimete(std::string filename, int color)
{
	stopAnimete();
	Animation *playerAnimate = Animation::create();
	for (int i=0; i<playerFrameNum; i++)
	{
		char name[32];
		sprintf(name, filename.c_str(), i);
		playerAnimate->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	playerAnimate->setDelayPerUnit(playerAnimateSpeed);
	RepeatForever* animate = RepeatForever::create(Animate::create(playerAnimate));
	animate->setTag(color);
	Player->runAction(animate);

	state = color;
}

void PlayerLayer::colorAnimete(int color)
{
	switch (color)
	{
	case BLACK:
		colorAnimete("black/b_%d.png", BLACK);
		break;
	case RED:
		colorAnimete("red/r_%d.png", RED);
		break;
	case GREEN:
		colorAnimete("green/g_%d.png", GREEN);
		break;
	case BLUE:
		colorAnimete("blue/b_%d.png", BLUE);
		break;
	case YELLOW:
		colorAnimete("yellow/y_%d.png", YELLOW);
		break;
	case PINK:
		colorAnimete("pink/p_%d.png", PINK);
		break;;
	case CYAN:
		colorAnimete("cyan/c_%d.png", CYAN);
		break;
	case WHITE:
		colorAnimete("white/w_%d.png", WHITE);
		break;
	}
}

Sprite* PlayerLayer::getPlayerSprite()
{
	return Player;
}

int PlayerLayer::getState()
{
	return state;
}

bool PlayerLayer::checkOutScreen()
{
	if (Player->getPositionX() < 0 || Player->getBoundingBox().getMaxY() < 0)
	{
		return true;
	}
	return false;
}

void PlayerLayer::update(float dt)
{
	Player->setPositionY(Player->getPositionY() + XMX_JumpButton_getSpeedY());
	XMX_JumpButton_gravityEffect();
}
