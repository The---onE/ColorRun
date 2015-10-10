#include "ButtonLayer.h"

#define RHLIFT visibleSize.width*0.7
#define RHRIGHT visibleSize.width*0.85
#define RHUP visibleSize.height*0.32
#define RHDOWN visibleSize.height*0.08

#define LHLIFT visibleSize.width*0.3
#define LHRIGHT visibleSize.width*0.15
#define LHUP visibleSize.height*0.32
#define LHDOWN visibleSize.height*0.08

#define UL 1
#define DL 2
#define UR 3
#define DR 4

bool ButtonLayer::init()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites/button.plist", "sprites/button.png");

	rState = 0;
	lState = 0;
	rightButtonFlag = false;
	leftButtonFlag = false;

	XMX_Button_setVibratorTime(VibrateTime);

	left = RHLIFT;
	right = RHRIGHT;
	up = RHUP;
	down = RHDOWN;
	rightHandFlag = true;

	scheduleUpdate();
	return true;
}


void ButtonLayer::onEnter()
{
	Layer::onEnter();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(false);
	listener->onTouchBegan = [=](Touch *touch, Event *unused_event){XMX_Button_onTouchBegan(touch, unused_event);return true;};
	listener->onTouchMoved = [=](Touch *touch, Event *unused_event){XMX_Button_onTouchMoved(touch, unused_event);};
	listener->onTouchEnded = [=](Touch *touch, Event *unused_event){XMX_Button_onTouchEnded(touch, unused_event);};
	listener->onTouchCancelled = [=](Touch *touch, Event *unused_event){XMX_Button_onTouchEnded(touch, unused_event);};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	KEYBOARD_LISTENER(ButtonLayer);
}

void ButtonLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_U:
		XMX_Button_needResponse(UL);
		break;
	case EventKeyboard::KeyCode::KEY_J:
		XMX_Button_needResponse(DL);
		break;
	case EventKeyboard::KeyCode::KEY_I:
		XMX_Button_needResponse(UR);
		break;
	case EventKeyboard::KeyCode::KEY_K:
		XMX_Button_needResponse(DR);
		break;
	default:
		break;
	}
}

void ButtonLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	default:
		break;
	}
}

void ButtonLayer::RGBMode()
{
	setUpRightButton(right, GREEN);
	setDownRightButton(right, BLUE);

	rS = Sprite::create();
	changeSprite(rS, RED);
	SETSIZE(rS, 0.1);
	rS->setPosition(Point(right, (up+down)/2));
	this->addChild(rS);

	rightButtonFlag = true;
	leftButtonFlag = false;
}

void ButtonLayer::RGBRGBMode()
{
	setUpRightButton(right, GREEN);
	setDownRightButton(right, BLUE);
	setUpLeftButton(left, GREEN);
	setDownLeftButton(left, BLUE);

	rS = Sprite::create();
	changeSprite(rS, RED);
	SETSIZE(rS, 0.1);
	rS->setPosition(Point(right, (up+down)/2));
	this->addChild(rS);

	lS = Sprite::create();
	changeSprite(lS, RED);
	SETSIZE(lS, 0.1);
	lS->setPosition(Point(left, (up+down)/2));
	this->addChild(lS);

	rightButtonFlag = true;
	leftButtonFlag = true;
}

void ButtonLayer::WhiteMode()
{
	lState = WHITE;
	rState = WHITE;

	rightButtonFlag = false;
	leftButtonFlag = false;
}

void ButtonLayer::changeHand()
{
	if (rightHandFlag)
	{
		left = LHLIFT;
		right = LHRIGHT;
		up = LHUP;
		down = LHDOWN;
		rightHandFlag = false;
	}
	else
	{
		left = RHLIFT;
		right = RHRIGHT;
		up = RHUP;
		down = RHDOWN;
		rightHandFlag = true;
	}

	if (rightButtonFlag)
	{
		setUpRightButton(right, XMX_Button_getMainState(UR));
		setDownRightButton(right, XMX_Button_getMainState(DR));
	}

	if (leftButtonFlag)
	{
		setUpLeftButton(left, XMX_Button_getMainState(UL));
		setDownLeftButton(left, XMX_Button_getMainState(DL));
	}
	if (rS)
	{
		rS->setPosition(Point(right, (up+down)/2));
	}
	if (lS)
	{
		lS->setPosition(Point(left, (up+down)/2));
	}

}

