#ifndef _UIMember_H_
#define _UIMember_H_
#include "UIDialog.h"

class UIMember : public UIDialog
{
public:
	UIMember();
	~UIMember();
	virtual bool initLayout();
	CREATE_FUNC(UIMember);
private:

	void onReturnTouch(CCObject *pObject,ui::TouchEventType touchType);
	
private:

	ui::UIButton *s_pBtnReturn;

};

#endif //_UIMember_H_