#include "XMX_JumpButton.h"
#include "XMX_Vibrator.h"

#define SETSIZE(SPRITE,SIZE) (SPRITE)->setScale(XMX_JumpButton_datum*(SIZE)/(SPRITE)->getContentSize().height)

XMX_JumpButton::XMX_JumpButton()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	XMX_JumpButton_datum = visibleSize.height;

	XMX_JumpButton_jumpButton = NULL;
	XMX_JumpButton_jumpRect = Rect();

	XMX_JumpButton_speedY = 0;
	XMX_JumpButton_jumpSpeed = 0;
	XMX_JumpButton_gravity = 0;
	XMX_JumpButton_lowGravity = 0;
	XMX_JumpButton_highGravity = 0;

	XMX_JumpButton_vibratorTime = 0;

	XMX_JumpButton_jumpButtonFlag = false;
	XMX_JumpButton_touchFlag = false;
	XMX_JumpButton_allowJumpFlag = true;
	XMX_JumpButton_allowJumpTwiceFlag = true;
	XMX_JumpButton_jumpOnceFlag = false;;
	XMX_JumpButton_jumpTwiceFlag = false;
	XMX_JumpButton_highGravityFlag = false;
	XMX_JumpButton_jumpSpeedFlag = false;
	XMX_JumpButton_gravityEffectFlag = false;
}

void XMX_JumpButton::XMX_JumpButton_setJumpButton(Sprite* jumpButton, float size, int x, int y)
{
	removeChild(XMX_JumpButton_jumpButton);

	XMX_JumpButton_jumpButton = jumpButton;
	SETSIZE(XMX_JumpButton_jumpButton, size);
	XMX_JumpButton_jumpButton->setPosition(Point(x,y));
	addChild(XMX_JumpButton_jumpButton);

	XMX_JumpButton_jumpRect = jumpButton->getBoundingBox();

	XMX_JumpButton_jumpButtonFlag = true;
}

void XMX_JumpButton::XMX_JumpButton_setJumpButton(Rect jumpRect)
{
	XMX_JumpButton_jumpRect = jumpRect;

	XMX_JumpButton_jumpButtonFlag = true;
}

void XMX_JumpButton::XMX_JumpButton_setJumpSpeed(float jumpSpeed)
{
	XMX_JumpButton_jumpSpeed = jumpSpeed;

	XMX_JumpButton_jumpSpeedFlag = true;
}

void XMX_JumpButton::XMX_JumpButton_setVibratorTime(int time)
{
	XMX_JumpButton_vibratorTime = time;
}

void XMX_JumpButton::XMX_JumpButton_allowJump()
{
	XMX_JumpButton_allowJumpFlag = true;
	XMX_JumpButton_gravityEffectFlag = true;
}

void XMX_JumpButton::XMX_JumpButton_notAllowJump()
{
	XMX_JumpButton_allowJumpFlag = false;
}

void XMX_JumpButton::XMX_JumpButton_forbidden()
{
	XMX_JumpButton_notAllowJump();
	XMX_JumpButton_gravityEffectFlag = false;
	XMX_JumpButton_resume();
}

void XMX_JumpButton::XMX_JumpButton_setGravity(float gravity)
{
	XMX_JumpButton_lowGravity = gravity;
	XMX_JumpButton_highGravity = gravity;

	XMX_JumpButton_gravity = gravity;
}

void XMX_JumpButton::XMX_JumpButton_setGravity(float lowGravity, float highGravity)
{
	XMX_JumpButton_lowGravity = lowGravity;
	XMX_JumpButton_highGravity = highGravity;

	XMX_JumpButton_gravity = lowGravity;
}

float XMX_JumpButton::XMX_JumpButton_getSpeedY()
{
	return XMX_JumpButton_speedY;
}

bool XMX_JumpButton::XMX_JumpButton_checkControler()
{
	if (!XMX_JumpButton_jumpButtonFlag)
		return false;
	if (!XMX_JumpButton_jumpSpeedFlag)
		return false;

	return true;
}

void XMX_JumpButton::XMX_JumpButton_gravityEffect()
{
	if (XMX_JumpButton_gravityEffectFlag)
	{
		XMX_JumpButton_speedY -= XMX_JumpButton_gravity;
		if (XMX_JumpButton_highGravityFlag)
		{
			if (XMX_JumpButton_speedY < 0)
			{
				XMX_JumpButton_setLowGravity();
			}
		}
	}
}

void XMX_JumpButton::XMX_JumpButton_resume()
{
	XMX_JumpButton_speedY = 0;
	XMX_JumpButton_jumpOnceFlag = false;
	XMX_JumpButton_jumpTwiceFlag = false;

	XMX_JumpButton_setLowGravity();
}

void XMX_JumpButton::XMX_JumpButton_jumpBegan()
{
	if (!XMX_JumpButton_jumpOnceFlag && !XMX_JumpButton_jumpTwiceFlag)
	{
		XMX_Vibrator::vibrate(XMX_JumpButton_vibratorTime);

		XMX_JumpButton_speedY = XMX_JumpButton_jumpSpeed;
		XMX_JumpButton_jumpOnceFlag = true;
		XMX_JumpButton_setLowGravity();
	}
	else if (XMX_JumpButton_jumpOnceFlag && !XMX_JumpButton_jumpTwiceFlag && XMX_JumpButton_allowJumpTwiceFlag)
	{
		XMX_Vibrator::vibrate(XMX_JumpButton_vibratorTime);

		XMX_JumpButton_speedY = XMX_JumpButton_jumpSpeed;
		XMX_JumpButton_jumpTwiceFlag = true;
		XMX_JumpButton_setLowGravity();
	}
}

void XMX_JumpButton::XMX_JumpButton_jumpEnded()
{
	XMX_JumpButton_setHighGravity();
}

void XMX_JumpButton::XMX_JumpButton_onTouchBegan(Touch *touch, Event *unused_event)
{
	if (XMX_JumpButton_allowJumpFlag)
	{
		if (!XMX_JumpButton_touchFlag)
		{
			if (XMX_JumpButton_checkControler())
			{
				Point touchPoint = Director::getInstance()->convertToGL(touch->getLocationInView());
				if (XMX_JumpButton_jumpRect.containsPoint(touchPoint))
				{
					XMX_JumpButton_jumpBegan();
					XMX_JumpButton_touchFlag = true;
				}

			}
		}
	}
}

void XMX_JumpButton::XMX_JumpButton_onTouchMoved(Touch *touch, Event *unused_event)
{
}

void XMX_JumpButton::XMX_JumpButton_onTouchEnded(Touch *touch, Event *unused_event)
{
	if (XMX_JumpButton_allowJumpFlag)
	{
		if (XMX_JumpButton_touchFlag)
		{
			Point touchPoint = Director::getInstance()->convertToGL(touch->getLocationInView());
			Point startPoint = Director::getInstance()->convertToGL(touch->getStartLocationInView());

			if (XMX_JumpButton_jumpRect.containsPoint(startPoint))
			{
				XMX_JumpButton_jumpEnded();
				XMX_JumpButton_touchFlag = false;
			}
		}
	}
}

void XMX_JumpButton::XMX_JumpButton_setHighGravity()
{
	XMX_JumpButton_gravity = XMX_JumpButton_highGravity;
	XMX_JumpButton_highGravityFlag = true;
}

void XMX_JumpButton::XMX_JumpButton_setLowGravity()
{
	XMX_JumpButton_gravity = XMX_JumpButton_lowGravity;
	XMX_JumpButton_highGravityFlag = false;
}