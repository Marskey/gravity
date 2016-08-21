#include "stdafx.h"	
#include "UIMember.h"
#include "UISetLayer.h"
#include "SimpleAudioEngine.h"


UIMember::UIMember() :UIDialog("Member/Member_2_1.ExportJson")
{
	
	this ->setTouchPriority(-4);
}
UIMember::~UIMember()
{
	
}
bool UIMember::initLayout()
{
	if (!UIDialog::initLayout())
	{
		return false;
	}

	GetObjectByName(&s_pBtnReturn,"Return");
	s_pBtnReturn->addTouchEventListener(this,ui::SEL_TouchEvent(&UIMember::onReturnTouch));


	this ->setPosition(0,0);
	CCSequence *SetActions = CCSequence::create(CCScaleBy::create(0.06f, 0.95f), 
		CCScaleBy::create(0.06f, 1.05f), CCScaleBy::create(0.06f, 1.0f), NULL);
	this->runAction(SetActions);

	return true;
}


void UIMember::onReturnTouch(CCObject *pObject, ui::TouchEventType touchType)
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

