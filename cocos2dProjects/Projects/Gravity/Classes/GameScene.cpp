#include "stdafx.h"
#include "GameScene.h"
#include "Entity\EntityManager.h"
#include "DBCSVService\DBCSVService.h"
#include "UI\UIGameOver.h"
#include "UI\UIGameStop.h"
#include "UI\UIGameVictory.h"
#include "UI\UIStageSelect.h"
#include "Global\Global_Define.h"
#include "Config.h"

GameScene::GameScene() :UIDialog("GameUi/GameUi_1.ExportJson")
{

}
GameScene::~GameScene()
{
	CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
}
bool GameScene::init()
{
	if (!UIDialog::initLayout())
	{
		return false;
	}
//获取控件
	GetObjectByName(&pPauseBtn, "Button_pause");
	GetObjectByName(&pClock, "Image_clockIcon");
	GetObjectByName(&pSec, "AtlasLabel_time_sec");
	GetObjectByName(&pEnergyBar, "ProgressBar_Energy");
	GetObjectByName(&pCoreGet, "AtlasLabel_coreGet");
	GetObjectByName(&pCoreIcon, "Image_coreIcon");
//------------------------------关卡创建----------------------------------
	//Config::getInstance()->setstageNum(2);
	pEntities = EntityManager::createWithLevel(Config::getInstance()->getstageNum());
	this->addChild(pEntities,-1);
//------------------------------background----------------------------------
	CCSprite* pBackground = CCSprite::create(PATH_BACKGROUND_01);
	pBackground->setAnchorPoint(CCPointZero);
	this->addChild(pBackground, -2);
//------------------------------------------------------------------------
	m_CoreGetNum = 0;

	pPauseBtn->addTouchEventListener(this, ui::SEL_TouchEvent(&GameScene::onPauseBtn));

	CCNotificationCenter::sharedNotificationCenter()->addObserver(
		this,
		callfuncO_selector(GameScene::gameOver),
		"gameOver",
		NULL);

	CCNotificationCenter::sharedNotificationCenter()->addObserver(
		this,
		SEL_CallFuncO(&GameScene::resume),
		"backToGame",
		NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(
		this,
		SEL_CallFuncO(&GameScene::addCoreNum),
		"addCoreNum",
		NULL);
	this->setTouchEnabled(true);
	this->setTouchMode(kCCTouchesOneByOne);
	_time = 30;
	gameState = true;
	m_mapPreScale = 1.0f;
	m_touchesNum = 0;
	WIN_SIZE = CCDirector::sharedDirector()->getVisibleSize();
	if (CCUserDefault::sharedUserDefault()->getBoolForKey("isMusicOn",true))
	{
		if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
		{
			//CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic("Music/MainMenuBgm.wav");
		}
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Music/GameLayerBgm.wav");
	}
	scheduleUpdate();	
	schedule(SEL_SCHEDULE(&GameScene::countTime), 1.0f);
	return true;
}
void GameScene::gameOver(CCObject* pSender)
{
	gameState = false;
	pPauseBtn->setEnabled(false);
	if (strcmp((char*)pSender, "lose") == 0)
	{
		scheduleOnce(SEL_SCHEDULE(&GameScene::gameLose), 1.0f);
	}
	else if (strcmp((char*)pSender , "win") == 0)
	{
		scheduleOnce(SEL_SCHEDULE(&GameScene::gameWin), 2.0f);
	}
}
void GameScene::gameWin(float dt)
{	
	Config::getInstance()->settime(_time);
	Config::getInstance()->setevaluation(calculateEvaluation());
	SCENECHANGE(UIGameVictory, 0.0f);

}
void GameScene::gameLose(float dt)
{
	SCENECHANGE(UIGameOver, 0.0f);
}
void GameScene::update(float dt)
{
	pEnergyBar->setPercent(pEntities->getRocketEnergy());
}

bool GameScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (gameState)
	{
		CCNotificationCenter::sharedNotificationCenter()->postNotification("TouchBegan", NULL);
	}
	return true;
}

void GameScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}
void GameScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if (gameState)
	{
		CCNotificationCenter::sharedNotificationCenter()->postNotification("TouchEnded", NULL);
	}
}
void GameScene::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
	this->ccTouchEnded(pTouch, pEvent);
}

void GameScene::pause()
{
	this->pauseSchedulerAndActions();
	pEntities->pause();
}
void GameScene::resume(CCObject* pSender)
{
	this->resumeSchedulerAndActions();
	pEntities->resume();
}

void GameScene::onPauseBtn(CCObject* pSender, ui::TouchEventType type)
{
	if (type == ui::TOUCH_EVENT_ENDED)
	{
		if (CCUserDefault::sharedUserDefault()->getBoolForKey("isFXOn",true))
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("FX/buttonClick.wav");
		}
		pause();
		UIGameStop* pWinStop = UIGameStop::create();
		this->addChild(pWinStop);
	}

}

void GameScene::countTime(float dt)
{
	//_time += 1/60.0f;
	//temp = CCString::createWithFormat("%02d", (int)_time % 60);
	//pSec->setStringValue(temp->getCString());
	//temp = CCString::createWithFormat("%02d", (int)_time / 60);
	//pMin->setStringValue(temp->getCString());
	//if (abs(_time - 25.0f) < 1e-03)
	//{
	//	CCAction* action = CCRepeat::create(CCSequence::create(CCFadeOut::create(0.1f), CCFadeIn::create(0.1f), NULL),25);
	//	pMin->runAction(action);
	//	pSec->runAction(action);
	//}
	//if (abs(_time - 30.0f) < 1e-03)
	//{
	//	pMin->setOpacity(100);
	//	pSec->setOpacity(100);
	//	pColon->setOpacity(100);
	//}
	if (_time)
	{
		--_time;
		temp = CCString::createWithFormat("%02d", _time);
		pSec->setStringValue(temp->getCString());
		if (_time == 5)
		{
			CCAction* action = CCRepeat::create(CCSequence::create(CCFadeOut::create(0.1f), CCFadeIn::create(0.1f), NULL), 25);
			pSec->runAction(action);
		}
		if (_time == 0)
		{
			pSec->stopAllActions();
			pSec->setOpacity(100);
			pClock->setOpacity(100);
		}
	}
}

float GameScene::calculateEvaluation()
{
	int num = 0;
	if (m_CoreGetNum > 0)
	{
		++num;
	}
	if (_time)
	{
		++num;
	}
	if (pEnergyBar->getPercent() > 30)
	{
		++num;
	}
	return num;
}

void GameScene::addCoreNum(CCObject *pSender)
{
	temp = CCString::createWithFormat("%d", ++m_CoreGetNum);
	pCoreGet->setStringValue(temp->getCString());
	if (m_CoreGetNum > 0)
	{
		pCoreGet->setOpacity(255);
		pCoreIcon->setOpacity(255);
	}
}