#include "ControlLayer.h"

#define closeItemSize 0.1
#define closeItemPositionX visibleSize.width*0.95
#define closeItemPositionY visibleSize.height*0.95
#define pauseItemSize 0.1
#define pauseItemPositionX visibleSize.width/2
#define pauseItemPositionY visibleSize.height*0.95
#define restartItemSize 0.1
#define restartItemPositionX visibleSize.width*0.95
#define restartItemPositionY visibleSize.height/2
#define chItemSize 0.1
#define chItemPositionX visibleSize.width*0.05
#define chItemPositionY visibleSize.height*0.95

bool ControlLayer::init()
{
	Layer::init();
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites/item.plist", "sprites/item.png");

	createCloseButton("close_n.png", "close_s.png");
	createPauseButton("pause_n.png", "pause_s.png");
	createRestartButton("restart_n.png", "restart_s.png");
	createChangeHandButton("changeHand.png", "changeHand.png");

	pauseFlag = false;
	restartFlag = false;
	changeHandFlag = false;

	return true;
}

void ControlLayer::onEnter()
{
	Layer::onEnter();
}


void ControlLayer::createCloseButton(std::string filenameN, std::string filenameS)
{
	MenuItemImage* closeItem = MenuItemImage::create();
	closeItem->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(filenameN));
	closeItem->setSelectedSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(filenameS));
	closeItem->setCallback(CC_CALLBACK_0(ControlLayer::quitGame, this));

	SETSIZE(closeItem, closeItemSize);
	closeItem->setPosition(Point(origin.x + closeItemPositionX, origin.y + closeItemPositionY));
	Menu* pMenu = Menu::create(closeItem, NULL);
	pMenu->setPosition(Point::ZERO);
	this->addChild(pMenu);
}

void ControlLayer::createPauseButton(std::string filenameN, std::string filenameS)
{
	MenuItemImage* pauseItem = MenuItemImage::create();
	pauseItem->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(filenameN));
	pauseItem->setSelectedSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(filenameS));
	pauseItem->setCallback(CC_CALLBACK_0(ControlLayer::pauseGame, this));

	SETSIZE(pauseItem, pauseItemSize);
	pauseItem->setPosition(Point(origin.x + pauseItemPositionX, origin.y + pauseItemPositionY));
	Menu* pMenu = Menu::create(pauseItem, NULL);
	pMenu->setPosition(Point::ZERO);
	this->addChild(pMenu);
}

void ControlLayer::createRestartButton(std::string filenameN, std::string filenameS)
{
	MenuItemImage* restartItem = MenuItemImage::create();
	restartItem->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(filenameN));
	restartItem->setSelectedSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(filenameS));
	restartItem->setCallback(CC_CALLBACK_0(ControlLayer::restartGame, this));

	SETSIZE(restartItem, restartItemSize);
	restartItem->setPosition(Point(origin.x + restartItemPositionX, origin.y + restartItemPositionY));
	Menu* pMenu = Menu::create(restartItem, NULL);
	pMenu->setPosition(Point::ZERO);
	this->addChild(pMenu);
}

void ControlLayer::createChangeHandButton(std::string filenameN, std::string filenameS)
{
	MenuItemImage* chItem = MenuItemImage::create();
	chItem->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(filenameN));
	chItem->setSelectedSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(filenameS));
	chItem->setCallback(CC_CALLBACK_0(ControlLayer::changeHand, this));

	SETSIZE(chItem, chItemSize);
	chItem->setPosition(Point(origin.x + chItemPositionX, origin.y + chItemPositionY));
	Menu* pMenu = Menu::create(chItem, NULL);
	pMenu->setPosition(Point::ZERO);
	this->addChild(pMenu);
}


void ControlLayer::pauseGame()
{
	if (pauseFlag)
	{
		Director::getInstance()->resume();
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		pauseFlag = false;
	}
	else
	{
		Director::getInstance()->pause();
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		pauseFlag = true;
	}
}

void ControlLayer::quitGame()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}

void ControlLayer::restartGame()
{
	restartFlag = true;
}

void ControlLayer::changeHand()
{
	changeHandFlag = true;
}

bool ControlLayer::isRestart()
{
	return restartFlag;
}

bool ControlLayer::isChangeHand()
{
	if (changeHandFlag)
	{
		changeHandFlag = false;
		return true;
	}
	else
	{
		return false;
	}
}