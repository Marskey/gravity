#include "stdafx.h"
#ifndef _UIDialog_H_
#define _UIDialog_H_
class UIDialog :public CCLayer
{
public:
	UIDialog(const char *pFileName, int nPrioryty = 0);
	~UIDialog();
	template <typename T>
	void GetObjectByName(T* ppControl, const char *pName)
	{
		CCAssert(*ppControl = dynamic_cast<T>(ui::UIHelper::seekWidgetByName(m_pContent, pName)), "widget cannot found");
	}
	template <typename T>
	void GetObjectByTag(T* ppControl, int tag)
	{
		*ppControl = dynamic_cast<T>(ui::UIHelper::seekWidgetByTag(m_pContent, tag));
	}
	virtual bool init();
	virtual bool initLayout();
	virtual void onEnter();
	virtual void onExit();
private:
	bool m_bDirty;
	std::string m_strFileName;
protected:
	ui::Widget *m_pContent;
};
#endif //_UIDialog_H_