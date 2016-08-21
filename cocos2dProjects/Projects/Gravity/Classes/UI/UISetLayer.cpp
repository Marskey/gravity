#include "stdafx.h"	
#include "Global/Global_Define.h"
#include "UISetLayer.h"
//#include "UIMainMenu.h"
#include "UIOption.h"
UISetLayer::UISetLayer() :UIDialog(PATH_SETINGLAYER)
{
	//this ->setTouchPriority(-3);
}
UISetLayer::~UISetLayer()
{
	
}
bool UISetLayer::initLayout()
{
	if (!UIDialog::initLayout())
	{
		return false;
	}

	GetObjectByName(&s_pMusic,"Music");
	GetObjectByName(&s_pSEffect, "SEffect");
	GetObjectByName(&s_pBtnMember,"Member");
	GetObjectByName(&s_pBtnReturn,"Close");
	GetObjectByName(&s_pBtnWeixin,"weixin");
	GetObjectByName(&m_pWin, "Image_win");

	s_pMusic->addEventListenerCheckBox(this,ui::SEL_SelectedStateEvent(&UISetLayer::onMusicTouch));
	s_pMusic->setSelectedState(CCUserDefault::sharedUserDefault()->getBoolForKey("isMusicOn",true));
	s_pSEffect->addEventListenerCheckBox(this, ui::SEL_SelectedStateEvent(&UISetLayer::onSoundEffectTouch));
	s_pSEffect->setSelectedState(CCUserDefault::sharedUserDefault()->getBoolForKey("isFXOn",true));

	s_pBtnMember->addTouchEventListener(this,ui::SEL_TouchEvent(&UISetLayer::onMemberTouch));
	s_pBtnReturn->addTouchEventListener(this,ui::SEL_TouchEvent(&UISetLayer::onReturnTouch));
	s_pBtnWeixin->addTouchEventListener(this,ui::SEL_TouchEvent(&UISetLayer::onOptionTouch));

	float scaleSm = 0.9f, scaleBig = 10.0f / 9.0f;
	CCScaleBy* scaleToSml = CCScaleBy::create(0.03f, scaleSm);
	CCScaleBy* scaleToBi = CCScaleBy::create(0.03f, scaleBig);
	CCAction* action = CCSequence::create(scaleToSml, scaleToBi, scaleToBi, scaleToSml, NULL);

	m_pWin->runAction(action);



	return true;
}


void UISetLayer::onMusicTouch(CCObject *pObject, ui::CheckBoxEventType touchType)
{
	if (CCUserDefault::sharedUserDefault()->getBoolForKey("isFXOn"))
	{
		SimpleAudioEngine::sharedEngine()->playEffect("FX/buttonClick.wav");
	}
	if (CCUserDefault::sharedUserDefault()->getBoolForKey("isMusicOn"))
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic("Music/MainMenuBgm.wav");
		CCUserDefault::sharedUserDefault()->setBoolForKey("isMusicOn", false);
		s_pMusic->setSelectedState(false);
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Music/MainMenuBgm.wav", true);
		CCUserDefault::sharedUserDefault()->setBoolForKey("isMusicOn", true);
		s_pMusic->setSelectedState(true);
	}
}
void UISetLayer::onSoundEffectTouch(CCObject *pObject, ui::CheckBoxEventType touchType)
{
	if (CCUserDefault::sharedUserDefault()->getBoolForKey("isFXOn"))
	{
		CCUserDefault::sharedUserDefault()->setBoolForKey("isFXOn", false);
		SimpleAudioEngine::sharedEngine()->stopAllEffects();
		s_pSEffect->setSelectedState(false);
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("FX/buttonClick.wav");
		CCUserDefault::sharedUserDefault()->setBoolForKey("isFXOn", true);
		s_pSEffect->setSelectedState(true);
	}
}
void UISetLayer::onMemberTouch(CCObject *pObject, ui::TouchEventType touchType)
{
	if (touchType == ui::CHECKBOX_STATE_EVENT_SELECTED)
	{
		if (CCUserDefault::sharedUserDefault()->getBoolForKey("isFXOn"))
		{
			SimpleAudioEngine::sharedEngine()->playEffect("FX/buttonClick.wav");
		}
		memberLayer = UIMember::create();
		this->addChild(memberLayer);
	}
}

void UISetLayer::onReturnTouch(CCObject *pObject, ui::TouchEventType touchType)
{
	if(touchType==ui::TOUCH_EVENT_ENDED)
	{
		if(CCUserDefault::sharedUserDefault()->getBoolForKey("isFXOn"))
		{
			SimpleAudioEngine::sharedEngine()->playEffect("FX/buttonClick.wav");
		}
		closingActionForBack();
	}
}
void UISetLayer::onOptionTouch(CCObject *pObject, ui::TouchEventType touchType)
{
	if (touchType == ui::TOUCH_EVENT_ENDED)
	{
		if(CCUserDefault::sharedUserDefault()->getBoolForKey("isFXOn"))
		{
			SimpleAudioEngine::sharedEngine()->playEffect("FX/buttonClick.wav");
		}
		CCLayer *layer = UIOption::create();
		this->addChild(layer);
	}
}

void UISetLayer::closingActionForBack()
{
	CCAction* action = CCSequence::create(
		CCScaleTo::create(0.2f,0.0f),
		CCCallFunc::create(this,SEL_CallFunc(&UISetLayer::close)),
		NULL);
	m_pWin->runAction(action);
}
void UISetLayer::close()
{
	this->removeFromParent();
}