int ButtonLayer::getState()
{
	if (lState == rState)
	{
		return lState;
	}
	else
	{
		return lState + rState;
	}
}

void ButtonLayer::setUpRightButton(float pX, int color)
{
	switch (color)
	{
	case RED:
		XMX_Button_changeButton(UR, Sprite::createWithSpriteFrameName("red_u.png"), 0.14f, pX, up);
		break;
	case GREEN:
		XMX_Button_changeButton(UR, Sprite::createWithSpriteFrameName("green_u.png"), 0.14f, pX, up);
		break;
	case BLUE:
		XMX_Button_changeButton(UR, Sprite::createWithSpriteFrameName("blue_u.png"), 0.14f, pX, up);
		break;
	}
	XMX_Button_setMainState(UR, color);
}

void ButtonLayer::setDownRightButton(float pX, int color)
{
	switch (color)
	{
	case RED:
		XMX_Button_changeButton(DR, Sprite::createWithSpriteFrameName("red_d.png"), 0.14f, pX, down);
		break;
	case GREEN:
		XMX_Button_changeButton(DR, Sprite::createWithSpriteFrameName("green_d.png"), 0.14f, pX, down);
		break;
	case BLUE:
		XMX_Button_changeButton(DR, Sprite::createWithSpriteFrameName("blue_d.png"), 0.14f, pX, down);
		break;
	}
	XMX_Button_setMainState(DR, color);
}

void ButtonLayer::setUpLeftButton(float pX, int color)
{
	switch (color)
	{
	case RED:
		XMX_Button_changeButton(UL, Sprite::createWithSpriteFrameName("red_u.png"), 0.14f, pX, up);
		break;
	case GREEN:
		XMX_Button_changeButton(UL, Sprite::createWithSpriteFrameName("green_u.png"), 0.14f, pX, up);
		break;
	case BLUE:
		XMX_Button_changeButton(UL, Sprite::createWithSpriteFrameName("blue_u.png"), 0.14f, pX, up);
		break;
	}
	XMX_Button_setMainState(UL, color);
}

void ButtonLayer::setDownLeftButton(float pX, int color)
{
	switch (color)
	{
	case RED:
		XMX_Button_changeButton(DL, Sprite::createWithSpriteFrameName("red_d.png"), 0.14f, pX, down);
		break;
	case GREEN:
		XMX_Button_changeButton(DL, Sprite::createWithSpriteFrameName("green_d.png"), 0.14f, pX, down);
		break;
	case BLUE:
		XMX_Button_changeButton(DL, Sprite::createWithSpriteFrameName("blue_d.png"), 0.14f, pX, down);
		break;
	}
	XMX_Button_setMainState(DL, color);
}


void ButtonLayer::changeSprite(Sprite* s, int color)
{
	SpriteFrame* frame;   
	switch (color)
	{
	case RED:
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("red_now.png");
		break;
	case GREEN:
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("green_now.png");
		break;
	case BLUE:
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("blue_now.png");
		break;
	}
	s->setSpriteFrame(frame);
	if (s == rS)
		rState = color;
	else if (s == lS)
	{
		lState = color;
	}
}

void ButtonLayer::checkPress()
{
	if (rightButtonFlag)
	{
		if (XMX_Button_isNeedResponse(UR))
		{
			int n = rState;
			int t = XMX_Button_getMainState(UR);
			setUpRightButton(right, 111-n-t);
			setDownRightButton(right, n);
			changeSprite(rS, t);
			XMX_Button_responsed(UR);
		}
		if (XMX_Button_isNeedResponse(DR))
		{
			int n = rState;
			int t = XMX_Button_getMainState(DR);
			setDownRightButton(right, 111-n-t);
			setUpRightButton(right, n);
			changeSprite(rS, t);
			XMX_Button_responsed(DR);
		}
	}
	if (leftButtonFlag)
	{
		if (XMX_Button_isNeedResponse(UL))
		{
			int n = lState;
			int t = XMX_Button_getMainState(UL);
			setUpLeftButton(left, 111-n-t);
			setDownLeftButton(left, n);
			changeSprite(lS, t);
			XMX_Button_responsed(UL);
		}
		if (XMX_Button_isNeedResponse(DL))
		{
			int n = lState;
			int t = XMX_Button_getMainState(DL);
			setDownLeftButton(left, 111-n-t);
			setUpLeftButton(left, n);
			changeSprite(lS, t);
			XMX_Button_responsed(DL);
		}
	}
}

void ButtonLayer::update(float dt)
{
	checkPress();
}