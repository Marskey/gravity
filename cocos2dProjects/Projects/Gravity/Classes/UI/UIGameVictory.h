#ifndef _UIGameVictory_H_
#define _UIGameVictory_H_
#include "UIDialog.h"
#include "BlurLayer.h"


class UIGameVictory : public UIDialog
{
public:
	UIGameVictory();
	~UIGameVictory();
	virtual bool initLayout();
	CREATE_FUNC(UIGameVictory);
private:
	
	void onNextTouch(CCObject *pObject, ui::TouchEventType touchType);
	void onReSelectTouch(CCObject *pObject,ui::TouchEventType touchType);
	void onReplayTouch(CCObject *pObject,ui::TouchEventType touchType);
	void onSharedTouch(CCObject *pObject, ui::TouchEventType touchType);
	void screenShot();
private:
	int _curStageNum;

private:
	CCLabelTTF *scoreTime;
	CCLabelTTF *level;
	ui::UIButton *s_pBtnNext;
	ui::UIButton *s_pBtnReSelect;
	ui::UIButton *s_pBtnAgain;
	ui::UIButton *s_pBtnShared;
	ui::UIImageView *s_pImgWin;
	ui::UIImageView *s_pImgWindow;
	CCArmature *m_pLight;
	CCArmature *m_pScore;
	BlurLayer *pBlur;
};

#endif //_UIGameVictory_H_