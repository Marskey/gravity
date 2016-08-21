#include "stdafx.h"
#include "UIDialog.h"
UIDialog::UIDialog(const char *pFileName, int nPrioryty)
	:m_pContent(NULL)
	, m_bDirty(true)
{
	m_strFileName = CCFileUtils::sharedFileUtils()->fullPathForFilename(pFileName);
	setTouchPriority(nPrioryty);
	setTouchEnabled(true);
}
UIDialog::~UIDialog()
{

}


bool UIDialog::init()
{
	CCLayer::init();
	return initLayout();
}
bool UIDialog::initLayout()
{
	ui::TouchGroup *tg = ui::TouchGroup::create();
	tg->setTouchPriority(getTouchPriority() - 1);
	addChild(tg);
	m_pContent = GUIReader::shareReader()->widgetFromJsonFile(m_strFileName.c_str());
	if (!m_pContent)
	{
		CCLog("json not load", "error");
		return false;
	}
	tg->addWidget(m_pContent);
	return true;
}

void UIDialog::onEnter()
{

	CCLayer::onEnter();
	if (m_bDirty && m_pContent)
	{
		m_bDirty = false;
	}
}
void UIDialog::onExit()
{
	CCLayer::onExit();
}


