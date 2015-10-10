#include "MainScene.h"
#include "StageScene_1.h"
#include "StageScene_2.h"
#include "StageScene_3.h"

#define fontSize 0.08

bool MainScene::init()
{
	Scene::init();

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	Label* rgbLable = Label::createWithSystemFont("RGB MODE", "Arial", fontSize*DATUM);
	MenuItemLabel* rgbmode = MenuItemLabel::create(rgbLable, CC_CALLBACK_0(MainScene::RGBMode, this));

	Label* rgbrgbLable = Label::createWithSystemFont("RGBRGB MODE", "Arial", fontSize*DATUM);
	MenuItemLabel* rgbrgbmode = MenuItemLabel::create(rgbrgbLable, CC_CALLBACK_0(MainScene::RGBRGBMode, this));

	Label* whiteLable = Label::createWithSystemFont("WHITE MODE", "Arial", fontSize*DATUM);
	MenuItemLabel* whitemode = MenuItemLabel::create(whiteLable, CC_CALLBACK_0(MainScene::WhiteMode, this));

	if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	Label* playLable = Label::createWithSystemFont("PLAY BGM", "Arial", fontSize*DATUM);
	MenuItemLabel* playBGM = MenuItemLabel::create(playLable);
	Label* stopLable = Label::createWithSystemFont("STOP BGM", "Arial", fontSize*DATUM);
	MenuItemLabel* stopBGM = MenuItemLabel::create(stopLable);
	MenuItemToggle* bgm = MenuItemToggle::createWithCallback(CC_CALLBACK_0(MainScene::PlayStopBGM, this), playBGM, stopBGM, NULL);

	effectFlag = false;
	Label* openEffectLable = Label::createWithSystemFont("OPEN EFFECT", "Arial", fontSize*DATUM);
	MenuItemLabel* openEffect = MenuItemLabel::create(openEffectLable);
	Label* closeEffectLable = Label::createWithSystemFont("CLOSE EFFECT", "Arial", fontSize*DATUM);
	MenuItemLabel* closeEffect = MenuItemLabel::create(closeEffectLable);
	MenuItemToggle* effect = MenuItemToggle::createWithCallback(CC_CALLBACK_0(MainScene::OpenCloseEffect, this), openEffect, closeEffect, NULL);

	Label* quitLable = Label::createWithSystemFont("QUIT GAME", "Arial", fontSize*DATUM);
	MenuItemLabel* quitGame = MenuItemLabel::create(quitLable, CC_CALLBACK_0(MainScene::QuitGame, this));

	Menu* mainMenu = Menu::create(rgbmode, rgbrgbmode, whitemode, bgm, effect, quitGame, NULL);
	mainMenu->alignItemsVerticallyWithPadding(20);
	this->addChild(mainMenu, 1000);

	createBackGround("sprites/main.jpg");

	return true;
}

void MainScene::RGBMode()
{
	StageScene_1* game = StageScene_1::create();
	game->setEffectFlag(effectFlag);
	Director::getInstance()->replaceScene(game);
}

void MainScene::RGBRGBMode()
{
	StageScene_2* game = StageScene_2::create();
	game->setEffectFlag(effectFlag);
	Director::getInstance()->replaceScene(game);
}

void MainScene::WhiteMode()
{
	StageScene_3* game = StageScene_3::create();
	game->setEffectFlag(effectFlag);
	Director::getInstance()->replaceScene(game);
}

void MainScene::PlayStopBGM()
{
	SimpleAudioEngine* audio = SimpleAudioEngine::getInstance();
	if (audio->isBackgroundMusicPlaying())
	{
		audio->stopBackgroundMusic();
	}
	else
	{
		audio->playBackgroundMusic("musics/bgm.mp3");
	}
}

void MainScene::OpenCloseEffect()
{
	effectFlag = !effectFlag;
}

void MainScene::QuitGame()
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

void MainScene::createBackGround(std::string filename)
{
	Sprite* Bg = Sprite::create(filename);
	Bg->setScaleX(visibleSize.width/Bg->getContentSize().width);
	Bg->setScaleY(visibleSize.height/Bg->getContentSize().height);
	Bg->setAnchorPoint(Point::ZERO);
	Bg->setPosition(Point::ZERO);
	this->addChild(Bg, -1000);
}