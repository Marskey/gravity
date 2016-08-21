#include "stdafx.h"	
#include "UIGameStop.h"
#include "GameScene.h"
#include "Global\Global_Define.h"
#include "UIStageSelect.h"
#include "Config.h"	


UIGameStop::UIGameStop() :UIDialog(PATH_PAUSELAYER)
{
	this ->setTouchPriority(-3);
}
UIGameStop::~UIGameStop()
{
	num->release();
}
bool UIGameStop::initLayout()
{
	if (!UIDialog::initLayout())
	{
		return false;
	}
	pBlur = BlurLayer::create();
	pBlur->setAnchorPoint(CCPointZero);
	this->addChild(pBlur,-1);
	GetObjectByName(&s_pMusic,"Music");
	GetObjectByName(&s_pSEffect, "SEffect");
	GetObjectByName(&s_pBtnReplay,"Again");
	GetObjectByName(&s_pBtnPlay,"Continue");
	GetObjectByName(&s_pBtnReSelect,"Map");
	GetObjectByName(&m_pWin, "Image_win");
	s_pMusic->addEventListenerCheckBox(this,ui::SEL_SelectedStateEvent(&UIGameStop::onMusicTouch));
	s_pMusic->setSelectedState(CCUserDefault::sharedUserDefault()->getBoolForKey("isMusicOn", true));

	s_pSEffect->addEventListenerCheckBox(this, ui::SEL_SelectedStateEvent(&UIGameStop::onSoundEffectTouch));
	s_pSEffect->setSelectedState(CCUserDefault::sharedUserDefault()->getBoolForKey("isFXOn", true));

	s_pBtnReplay->addTouchEventListener(this,ui::SEL_TouchEvent(&UIGameStop::onReplayTouch));
	s_pBtnPlay->addTouchEventListener(this,ui::SEL_TouchEvent(&UIGameStop::onPlayTouch));
	s_pBtnReSelect->addTouchEventListener(this,ui::SEL_TouchEvent(&UIGameStop::onReSelectTouch));


	num = CCLabelAtlas::create("3","Number_png/number.png",300,300,'1');
	num->retain();
	float scaleSm = 0.9f, scaleBig = 10.0f / 9.0f;
	CCScaleBy* scaleToSml = CCScaleBy::create(0.03f, scaleSm);
	CCScaleBy* scaleToBi = CCScaleBy::create(0.03f, scaleBig);
	CCAction* action = CCSequence::create(scaleToSml, scaleToBi, scaleToBi, scaleToSml, NULL);

	m_pWin->runAction(action);
	return true;
}

