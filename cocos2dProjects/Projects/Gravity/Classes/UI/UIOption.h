#ifndef _UIOption_H_
#define _UIOption_H_
#include "UIDialog.h"

class UIOption : public UIDialog
{
public:
	UIOption();
	~UIOption();
	virtual bool initLayout();
	CREATE_FUNC(UIOption);
private:

	void onReturnTouch(CCObject *pObject,ui::TouchEventType touchType);
	
private:

	ui::UIButton *s_pBtnReturn;

};

#endif //_UIOption_H_