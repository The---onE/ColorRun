#pragma once

#define DATUM visibleSize.height
#define SETSIZE(SPRITE,SIZE) (SPRITE)->setScale(DATUM*(SIZE)/(SPRITE)->getContentSize().height)
#define PlayerPositionX visibleSize.width*0.3
#define VibrateTime 40

#define BLACK 0
#define RED 100
#define GREEN 10
#define BLUE 1
#define YELLOW 110
#define PINK 101
#define CYAN 11
#define WHITE 111
#define RIGID 1111
#define R(color) (((color%1000)/100)*100)
#define G(color) (((color%100)/10)*10)
#define B(color) (color%10)
#define Ri(color) (color/1000)

#define KEYBOARD_FUNCTION void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);\
						  void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

#define KEYBOARD_LISTENER(CLASS) EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();\
								 keyboardListener->onKeyPressed = CC_CALLBACK_2(CLASS::onKeyPressed, this);\
								 keyboardListener->onKeyReleased = CC_CALLBACK_2(CLASS::onKeyReleased, this);\
								 Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
