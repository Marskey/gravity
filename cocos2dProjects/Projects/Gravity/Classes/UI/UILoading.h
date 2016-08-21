/************************************************************************
*  Name: UILoading.h
*  Purpose:
*  Author: Marskey
*  time: 2015-06-14	
*  version: 1.0
/************************************************************************/
#include "stdafx.h"
#ifndef HEADER__UILOADING
#define HEADER__UILOADING
#include "UI\UIDialog.h"
class UILoading :public UIDialog 
{
public:
    UILoading();
	bool init();
	bool load();
    void loadingCallBack(cocos2d::CCObject *obj);
    void loadingCallBack(float delta);
	CREATE_FUNC(UILoading);

private:
    int m_numberOfResources;
    int m_numberOfLoadedResources;
	ui::UILoadingBar *m_pProgressBar;
	ui::UILabelAtlas *m_pProgressPercent;

};
#endif // HEADER__UILOADING