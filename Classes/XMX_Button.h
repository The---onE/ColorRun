#pragma once

#include "cocos2d.h"
USING_NS_CC;

typedef bool(*Method)();
class XMX_Button_Node : public Node
{
public:
	CREATE_FUNC(XMX_Button_Node);
	bool init()
	{
		button = NULL;
		rect = Rect();
		onPress = NULL;
		onRelease = NULL;
		buttonFlag = false;
		touchFlag = false;
		allowFlag = false;
		needResponseFlag = false;
		mainState = 0;
		secondState = 0;

		return true;
	}

	Sprite* button;
	Rect rect;
	Method onPress;
	Method onRelease;
	bool buttonFlag;
	bool touchFlag;
	bool allowFlag;
	bool needResponseFlag;
	int mainState;
	int secondState;
};

class XMX_Button : public virtual Layer
{
public:
	XMX_Button();
	void XMX_Button_addButton(int id, Sprite* button, float size, int x, int y, Method press=NULL, Method release=NULL);
	void XMX_Button_addButton(int id, Rect rect, Method press=NULL, Method release=NULL);
	void XMX_Button_changeButton(int id, Sprite* button, float size, int x, int y);
	void XMX_Button_setMainState(int id, int state);
	int XMX_Button_getMainState(int id);
	void XMX_Button_setVibratorTime(int time);
	void XMX_Button_allow(int id);
	void XMX_Button_forbidden(int id);
	bool XMX_Button_isNeedResponse(int id);
	void XMX_Button_needResponse(int id);
	void XMX_Button_responsed(int id);
	void XMX_Button_onTouchBegan(Touch *touch, Event *unused_event);
	void XMX_Button_onTouchMoved(Touch *touch, Event *unused_event);
	void XMX_Button_onTouchEnded(Touch *touch, Event *unused_event);

private:
	void XMX_Button_addButton(int id, XMX_Button_Node* adding);
	XMX_Button_Node* XMX_Button_searchButton(int id);
	Size visibleSize;
	Point origin;
	int XMX_Button_datum;
	int XMX_Button_vibratorTime;

	Map<int, XMX_Button_Node*> XMX_Button_list;
};

