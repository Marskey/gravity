#include "stdafx.h"	
#include "UIOption.h"
#include "Global/Global_Define.h"
#include "UISetLayer.h"
#include "SimpleAudioEngine.h"


UIOption::UIOption() :UIDialog(PATH_OPTION)
{
	
	this ->setTouchPriority(-4);
}
UIOption::~UIOption()
{
	
}
bool UIOption::initLayout()
{
	if (!UIDialog::initLayout())
	{
		return false;
	}

	GetObjectByName(&s_pBtnReturn,"Return");
	s_pBtnReturn->addTouchEventListener(this,ui::SEL_TouchEvent(&UIOption::onReturnTouch));


	float scaleSm = 0.9f, scaleBig = 10.0f / 9.0f;
	CCScaleBy* scaleToSml = CCScaleBy::create(0.03f, scaleSm);
	CCScaleBy* scaleToBi = CCScaleBy::create(0.03f, scaleBig);
	CCAction* action = CCSequence::create(scaleToSml, scaleToBi, scaleToBi, scaleToSml, NULL);

	this->runAction(action);

	return true;
}


void UIOption::onReturnTouch(CCObject *pObject, ui::TouchEventType touchType)
{
	if(touchType==ui::TOUCH_EVENT_ENDED)
	{
		if(CCUserDefault::sharedUserDefault()->getBoolForKey("isFXOn",true))
		{
			SimpleAudioEngine::sharedEngine()->playEffect("FX/buttonClick.wav",false);
		}
	   this->removeAllChildrenWithCleanup(true);		
	}
}

