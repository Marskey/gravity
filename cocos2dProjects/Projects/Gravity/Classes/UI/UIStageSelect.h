/************************************************************************
*  Name: UIStageSelect.h
*  Purpose:
*  Author: Marskey
*  time: 2015-06-09	
*  version: 1.0
/************************************************************************/
#include "stdafx.h"
#ifndef HEADER__UISTAGESELECT
#define HEADER__UISTAGESELECT
#include "UIDialog.h"
#include "Entity/Stage.h"
class ParticleFire;
class UIStageSelect :public UIDialog
{
public:
	UIStageSelect();
	~UIStageSelect();
	bool init();
	void update();
	CREATE_FUNC(UIStageSelect);
//data
private:
	//std::vector<std::vector<int> > _arr;
	int _arr[10][5];
	CCRect _scrollRect;
	CCPoint _touchPos;
	bool _isInScrollRect;
	float _ratioOfTouchDistToDegree;
	int _curStageNum;
	float _distance;
	float _preDegree;
	float _degreeOnIndicator;
	int _frontBall;
	bool _isOnDraging;
	int _unlockNum;
//widget:
private:
	ui::UIImageView *_indicator;
	ui::UIImageView* _scrollIndicator;
	ui::UIButton *_btnBack;
	ui::UILabelAtlas *_LabelStageNum;
	CCArmature* _evaluationAnimation;
	Stage* _stageBall[10];

private:
	bool rollBalls(float degree);
	void bounceOnRoll();
	void onTouchStage(CCObject *pObject, ui::TouchEventType touchType);
	void onTouchBack(CCObject *pObject, ui::TouchEventType touchType);
	void scrollWhileTouchIndicator(float delta);
	void animationForStageNum(bool var/*true for in,false for out*/);
	/*play out when var is true , play in when var is false.*/
	void playAnimationOfEvaluation(bool var);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
};
#endif // HEADER__UISTAGESELECT