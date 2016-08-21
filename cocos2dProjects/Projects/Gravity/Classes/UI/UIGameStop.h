#ifndef _UIGameStop_H_
#define _UIGameStop_H_
#include "UIDialog.h"
#include "BlurLayer.h"
enum winTag
{
	kUiPause,
};

class UIGameStop : public UIDialog
{
public:
	UIGameStop();
	~UIGameStop();
	virtual bool initLayout();
	CREATE_FUNC(UIGameStop);
private:
	void onMusicTouch(CCObject *pObject, ui::CheckBoxEventType touchType);
	void onSoundEffectTouch(CCObject *pObject,ui::CheckBoxEventType touchType);
	void onReplayTouch(CCObject *pObject, ui::TouchEventType touchType);
	void onPlayTouch(CCObject *pObject,ui::TouchEventType touchType);
	void onReSelectTouch(CCObject *pObject,ui::TouchEventType touchType);
	void closingActionOnBack();
	void closingActionForall();
	void close();
	void countDown();
	void numChange();

private:

	ui::UICheckBox *s_pMusic;
	ui::UICheckBox *s_pSEffect;
	ui::UIButton *s_pBtnReplay;
	ui::UIButton *s_pBtnPlay;
	ui::UIButton *s_pBtnReSelect;
	ui::UIImageView *m_pWin;
	BlurLayer *pBlur;
	CCLabelAtlas* num;
};

#endif //_UIGameStop_H_