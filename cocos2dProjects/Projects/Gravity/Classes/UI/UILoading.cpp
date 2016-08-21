#include "UI\UILoading.h"
#include "DBCSVService\DBCSVService.h"
#include "Global\Global_Define.h"
#include "UI\UIMainMenu.h"
UILoading::UILoading() :UIDialog("UILoading/UILoading_1.ExportJson")
{

}

bool UILoading::init()
{
	if (!UIDialog::initLayout())
	{
		return false;
	}
	if (load())
	{
		return true;
	}
	return false;
}

bool UILoading::load()
{
	m_numberOfLoadedResources = 0;
	m_numberOfResources = 51;
	GetObjectByName(&m_pProgressPercent, "AtlasLabel_progressPercent");
	GetObjectByName(&m_pProgressBar, "ProgressBar_loading");
	//------------------------------------------------------------------------Aniamtion:8
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(
		"Rocket/NewAnimation.ExportJson",
		this,
		SEL_SCHEDULE(&UILoading::loadingCallBack)
		);
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(
		"Star/Star.ExportJson",
		this,
		SEL_SCHEDULE(&UILoading::loadingCallBack)
		);
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(
		"starVictory/star.ExportJson",
		this,
		SEL_SCHEDULE(&UILoading::loadingCallBack)
		);
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(
		"round/round.ExportJson",
		this,
		SEL_SCHEDULE(&UILoading::loadingCallBack)
		);
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(
		"Halo/Halo.ExportJson",
		this,
		SEL_SCHEDULE(&UILoading::loadingCallBack)
		);
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(
		"Effect/Boom/Boom.ExportJson",
		this,
		SEL_SCHEDULE(&UILoading::loadingCallBack)
		);
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(
		"victoryAnimation/star2.ExportJson",
		this,
		SEL_SCHEDULE(&UILoading::loadingCallBack)
		);
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(
		"evaluationAnimation/evaluation.ExportJson",
		this,
		SEL_SCHEDULE(&UILoading::loadingCallBack)
		);
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(
		"textAnimation/textAnimation.ExportJson",
		this,
		SEL_SCHEDULE(&UILoading::loadingCallBack)
		);
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(
		"redHaloAnimation/redHaloAnimation.ExportJson",
		this,
		SEL_SCHEDULE(&UILoading::loadingCallBack)
		);

	//------------------------------------------------------------------------Image: 32 
    CCTextureCache::sharedTextureCache()->addImageAsync(
		"Background/background_00.png",
		this, 
		callfuncO_selector(UILoading::loadingCallBack)
		);
    CCTextureCache::sharedTextureCache()->addImageAsync(
		"Background/background_01.png",
		this, 
		callfuncO_selector(UILoading::loadingCallBack)
		);
    CCTextureCache::sharedTextureCache()->addImageAsync(
		"Background/background_02.png",
		this, 
		callfuncO_selector(UILoading::loadingCallBack)
		);
    CCTextureCache::sharedTextureCache()->addImageAsync(
		"Number_png/number.png",
		this, 
		callfuncO_selector(UILoading::loadingCallBack)
		);
	CCTextureCache::sharedTextureCache()->addImageAsync(
		"Planet/0.png",
		this,
		callfuncO_selector(UILoading::loadingCallBack)
        );

	char tmp[30];
	for (int i = 1; i <= 10; ++i)
	{
		sprintf(tmp, "Planet/%dWithHalo.png", i);
		CCTextureCache::sharedTextureCache()->addImageAsync(
			tmp,
			this,
			callfuncO_selector(UILoading::loadingCallBack)
			);
	}
	CCTextureCache::sharedTextureCache()->addImageAsync(
		"Planet/empty.png",
		this,
		callfuncO_selector(UILoading::loadingCallBack)
		);
	CCTextureCache::sharedTextureCache()->addImageAsync(
		"About/Option0.png",
		this, 
		callfuncO_selector(UILoading::loadingCallBack)
		);
    CCTextureCache::sharedTextureCache()->addImageAsync(
		"Effect/fire.png",
		this, 
		callfuncO_selector(UILoading::loadingCallBack)
		);
    CCTextureCache::sharedTextureCache()->addImageAsync(
		"GameStop/GameStop_20.png",
		this, 
		callfuncO_selector(UILoading::loadingCallBack)
		);
    CCTextureCache::sharedTextureCache()->addImageAsync(
		"GameStop/GameStop_21.png",
		this, 
		callfuncO_selector(UILoading::loadingCallBack)
		);
    CCTextureCache::sharedTextureCache()->addImageAsync(
		"GameUi/GameUi0.png",
		this, 
		callfuncO_selector(UILoading::loadingCallBack)
		);
    CCTextureCache::sharedTextureCache()->addImageAsync(
		"GameUi/labelatlasimg_1.png",
		this, 
		callfuncO_selector(UILoading::loadingCallBack)
		);
    CCTextureCache::sharedTextureCache()->addImageAsync(
		"MainMenu/MainMenu0.png",
		this, 
		callfuncO_selector(UILoading::loadingCallBack)
		);
    CCTextureCache::sharedTextureCache()->addImageAsync(
		"MainMenu/MainMenu1.png",
		this, 
		callfuncO_selector(UILoading::loadingCallBack)
		);
    CCTextureCache::sharedTextureCache()->addImageAsync(
		"UISetting/SET_20.png",
		this, 
		callfuncO_selector(UILoading::loadingCallBack)
		);
    CCTextureCache::sharedTextureCache()->addImageAsync(
		"UIGameOver/UIGameOver0.png",
		this, 
		callfuncO_selector(UILoading::loadingCallBack)
		);
    CCTextureCache::sharedTextureCache()->addImageAsync(
		"UIGameOver/UIGameOver1.png",
		this, 
		callfuncO_selector(UILoading::loadingCallBack)
		);
    CCTextureCache::sharedTextureCache()->addImageAsync(
		"UIGameOver/UIGameOver2.png",
		this, 
		callfuncO_selector(UILoading::loadingCallBack)
		);
    CCTextureCache::sharedTextureCache()->addImageAsync(
		"UIStageSelect/UIStageSelect0.png",
		this, 
		callfuncO_selector(UILoading::loadingCallBack)
		);
    CCTextureCache::sharedTextureCache()->addImageAsync(
		"UIVictory/UIVictory0.png",
		this, 
		callfuncO_selector(UILoading::loadingCallBack)
		);
    CCTextureCache::sharedTextureCache()->addImageAsync(
		"UIVictory/UIVictory1.png",
		this, 
		callfuncO_selector(UILoading::loadingCallBack)
        );
	//------------------------------------------------------------------------Music: 2
	//SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(
	//	"Music/GameLayerBgm.wav"
	//	);
	//SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(
	//	"Music/MainMenuBgm.wav"
 //       );
	//------------------------------------------------------------------------Fx: 9
	SimpleAudioEngine::sharedEngine()->preloadEffect(
		"FX/arriveGoal.wav"
        );
	SimpleAudioEngine::sharedEngine()->preloadEffect(
		"FX/boom.wav"
        );
	SimpleAudioEngine::sharedEngine()->preloadEffect(
		"FX/buttonClick.wav"
        );
	SimpleAudioEngine::sharedEngine()->preloadEffect(
		"FX/collecting.wav"
		);
	SimpleAudioEngine::sharedEngine()->preloadEffect(
		"FX/gameOver.wav"
		);
	SimpleAudioEngine::sharedEngine()->preloadEffect(
		"FX/runningOut.wav"
		);
	SimpleAudioEngine::sharedEngine()->preloadEffect(
		"FX/starOut.wav"
		);
	SimpleAudioEngine::sharedEngine()->preloadEffect(
		"FX/victory.wav"
        );
	//------------------------------------------------------------------------Data: 1
	DBCSVService::getInstance();
	m_numberOfLoadedResources += 10;
	return true;
}

void UILoading::loadingCallBack(cocos2d::CCObject *obj)
{
    ++m_numberOfLoadedResources;
    char tmp[10];
	int percent = (int)(((float)m_numberOfLoadedResources / m_numberOfResources) * 100);
	sprintf(tmp, "%02d", percent);
    m_pProgressPercent->setStringValue(tmp);
	m_pProgressBar->setPercent(percent);
    if (m_numberOfResources == m_numberOfLoadedResources)
    {
		SCENECHANGE(UIMainMenu, 0.5f);
    }
}

void UILoading::loadingCallBack(float delta)
{
    ++m_numberOfLoadedResources;
    char tmp[10];
	int percent = (int)(((float)m_numberOfLoadedResources / m_numberOfResources) * 100);
	sprintf(tmp, "%02d", percent);
    m_pProgressPercent->setStringValue(tmp);
	m_pProgressBar->setPercent(percent);
    if (m_numberOfResources == m_numberOfLoadedResources)
    {
		SCENECHANGE(UIMainMenu, 0.5f);
    }
}