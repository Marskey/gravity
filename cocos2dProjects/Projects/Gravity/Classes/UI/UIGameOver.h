#ifndef _UIGameOver_H_
#define _UIGameOver_H_
#include "UIDialog.h"
#include "BlurLayer.h"

class UIGameOver : public UIDialog
{
public:
	UIGameOver();
	~UIGameOver();
	virtual bool initLayout();

	CREATE_FUNC(UIGameOver);
private:

	void onReplayTouch(CCObject *pObject, ui::TouchEventType touchType);
	void onReturnTouch(CCObject *pObject,ui::TouchEventType touchType);

private:
	
	ui::UIButton *s_pBtnReplay;
	ui::UIButton *s_pBtnReturn;
	ui::ImageView *m_win;
	BlurLayer *pBlur;
	

};

#endif //_UIGameOver_H_