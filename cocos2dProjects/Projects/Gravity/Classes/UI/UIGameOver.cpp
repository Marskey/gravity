#include "stdafx.h"	
#include "GameScene.h"
#include "UIGameOver.h"
#include "UIStageSelect.h"
#include "Global\\Global_Define.h"
#include "Config.h"



UIGameOver::UIGameOver() :UIDialog("UIGameOver/UIGameOver_1.ExportJson")
{
	this->setTouchPriority(-3);
}
UIGameOver::~UIGameOver()
{
	
}
bool UIGameOver::initLayout()
{
	if (!UIDialog::initLayout())
	{
		return false;
	}

	pBlur = BlurLayer::create();
	pBlur->setAnchorPoint(CCPointZero);
	this->addChild(pBlur,-1);
	GetObjectByName(&s_pBtnReplay,"Button_again");
	GetObjectByName(&s_pBtnReturn,"Button_map");
	GetObjectByName(&m_win, "Image_win");

	s_pBtnReplay ->addTouchEventListener(this,ui::SEL_TouchEvent(&UIGameOver::onReplayTouch));
	s_pBtnReturn ->addTouchEventListener(this,ui::SEL_TouchEvent(&UIGameOver::onReturnTouch));


	float scaleSm = 0.9f, scaleBig = 10.0f / 9.0f;
	CCScaleBy* scaleToSml = CCScaleBy::create(0.03f, scaleSm);
	CCScaleBy* scaleToBi = CCScaleBy::create(0.03f, scaleBig);
	CCAction* action = CCSequence::create(scaleToSml, scaleToBi, scaleToBi, scaleToSml, NULL);

	if (CCUserDefault::sharedUserDefault()->getBoolForKey("isFXOn"))
	{
		SimpleAudioEngine::sharedEngine()->playEffect("FX/gameOver.mp3");
	}
	m_win->runAction(action);
	return true;
}



void UIGameOver::onReplayTouch(CCObject *pObject, ui::TouchEventType touchType)
{
	if(touchType==ui::TOUCH_EVENT_ENDED)
	{
		if (CCUserDefault::sharedUserDefault()->getBoolForKey("isFXOn"))
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("FX/buttonClick.wav");
		}
		this->removeFromParent();
		collectionArr->release();
		SCENECHANGE(GameScene, 0.5f);

	}
}
void UIGameOver::onReturnTouch(CCObject *pObject, ui::TouchEventType touchType)
{
	if(touchType==ui::TOUCH_EVENT_ENDED)
	{
		if (CCUserDefault::sharedUserDefault()->getBoolForKey("isFXOn"))
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("FX/buttonClick.wav");
		}
		this->removeFromParent();
		CCUserDefault::sharedUserDefault()->setIntegerForKey("curStageNum", Config::getInstance()->getstageNum());
		collectionArr->release();
		SCENECHANGE(UIStageSelect,1.0f);

	}
}


