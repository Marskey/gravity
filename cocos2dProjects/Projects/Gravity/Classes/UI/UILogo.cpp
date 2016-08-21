#include "stdafx.h"	
#include "UILogo.h"
#include "UILoading.h"
UILogo::UILogo() :UIDialog("UILogo/UILogo_1.ExportJson")
{

}
UILogo::~UILogo()
{
	
}
bool UILogo::initLayout()
{
	if (!UIDialog::initLayout())
	{
		return false;
	}
	GetObjectByName(&m_pImageLogo, "Image_Logo");
	CCFadeIn *LogoFadeIn = CCFadeIn::create(1.5f);
	CCFadeOut *LogoFadeOut = CCFadeOut::create(1.5f);
	CCAction *LogoAction = CCSequence::create(CCDelayTime::create(1.5f), LogoFadeIn, CCDelayTime::create(2.0f), LogoFadeOut, NULL);
	m_pImageLogo->runAction(LogoAction);
	scheduleOnce(SEL_SCHEDULE(&UILogo::update), 6.5f);
	//SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("Music/Bgmusic.wav");
	//if (CCUserDefault::sharedUserDefault()->getBoolForKey("Music", true))
	//{
	//	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Music/Bgmusic.MP3", true);
	//}

	return true;
}
void UILogo::update(float dt)
{
	CCScene *pNextScene = CCScene::create();
	pNextScene->addChild(UILoading::create());	
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.0f, pNextScene));
}