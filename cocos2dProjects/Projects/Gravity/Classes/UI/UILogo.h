#ifndef _UILOGO_H_
#define _UILOGO_H_
#include "UIDialog.h"
class UILogo : public UIDialog
{
public:
	UILogo();
	~UILogo();
	virtual bool initLayout();
	virtual void update(float dt);
	CREATE_FUNC(UILogo);
private:

private:
	ui::UIImageView *m_pImageLogo;

};

#endif //_UILOGO_H_