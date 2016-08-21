#include "stdafx.h"	
#include "UIGameVictory.h"
#include "UIStageSelect.h"
#include "Global/Global_Define.h"
#include "Config.h"
#include "Global/Global_Define.h"
#include "GameScene.h"
#include "Android/AndroidInterface.h"


UIGameVictory::UIGameVictory() :UIDialog("UIVictory/UIVictory_1.ExportJson")
{
	
	this ->setTouchPriority(-3);
}
UIGameVictory::~UIGameVictory()
{
	
}
bool UIGameVictory::initLayout()
{
	if (!UIDialog::initLayout())
	{
		return false;
	}
	pBlur = BlurLayer::create();
	pBlur->setAnchorPoint(CCPointZero);
	this->addChild(pBlur,-1);

	GetObjectByName(&s_pBtnNext,"Button_next");
	GetObjectByName(&s_pBtnReSelect,"Button_map");
	GetObjectByName(&s_pImgWin,"Image_textWin");
	GetObjectByName(&s_pImgWindow, "Image_win");
	GetObjectByName(&s_pBtnShared, "Button_share");
	GetObjectByName(&s_pBtnAgain, "Button_again");

	float scaleSm = 0.9f, scaleBig = 10.0f / 9.0f;

	s_pBtnNext->addTouchEventListener(this,ui::SEL_TouchEvent(&UIGameVictory::onNextTouch));
	s_pBtnReSelect->addTouchEventListener(this,ui::SEL_TouchEvent(&UIGameVictory::onReSelectTouch));
	s_pBtnAgain->addTouchEventListener(this,ui::SEL_TouchEvent(&UIGameVictory::onReplayTouch));
	s_pBtnShared->addTouchEventListener(this,ui::SEL_TouchEvent(&UIGameVictory::onSharedTouch));

	CCSequence *ImgActions = CCSequence::create(CCScaleTo::create(0.0f, 0.0f),CCScaleTo::create(2.0f, 1.0f),NULL);
	s_pImgWin->runAction(ImgActions);


	m_pScore = CCArmature::create("star");
	m_pScore->setPosition(320, 640);
	m_pScore->setScale(0.65f);
	addChild(m_pScore,1);

	CCScaleBy* scaleToSml = CCScaleBy::create(0.03f, scaleSm);
	CCScaleBy* scaleToBi = CCScaleBy::create(0.03f, scaleBig);
	CCAction* action = CCSequence::create(scaleToSml, scaleToBi, scaleToBi, scaleToSml, NULL);

	s_pImgWindow->runAction(action);

	int unlockNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("unlockNum", 1);
	_curStageNum = Config::getInstance()->getstageNum();

	CCString* strTemp = CCString::createWithFormat("stageEvaluation_%02d", _curStageNum);
	int evaluation = Config::getInstance()->getevaluation();
	int preEvaluation = CCUserDefault::sharedUserDefault()->getIntegerForKey(strTemp->getCString());
	if (evaluation > preEvaluation)
	{
		CCUserDefault::sharedUserDefault()->setIntegerForKey(strTemp->getCString(), evaluation);
	}
	if (evaluation == 1)
	{
		if (CCUserDefault::sharedUserDefault()->getBoolForKey("isFXOn"))
		{
			SimpleAudioEngine::sharedEngine()->playEffect("FX/starOut.wav");
		}
		m_pScore->getAnimation()->play("Animation1");
	}
	else if (evaluation== 2)
	{
		if (CCUserDefault::sharedUserDefault()->getBoolForKey("isFXOn"))
		{
			SimpleAudioEngine::sharedEngine()->playEffect("FX/starOut.wav");
		}
		m_pScore->getAnimation()->play("Animation2");
	}
	else if (evaluation== 3)
	{
		if (CCUserDefault::sharedUserDefault()->getBoolForKey("isFXOn"))
		{
			SimpleAudioEngine::sharedEngine()->playEffect("FX/starOut.wav");
		}
		m_pScore->getAnimation()->play("Animation3");
	}
	m_pLight = CCArmature::create("round");
	m_pLight->setPosition(320, 640);
	m_pLight->setScale(0.8f);
	addChild(m_pLight,0);
	m_pLight->getAnimation()->play("Animation1");

	int Level = Config::getInstance()->getstageNum();
	level = CCLabelTTF::create("0", "Segoe Print", 40);
	level->setColor(ccc3(255,255,255));
	this->addChild(level);
	strTemp = CCString::createWithFormat("LEVEL %d", Level);
	level->setString(strTemp->getCString());
	level->setPosition(ccp(320,800));
	int time = Config::getInstance()->gettime();
	int m = time/60;
	int s = time%60;
	scoreTime = CCLabelTTF::create("","Segoe Print",40);
	scoreTime->setColor(ccc3(255, 255, 255));
    this->addChild(scoreTime, 1);
	strTemp = CCString::createWithFormat("%02d : %02d", m, s);
	scoreTime->setString(strTemp->getCString());
	scoreTime->setPosition(ccp(320, 330)); 
	if (CCUserDefault::sharedUserDefault()->getBoolForKey("isFXOn"))
	{
		SimpleAudioEngine::sharedEngine()->playEffect("FX/victory.wav");
	}

	if (++_curStageNum > unlockNum&&_curStageNum <= 10)
	{
		CCUserDefault::sharedUserDefault()->setIntegerForKey("unlockNum", _curStageNum);
	}
	return true;
}

void UIGameVictory::onNextTouch(CCObject *pObject, ui::TouchEventType touchType)
{
	if (touchType == ui::TOUCH_EVENT_ENDED)
	{
		if(CCUserDefault::sharedUserDefault()->getBoolForKey("isFXOn"))
		{
			SimpleAudioEngine::sharedEngine()->playEffect("FX/buttonClick.wav");
		}
		collectionArr->release();
		Config::getInstance()->setstageNum(MIN(_curStageNum,MAXSTAGENUM));
		SCENECHANGE(GameScene, 1.0f);

	}
}
void UIGameVictory::onReSelectTouch(CCObject *pObject, ui::TouchEventType touchType)
{
	if(touchType==ui::TOUCH_EVENT_ENDED)
	{
		if(CCUserDefault::sharedUserDefault()->getBoolForKey("isFXOn"))
		{
			SimpleAudioEngine::sharedEngine()->playEffect("FX/buttonClick.wav");
		}
		CCUserDefault::sharedUserDefault()->setIntegerForKey("curStageNum", Config::getInstance()->getstageNum());
		collectionArr->release();
		SCENECHANGE(UIStageSelect, 1.0f);
	}
}

void UIGameVictory::onReplayTouch(CCObject *pObject, ui::TouchEventType touchType)
{
	if(touchType==ui::TOUCH_EVENT_ENDED)
	{
		if(CCUserDefault::sharedUserDefault()->getBoolForKey("isFXOn"))
		{
			SimpleAudioEngine::sharedEngine()->playEffect("FX/buttonClick.wav");
		}
		collectionArr->release();
		SCENECHANGE(GameScene, 0.5f);
	}
}

void UIGameVictory::onSharedTouch(CCObject *pObject, ui::TouchEventType touchType)
{
	if (touchType == ui::TOUCH_EVENT_ENDED)
	{
		//screenShot();
		//share_to_freinds();
	}
}

void UIGameVictory::screenShot()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCRenderTexture* pRender = CCRenderTexture::create(visibleSize.width, visibleSize.height);
	pRender->begin();
	CCDirector::sharedDirector()->getRunningScene()->visit();
	pRender->end();
	pRender->saveToFile("screenShot/scoreShot.jpg",kCCImageFormatJPEG);
}