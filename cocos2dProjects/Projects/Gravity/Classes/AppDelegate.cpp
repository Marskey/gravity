#include "stdafx.h"
#include "AppDelegate.h"
//#include "GameScene.h"
//#include "UI\UIMainMenu.h"
#include "UI\UILogo.h"
//#include "UI\UIStageSelect.h"
//#include "UI\UILoading.h"

// window detail
#define DEFAULT_WINDOW_WIDTH (640)
#define DEFAULT_WINDOW_HEIGHT (960)

#define MIN_WINDOW_WIDTH (640)
#define MIN_WINDOW_HEIGHT (960)

#define MAX_WINDOW_WIDTH (640)
#define MAX_WINDOW_HEIGHT (960)
AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
	// setting the screen scale
	CCSize designSize = CCSizeMake(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
	//CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();

	////size for ios
	//int width, height;
	//if (screenSize.width<screenSize.height)
	//{
	//	width = screenSize.width;
	//	height = screenSize.height;
	//}
	//else
	//{
	//	width = screenSize.height;
	//	height = screenSize.width;
	//}
	//CCLog("%d", width);
	//float scale = 1.0;
	//if (width > MAX_WINDOW_WIDTH || height > MAX_WINDOW_HEIGHT)
	//{
	//	scale = (designSize.width / width, designSize.height / height);
	//	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(width * scale, height * scale, kResolutionNoBorder);
	//}
	//else if (width < MIN_WINDOW_WIDTH || height < MIN_WINDOW_HEIGHT)
	//{
	//	scale = max(designSize.width / width, designSize.height / height);
	//	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(width * scale, height * scale, kResolutionNoBorder);
	//}
	//size for Andriod
	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionShowAll);
    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
	CCScene *pScene = CCScene::create();
	pScene->addChild(UILogo::create());
    
    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
