#ifndef _UIMAINMENU_H_
#define _UIMAINMENU_H_
#include "UIDialog.h"
#include "UISetLayer.h"

class UIMainMenu :public UIDialog
{
public:
	UIMainMenu();
	~UIMainMenu();
	virtual bool initLayout();
	void update(float delta);
	CREATE_FUNC(UIMainMenu);
private:
	void circle();
	float m_preDegree1;
	float m_preDegree2;
	float m_preDegree3;
	float x, y;
	CCSize winSize;
private:
	void onSettingTouch(CCObject *pObject, ui::TouchEventType touchType);
private:
	void rotate(float omega,CCNode *pObj);
	void animationForHalo(CCNode *pObj);
	void animationForTitle(CCNode *pObj);
	void animationForRedHalo(CCNode *pObj);
	void callFun();
	void callFunForStart(float delta);
private:
	ui::UIImageView* pImage_planet_01;
	ui::UIImageView* pImage_planet_02;
	ui::UIImageView* pImage_planet_03;
	ui::UIButton* pButton_setting;
	CCArmature *textAnimation;
private:
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
};
#endif //_UIMAINMENU_H_