#include "stdafx.h"
#include "UIMainMenu.h"
#include "UIStageSelect.h"
#include "UISetLayer.h"
#include "Global/Global_Define.h"
#include <math.h>

#define  LongRadius 690
#define  MidRadius 600
#define ShortRadius 500
UIMainMenu::UIMainMenu()
	:UIDialog("UIMainMenu/UIMainMenu_1.ExportJson")
{
	
}
UIMainMenu::~UIMainMenu()
{

}
bool UIMainMenu::initLayout()
{
	if (!UIDialog::initLayout())
	{
		return false;
	}
	this->setTouchEnabled(false);
	this->setTouchMode(kCCTouchesOneByOne);
	winSize = CCDirector::sharedDirector()->getWinSize();
	ui::UIImageView* pSun; 
	ui::UIImageView* pHalo;
	ui::UIImageView* pTitle;
	GetObjectByName(&pHalo, "Image_halo");
	GetObjectByName(&pSun, "Image_planet_00");
	GetObjectByName(&pImage_planet_01, "Image_planet_01");
	GetObjectByName(&pImage_planet_02, "Image_planet_02");
	GetObjectByName(&pImage_planet_03, "Image_planet_03");
	GetObjectByName(&pTitle, "Image_title");
	GetObjectByName(&pButton_setting, "Button_setting");

	animationForTitle(pTitle);
//------------------------------------------------------------------------Planet
	rotate(10.0f, pSun);
	rotate(-10.0f, pImage_planet_01);
	rotate(9.0f, pImage_planet_02);
	rotate(8.0f, pImage_planet_03);
	
	x = 268.0f, y = 292.0f;
	m_preDegree1 = 60.0f;
	m_preDegree2 = 150.0f;
	m_preDegree3 = 300.0f;
	float Sin = sinf(CC_DEGREES_TO_RADIANS(60.0f));
	float Cos = cosf(CC_DEGREES_TO_RADIANS(60.0f));
	pImage_planet_01->setPosition(ccp(ShortRadius*Cos + x, ShortRadius*Sin*0.15f + y));
	Sin = sinf(CC_DEGREES_TO_RADIANS(150.0f));
	Cos = cosf(CC_DEGREES_TO_RADIANS(150.0f));
	pImage_planet_02->setPosition(ccp(MidRadius*Cos + x, MidRadius*Sin*0.23f + y));
	Sin = sinf(CC_DEGREES_TO_RADIANS(300.0f));
	Cos = cosf(CC_DEGREES_TO_RADIANS(300.0f));
	pImage_planet_03->setPosition(ccp(LongRadius*Cos + x, LongRadius*Sin*0.29f + y));
//------------------------------------------------------------------------Halo
	CCArmature *redHalo = CCArmature::create("redHaloAnimation");	
	redHalo->setPosition(ccp(winSize.width*0.41875f, winSize.height*0.304166f));
	redHalo->getAnimation()->play("Animation1");
	redHalo->setRotation(25.3f);
	redHalo->setScale(0.0f);
	redHalo->setZOrder(4);
	animationForRedHalo(redHalo);
	((ui::Widget*)(pSun->getParent()))->addNode(redHalo);

	animationForHalo(pHalo);
//------------------------------------------------------------------------button
	pButton_setting->addTouchEventListener(this, ui::SEL_TouchEvent(&UIMainMenu::onSettingTouch));
	pButton_setting->setTouchEnabled(false);
	scheduleUpdate();

    if (CCUserDefault::sharedUserDefault()->getBoolForKey("isMusicOn", "true"))
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Music/MainMenuBgm.wav", true);


	return true;
}

void UIMainMenu::update(float delta)
{
	circle();
}