void UIGameStop::onMusicTouch(CCObject *pObject,ui::CheckBoxEventType touchType)
{
	if(CCUserDefault::sharedUserDefault()->getBoolForKey("isFXOn"))
	{
		SimpleAudioEngine::sharedEngine()->playEffect("FX/buttonClick.wav");
	}
	if(CCUserDefault::sharedUserDefault()->getBoolForKey("isMusicOn"))
	{
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic("Music/GameLayerBgm.wav");
		CCUserDefault::sharedUserDefault()->setBoolForKey("isMusicOn",false);
		s_pMusic->setSelectedState(false);
	}
	else
	{
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Music/GameLayerBgm.wav");
		CCUserDefault::sharedUserDefault()->setBoolForKey("isMusicOn",true);
		s_pMusic->setSelectedState(true);
	}
}
void UIGameStop::onSoundEffectTouch(CCObject *pObject, ui::CheckBoxEventType touchType)
{
	if(CCUserDefault::sharedUserDefault()->getBoolForKey("isFXOn"))
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
		CCUserDefault::sharedUserDefault()->setBoolForKey("isFXOn", false);
		s_pSEffect->setSelectedState(false);
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("FX/buttonClick.wav");
		CCUserDefault::sharedUserDefault()->setBoolForKey("isFXOn",true);
		s_pSEffect->setSelectedState(true);
	}
}
//жиЭц
void UIGameStop::onReplayTouch(CCObject *pObject, ui::TouchEventType touchType)
{
	if(touchType==ui::TOUCH_EVENT_ENDED)
	{
		if(CCUserDefault::sharedUserDefault()->getBoolForKey("isFXOn"))
		{
			SimpleAudioEngine::sharedEngine()->playEffect("FX/buttonClick.wav");
		}
		collectionArr->release();
		SCENECHANGE(GameScene, 0.5f);
		closingActionForall();
	}
}
void UIGameStop::onPlayTouch(CCObject *pObject, ui::TouchEventType touchType)
{
	if(touchType==ui::TOUCH_EVENT_ENDED)
	{
		if(CCUserDefault::sharedUserDefault()->getBoolForKey("isFXOn"))
		{
			SimpleAudioEngine::sharedEngine()->playEffect("FX/buttonClick.wav");
		}
		closingActionOnBack();
		countDown();
	}
}
void UIGameStop::onReSelectTouch(CCObject *pObject,ui::TouchEventType touchType)
{
	if(touchType==ui::TOUCH_EVENT_ENDED)
	{
		if(CCUserDefault::sharedUserDefault()->getBoolForKey("isFXOn"))
		{
			SimpleAudioEngine::sharedEngine()->playEffect("FX/buttonClick.wav");
		}
		CCUserDefault::sharedUserDefault()->setIntegerForKey("curStageNum", Config::getInstance()->getstageNum());
		collectionArr->release();
		SCENECHANGE(UIStageSelect,1.0f);
		closingActionForall();
	}
}

void UIGameStop::closingActionOnBack()
{
	CCAction* action = CCSequence::create(
		CCScaleTo::create(0.2f,0.0f),
		CCDelayTime::create(3.0f),
		CCCallFunc::create(this,SEL_CallFunc(&UIGameStop::close)),
		NULL);
	m_pWin->runAction(action);
}

void UIGameStop::closingActionForall()
{
	CCAction* action = CCSequence::create(
		CCScaleTo::create(0.2f,0.0f),
		NULL);
	m_pWin->runAction(action);
}

void UIGameStop::close()
{
	GameScene* layer = dynamic_cast<GameScene*>(this->getParent());
	layer->resume(NULL);
	this->removeFromParent();
}

void UIGameStop::countDown()
{
	num->setPosition(ccp(320, 480));
	num->setAnchorPoint(ccp(0.5, 0.5));	
	num->setScale(0.0f);
	this->addChild(num);
	CCAction* action = CCSequence::create(CCDelayTime::create(0.2f),
		CCSpawn::createWithTwoActions(CCScaleTo::create(0.5f, 1.0f),CCFadeIn::create(0.3f)),
		CCSpawn::createWithTwoActions(CCScaleTo::create(0.5f, 0.0f),CCFadeIn::create(0.0f)),
		CCCallFunc::create(this,SEL_CallFunc(&UIGameStop::numChange)),
		CCSpawn::createWithTwoActions(CCScaleTo::create(0.5f, 1.0f),CCFadeIn::create(0.3f)),
		CCSpawn::createWithTwoActions(CCScaleTo::create(0.5f, 0.0f),CCFadeIn::create(0.0f)),
		CCCallFunc::create(this,SEL_CallFunc(&UIGameStop::numChange)),
		CCSpawn::createWithTwoActions(CCScaleTo::create(0.5f, 1.0f),CCFadeIn::create(0.0f)),
		CCSpawn::createWithTwoActions(CCScaleTo::create(0.5f, 0.0f),CCFadeIn::create(0.0f)),
		
		NULL);
	num->runAction(action);
	
}

void UIGameStop::numChange()
{
	static int Num = 3;
	CCString* str = CCString::createWithFormat("%d", --Num);
	num->setString(str->getCString());
	if (Num == 1)
	{
		Num = 3;
	}
}
