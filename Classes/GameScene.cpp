#include "GameScene.h"
#include "MainScene.h"

#define levleUp 0.000002
#define giveHealth 0.00085
#define giveHealthCycle 5
#define wallCycleRate 0.07

bool GameScene::init()
{
	Scene::init();

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	bg = BackGroundLayer::create();
	this->addChild(bg, -1000);
	control = ControlLayer::create();
	this->addChild(control, 1001);
	ground = GroundLayer::create();
	this->addChild(ground, 3);
	player = PlayerLayer::create();
	this->addChild(player, 1);
	color = ColorWallLayer::create();
	this->addChild(color, 2);
	button = ButtonLayer::create();
	this->addChild(button, 999);

	winFlag = false;
	effectFlag = false;
	playingFlag = false;
	overFlag = false;
	setSpeed(0);
	groundProgress = 0;
	wallProgress = 0;
	wallTime = 0;
	wallCycle = wallCycleRate*DATUM;
	score = 0;
	giveHealthProgress = 0;

	srand(time(NULL));
	this->scheduleUpdate();
	return true;
}

void GameScene::setEffectFlag(bool effectFlag)
{
	this->effectFlag = effectFlag;
}

void GameScene::showScore(int delta)
{
	score += delta;
	removeChild(scoreLable);
	char text[32];
	sprintf(text, "%d", score);
	scoreLable = Label::createWithBMFont("fonts/sg.fnt", text);
	scoreLable->setPosition(Point(origin.x + visibleSize.width*0.5, origin.y + visibleSize.height*0.88));
	SETSIZE(scoreLable, 0.05);
	addChild(scoreLable, 9999);
}

void GameScene::setSpeed(float speed)
{
	if (bg)
		bg->setSpeed(speed);
	if (ground)
		ground->setSpeed(speed);
	if (color)
		color->setSpeed(speed);
}

void GameScene::checkRestart()
{
	if (control)
	{
		if (control->isRestart())
		{
			MainScene* pScene = MainScene::create();
			Director::getInstance()->replaceScene(pScene);
		}
	}
}

void GameScene::checkChangeHand()
{
	if (control)
	{
		if (control->isChangeHand())
		{
			player->changeHand();
			button->changeHand();
		}
	}
}

void GameScene::GameoverSchedule(float dt)
{
	if (!overFlag)
	{
		float rotateG = gameover->getRotation();
		float scaleG = gameover->getScale();
		gameover->setRotation(rotateG + 24);
		gameover->setScale(scaleG + 0.02);
		if (gameover->getContentSize().height*gameover->getScale()>DATUM*0.9 && (int)(gameover->getRotation())%360<24)
		{
			overFlag = true;
			createRestart();
		}
	}
}

void GameScene::update(float dt)
{
	checkRestart();
	if (playingFlag)
	{
		if (!winFlag)
		{
			speed += levleUp * DATUM;
			setSpeed(speed);
			if (player->checkOutScreen())
			{
				speed = 0;
				setSpeed(0);
				winFlag = true;
				Gameover();
				return;
			}

			checkChangeHand();
			showScore(1);

			if (ground->checkCollision(player->getPlayerSprite(), player->XMX_JumpButton_getSpeedY(), player->getState()))
			{
				player->XMX_JumpButton_resume();
			}

			color->checkCollision(player->getPlayerSprite(), player->XMX_JumpButton_getSpeedY(), player->getState());

			if (button->getState() != player->getState())
			{
				player->colorAnimete(button->getState());
			}

			int x = player->getPlayerSprite()->getPositionX();
			if (x < PlayerPositionX)
			{
				giveHealthProgress++;
				if (giveHealthCycle >= giveHealthCycle)
				{
					player->getPlayerSprite()->setPositionX(x + DATUM*giveHealth*giveHealthCycle);
					giveHealthProgress = 0;
				}
			}

			if (ground->isBlockOver())
			{
				ground->createBlock(getGroundMapNode());
			}

			wallTime += speed;
			if (wallTime > wallCycle)
			{
				wallTime = 0;
				color->createWall(getColorMapNode());
			}
		}
	}
	else
	{
		playingFlag = true;
		initGame();
	}
}

void GameScene::writeHigh(std::string mode, int score)
{
	UserDefault::getInstance()->setIntegerForKey(mode.c_str(), score);
	UserDefault::getInstance()->flush();

	return;
}

int GameScene::readHigh(std::string mode)
{
	return UserDefault::getInstance()->getIntegerForKey(mode.c_str());
}

char GameScene::getGroundMapNode()
{
	int n = *groundP;
	if (n == STOP)
	{
		randomGroundMap();
		n = *groundP;
	}
	groundP++;
	return n;
}

char GameScene::getColorMapNode()
{
	int n = *colorP;
	if (n == STOP)
	{
		randomColorMap();
		n = *colorP;
	}
	colorP++;
	return n;
}

void GameScene::randomGroundMap()
{
	int r = rand();
	groundP = getGroundMap(r);
}

void GameScene::randomColorMap()
{
	int r = rand();
	colorP = getColorMap(r);
}