void UIMainMenu::circle()
{
//------------------------------------------------------------------------no1
	float degree = 0.7f;
	float Sin = sinf(CC_DEGREES_TO_RADIANS(m_preDegree1));
	float Cos = cosf(CC_DEGREES_TO_RADIANS(m_preDegree1));

	if (Sin > 0)
	{
		degree = 0.14f;
		pImage_planet_01->setZOrder(2);
	}
	else
		pImage_planet_01->setZOrder(4);

	m_preDegree1 += degree;
	pImage_planet_01->setPosition(ccp(ShortRadius*Cos + x, ShortRadius*Sin*0.15f + y-30));
	pImage_planet_01->setScale((-Sin + 1) / 2 * 0.066f + 0.04f);
	m_preDegree1 = fmod(m_preDegree1, 360.0f);
//------------------------------------------------------------------------no2
	degree = 0.4f;
	Sin = sinf(CC_DEGREES_TO_RADIANS(m_preDegree2));
	Cos = cosf(CC_DEGREES_TO_RADIANS(m_preDegree2));
	
	if (Sin > 0)
	{
		degree = 0.11f;
		pImage_planet_02->setZOrder(1);
	}
	else
		pImage_planet_02->setZOrder(5);
	 
	m_preDegree2 += degree;
	pImage_planet_02->setPosition(ccp(MidRadius*Cos + x, MidRadius*Sin*0.19f + y-50));
	pImage_planet_02->setScale((-Sin + 1) / 2 * 0.36f + 0.12f);
	m_preDegree2 = fmod(m_preDegree2, 360.0f);
//------------------------------------------------------------------------no3
	degree = 0.2f;
	Sin = sinf(CC_DEGREES_TO_RADIANS(m_preDegree3));
	Cos = cosf(CC_DEGREES_TO_RADIANS(m_preDegree3));
	 
	if (Sin > 0)
	{
		degree = 0.09f;
		pImage_planet_03->setZOrder(0);
	}
	else
		pImage_planet_03->setZOrder(6);

	m_preDegree3 += degree;
	pImage_planet_03->setPosition(ccp(LongRadius*Cos + x, LongRadius*Sin*0.23f + y-70));
	pImage_planet_03->setScale((-Sin + 1) / 2 * 0.66f + 0.18f);
	m_preDegree3 = fmod(m_preDegree3, 360.0f);
}
void UIMainMenu::rotate(float omega,CCNode *pObj)
{
	CCRotateBy *rotate = CCRotateBy::create(1.0f, omega);
	CCAction *action = CCRepeatForever::create(rotate);
	pObj->runAction(action);
}

void UIMainMenu::animationForHalo(CCNode *pObj)
{
	CCSequence* action = CCSequence::create(
		CCFadeTo::create(1.0f, 160), 
		CCFadeTo::create(1.0f, 90), 
		NULL
		);
	pObj->runAction(CCRepeatForever::create(action));
}

void UIMainMenu::animationForTitle(CCNode *pObj)
{
	CCAction *action = CCSequence::create(
		CCDelayTime::create(1.0f),
		CCSpawn::createWithTwoActions(CCFadeIn::create(0.2f), CCScaleTo::create(0.2f, 0.5f)),
		CCScaleTo::create(0.1f,0.7f),
		CCScaleTo::create(0.05f,0.6f),
		CCCallFunc::create(this, SEL_CallFunc(&UIMainMenu::callFun)),
		NULL
		);
	pObj->runAction(action);
}
void UIMainMenu::callFun()
{
	this->setTouchEnabled(true);
	pButton_setting->setTouchEnabled(true);
	textAnimation = CCArmature::create("textAnimation");
	textAnimation->setScale(0.6f);
	textAnimation->getAnimation()->play("Animation1");
	textAnimation->setPosition(ccp(winSize.width / 2, winSize.height/2 ));
	this->addChild(textAnimation);

}

void UIMainMenu::animationForRedHalo(CCNode *pObj)
{
	CCAction *action = CCSequence::create(
		CCDelayTime::create(0.5f),
		CCScaleTo::create(0.4f, 1.0f),
		NULL
		);
	pObj->runAction(action);
}

void UIMainMenu::onSettingTouch(CCObject *pObject, ui::TouchEventType touchType)
{
	if (touchType == ui::TOUCH_EVENT_ENDED)
	{
		UISetLayer *setting = UISetLayer::create();
		this->addChild(setting);
	}
}

bool UIMainMenu::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	textAnimation->getAnimation()->setSpeedScale(10.0f);
	scheduleOnce(SEL_SCHEDULE(&UIMainMenu::callFunForStart), 1.0f);
	this->setTouchEnabled(false);
	return true;
}

void UIMainMenu::callFunForStart(float delta)
{
	textAnimation->removeFromParent();
	SCENECHANGE(UIStageSelect, 1.0f);
}