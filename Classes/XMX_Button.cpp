#include "XMX_Button.h"
#include "XMX_Vibrator.h"

#define SETSIZE(SPRITE,SIZE) (SPRITE)->setScale(XMX_Button_datum*(SIZE)/(SPRITE)->getContentSize().height)

XMX_Button::XMX_Button()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	XMX_Button_datum = visibleSize.height;

	XMX_Button_vibratorTime = 0;
}

void XMX_Button::XMX_Button_addButton(int id, XMX_Button_Node* adding)
{
	XMX_Button_list.insert(id, adding);

	return;
}

void XMX_Button::XMX_Button_addButton(int id, Sprite* button, float size, int x, int y, Method press/* =NULL */, Method release/* =NULL */)
{
	XMX_Button_Node* adding = XMX_Button_Node::create();
	SETSIZE(button, size);
	button->setPosition(Point(x,y));
	adding->button = button;
	addChild(adding->button);
	adding->rect = button->getBoundingBox();
	adding->onPress = press;
	adding->onRelease = release;
	adding->buttonFlag = true;
	adding->allowFlag = true;

	XMX_Button_addButton(id, adding);
}

void XMX_Button::XMX_Button_addButton(int id, Rect rect, Method press/* =NULL */, Method release/* =NULL */)
{
	XMX_Button_Node* adding = XMX_Button_Node::create();
	adding->rect = rect;
	adding->onPress = press;
	adding->onRelease = release;
	adding->buttonFlag = true;
	adding->allowFlag = true;

	XMX_Button_addButton(id, adding);
}

void XMX_Button::XMX_Button_changeButton(int id, Sprite* button, float size, int x, int y)
{
	XMX_Button_Node* p = XMX_Button_searchButton(id);
	if (!p)
	{
		XMX_Button_addButton(id, button, size, x, y);
	}
	else
	{
		removeChild(p->button);
		SETSIZE(button, size);
		button->setPosition(Point(x,y));
		p->button = button;
		addChild(p->button);
		p->rect = button->getBoundingBox();
	}
}

void XMX_Button::XMX_Button_setMainState(int id, int state)
{
	XMX_Button_Node* p = XMX_Button_searchButton(id);
	if (p)
	{
		p->mainState = state;
	}
}

int XMX_Button::XMX_Button_getMainState(int id)
{
	XMX_Button_Node* p = XMX_Button_searchButton(id);
	if (p)
	{
		return p->mainState;
	}
	return 0;
}

XMX_Button_Node* XMX_Button::XMX_Button_searchButton(int id)
{
	XMX_Button_Node* p = XMX_Button_list.at(id);
	return p;
}

void XMX_Button::XMX_Button_setVibratorTime(int time)
{
	XMX_Button_vibratorTime = time;
}

void XMX_Button::XMX_Button_allow(int id)
{
	XMX_Button_Node* p = XMX_Button_searchButton(id);
	if (p)
	{
		p->allowFlag = true;
	}
}

void XMX_Button::XMX_Button_forbidden(int id)
{
	XMX_Button_Node* p = XMX_Button_searchButton(id);
	if (p)
	{
		p->allowFlag = false;
	}
}

bool XMX_Button::XMX_Button_isNeedResponse(int id)
{
	XMX_Button_Node* p = XMX_Button_searchButton(id);
	if (p)
	{
		return p->needResponseFlag;
	}
	return false;
}

void XMX_Button::XMX_Button_needResponse(int id)
{
	XMX_Button_Node* p = XMX_Button_searchButton(id);
	if (p)
	{
		p->needResponseFlag = true;
	}
}

void XMX_Button::XMX_Button_responsed(int id)
{
	XMX_Button_Node* p = XMX_Button_searchButton(id);
	if (p)
	{
		p->needResponseFlag = false;
	}
}

void XMX_Button::XMX_Button_onTouchBegan(Touch *touch, Event *unused_event)
{
	Point touchPoint = Director::getInstance()->convertToGL(touch->getLocationInView());
	Map<int, XMX_Button_Node*>::iterator it = XMX_Button_list.begin();
	while (it != XMX_Button_list.end())
	{
		XMX_Button_Node* p = it->second;
		if (p->allowFlag)
		{
			if (!p->touchFlag)
			{
				if (p->buttonFlag)
				{
					if (p->rect.containsPoint(touchPoint))
					{
						XMX_Vibrator::vibrate(XMX_Button_vibratorTime);
						Method method = p->onPress;
						if (method)
						{
							method();
						}
						else
						{
							p->needResponseFlag = true;
						}
						p->touchFlag = true;
					}
				}
			}
		}
		it++;
	}
}

void XMX_Button::XMX_Button_onTouchMoved(Touch *touch, Event *unused_event)
{
}

void XMX_Button::XMX_Button_onTouchEnded(Touch *touch, Event *unused_event)
{
	Point touchPoint = Director::getInstance()->convertToGL(touch->getLocationInView());
	Point startPoint = Director::getInstance()->convertToGL(touch->getStartLocationInView());
	Map<int, XMX_Button_Node*>::iterator it = XMX_Button_list.begin();
	while (it != XMX_Button_list.end())
	{
		XMX_Button_Node* p = it->second;
		if (p->allowFlag)
		{
			if (p->touchFlag)
			{
				if (p->rect.containsPoint(startPoint))
				{
					if (p->rect.containsPoint(touchPoint))
					{
						Method method = p->onRelease;
						if (method)
						{
							method();
						}
					}
					p->touchFlag = false;
				}
			}
		}
		it++;
	}
}