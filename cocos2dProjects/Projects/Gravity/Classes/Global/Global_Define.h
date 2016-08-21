#ifndef _Global_Define_H__
#define _Global_Define_H__

/* ----------SceneChange---------- */
#define SCENECHANGE(SceneName,time) {\
	CCScene *pScene=CCScene::create();\
	pScene->addChild(SceneName::create());\
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(time, pScene));\
}
#define  WINCREATE(UIWinName) {\
	CCScene *pWin = CCScene::create();\
	pWin->addChild(UIWinName::create());\
	CCDirector::sharedDirector()->pushScene(pWin);\
}
//------------------------------------------------------------------------random

/* ---------- ---------- */
#define PATH_BACKGROUND_00 "Background/background_00.png"
#define PATH_BACKGROUND_01 "Background/background_01.png"
#define PATH_BACKGROUND_02 "Background/background_02.png"
#define PATH_BACKGROUND_03 "Background/background_03.png"
#define PATH_BACKGROUND_04 "Background/background_04.png"
#define PATH_SETINGLAYER "UISetting/SettingPop.ExportJson"
#define PATH_PAUSELAYER "GameStop/GameStop.ExportJson"
#define PATH_UISTAGE "UIStageSelect/UIStageSelect_1.ExportJson"
#define PATH_OPTION "Option/Option_1.ExportJson"
/* ---------- ---------- */
#define CLOSETODURATION 1.0f
/* ---------- ---------- */
#define CSVPATH_PALENT "Data/planet/"
#define CSVPATH_STAGE "Data/stage/"
/* ---------- ---------- */
/* ------------------------ -----------------*/
#define RADIO_HALOANDPLANET 1.86f
#define MAXSTAGENUM 10
enum MyTag
{
	kRocketTag,
};
enum OrbitDir
{
	kClockwise = -1,
	kConter_clockwise = 1,
};
#endif// _Global_Define_H__