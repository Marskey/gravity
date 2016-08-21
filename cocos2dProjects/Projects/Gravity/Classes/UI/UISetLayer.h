#ifndef _UISetLayer_H_
#define _UISetLayer_H_
#include "UIDialog.h"
#include "UIMember.h"

class UISetLayer : public UIDialog
{
public:
	UISetLayer();
	~UISetLayer();
	virtual bool initLayout();
	CREATE_FUNC(UISetLayer);
private:
	void onMusicTouch(CCObject *pObject, ui::CheckBoxEventType touchType);
	void onSoundEffectTouch(CCObject *pObject,ui::CheckBoxEventType touchType);
	void onMemberTouch(CCObject *pObject, ui::TouchEventType touchType);
	void onReturnTouch(CCObject *pObject,ui::TouchEventType touchType);
	void onOptionTouch(CCObject *pObject,ui::TouchEventType touchType);
	void closingActionForBack();
	void close();
private:
	CCPoint ORIGIN;
	UIMember *memberLayer;
	ui::UIImageView *m_pWin;
	ui::UICheckBox *s_pMusic;
	ui::UICheckBox *s_pSEffect;
	ui::UIButton *s_pBtnMember;
	ui::UIButton *s_pBtnReturn;
	ui::UIButton *s_pBtnWeixin;

};

#endif //_UISetLayer_H_