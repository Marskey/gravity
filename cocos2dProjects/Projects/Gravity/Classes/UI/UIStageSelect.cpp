#include "UI/UIStageSelect.h"
#include "UI/UIMainMenu.h"
#include "Config.h"
#include "Global/Global_Define.h"
#include "DBCSVService/DBCSVService.h"
#include "GameScene.h"
#include "Effect/ParticleFire.h"
	//--------------radius-------------
#define _circleRadius  350
bool UIStageSelect::init()
{
	if (!UIDialog::initLayout())
	{
		return false;
	}
	_curStageNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("curStageNum", 1);//读取记录文件中的当前玩到的关卡。
	_unlockNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("unlockNum", 1);//读取记录文件中未解锁的关卡。
	_preDegree = -72.0f*(_curStageNum - 1);
	_isOnDraging = false;
	this->setTouchMode(kCCTouchesOneByOne);
	_distance = -_preDegree;
	//--------------------------------------------------------------------
	ui::UIButton* temp;
	GetObjectByName(&temp, "Button_1");
	_stageBall[0] = Stage::createBy(temp);
	GetObjectByName(&temp, "Button_2");
	_stageBall[1] = Stage::createBy(temp);
	GetObjectByName(&temp, "Button_3");
	_stageBall[2] = Stage::createBy(temp);
	GetObjectByName(&temp, "Button_4");
	_stageBall[3] = Stage::createBy(temp);
	GetObjectByName(&temp, "Button_5");
	_stageBall[4] = Stage::createBy(temp);
	GetObjectByName(&_indicator, "Image_indicator");
	GetObjectByName(&_scrollIndicator, "Image_verticalScrollIndicator");
	GetObjectByName(&_btnBack, "Button_back");
	GetObjectByName(&_LabelStageNum, "AtlasLabel_stageNum");

	//---------------------------------------------------------------------
	_btnBack->addTouchEventListener(this, ui::SEL_TouchEvent(&UIStageSelect::onTouchBack));
	CCSize scrollSize = _scrollIndicator->getContentSize();
	CCPoint scrollPos = _scrollIndicator->getPosition();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	_evaluationAnimation = CCArmature::create("evaluation");
	this->addChild(_evaluationAnimation,-1);
	_evaluationAnimation->setPosition(winSize / 2);
	//--------------------------------------------------------------
	CCSprite* pBackground = CCSprite::create(PATH_BACKGROUND_04);
	pBackground->setAnchorPoint(CCPointZero);
	this->addChild(pBackground, -2);
	
	_indicator->setPositionY(-_distance*1.3888888 + 450.0f);
	_scrollRect = CCRectMake(
		scrollPos.x - scrollSize.width / 2,
		scrollPos.y - scrollSize.height / 2,
		scrollSize.width,
		scrollSize.height
		);
	_isInScrollRect = false;
	//À˘”–µƒπÿø®‘⁄∂» ˝√ø¥Œ◊™π˝36+72*i∂»£¨ŒÂ∏ˆ«ÚÀ˘¥˙±Ìµƒπÿø®
	int arr[10][5]=
	{
		0, 0, 1, 2, 3,
		4, 0, 1, 2, 3,
		4, 5, 1, 2, 3,
		4, 5, 6, 2, 3,
		4, 5, 6, 7, 3,
		4, 5, 6, 7, 8,
		9, 5, 6, 7, 8,
		9, 10, 6, 7, 8,
		9, 10, 0, 7, 8,
		9, 10, 0, 0, 8,
	};
	memcpy(_arr, arr, sizeof(arr));
	//_arr.push_back(vector < int > { 0, 0, 1, 2, 3 });
	//_arr.push_back(vector < int > { 4, 0, 1, 2, 3 });
	//_arr.push_back(vector < int > { 4, 5, 1, 2, 3 });
	//_arr.push_back(vector < int > { 4, 5, 6, 2, 3 });
	//_arr.push_back(vector < int > { 4, 5, 6, 7, 3 });
	//_arr.push_back(vector < int > { 4, 5, 6, 7, 8 });
	//_arr.push_back(vector < int > { 9, 5, 6, 7, 8 });
	//_arr.push_back(vector < int > { 9, 10, 6, 7, 8 });
	//_arr.push_back(vector < int > { 9, 10, 0, 7, 8 });
	//_arr.push_back(vector < int > { 9, 10, 0, 0, 8 });
	//--------------radius-------------
	_ratioOfTouchDistToDegree = 72.0f / (_circleRadius*sinf(CC_DEGREES_TO_RADIANS(72.0f)));

	int no = (_distance + 36.0f) / 72.0f;
	for (int i = 0; i < 5; ++i)
	{
		_stageBall[i]->reloadBy(_arr[no][i]);
		float Sin = sinf(CC_DEGREES_TO_RADIANS(72.0f*i + 36.0f + _preDegree));
		float Cos = cosf(CC_DEGREES_TO_RADIANS(72.0f*i + 36.0f + _preDegree));
		_stageBall[i]->setPosition(ccp(Cos * _circleRadius * 0.5f + 320 + _circleRadius * 0.5f, Sin * _circleRadius + 480));
		_stageBall[i]->getEntity()->setScale(0.3f);
		if (_stageBall[i]->getstageNum()==_curStageNum)
		{
			_evaluationAnimation->setScale(0.3f);
			_stageBall[i]->getEntity()->setTouchEnabled(true);
			_frontBall = i;
			playAnimationOfEvaluation(true);
			animationForStageNum(true);
		}
		this->addChild(_stageBall[i]);
		_stageBall[i]->getEntity()->setOpacity((-Cos + 1) / 2 * 255);
		_stageBall[i]->getEntity()->setScale((-Cos + 1) / 2 * 0.3f);
		_stageBall[i]->getEntity()->addTouchEventListener(this, ui::SEL_TouchEvent(&UIStageSelect::onTouchStage));
	}
	char tmp[10];
	if (_curStageNum == _unlockNum + 1)
	{
		_LabelStageNum->setStringValue(":");
	}
	else
	{
		sprintf(tmp, "%d", _curStageNum);
		_LabelStageNum->setStringValue(tmp);
	}

	return true;
}

UIStageSelect::UIStageSelect() :UIDialog("UIStageSelect/UIStageSelect_1.ExportJson")
{

}


UIStageSelect::~UIStageSelect()
{

	CCUserDefault::sharedUserDefault()->setIntegerForKey("curStageNum", _curStageNum);
}

void UIStageSelect::onTouchStage(CCObject *pObject, ui::TouchEventType touchType)
{
	if (touchType == ui::TOUCH_EVENT_ENDED)
	{
		if (CCUserDefault::sharedUserDefault()->getBoolForKey("isFXOn"))
		{
			SimpleAudioEngine::sharedEngine()->playEffect("FX/buttonClick.wav");
		}
		if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
		{
			SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		}
		if (_curStageNum >_unlockNum)
		{
			return;
		}
        Config::getInstance()->setstageNum(_curStageNum);
		SCENECHANGE(GameScene, 1.0f);
	}
}

void UIStageSelect::onTouchBack(CCObject *pObject, ui::TouchEventType touchType)
{
	if (touchType == ui::TOUCH_EVENT_ENDED)
	{
		if (CCUserDefault::sharedUserDefault()->getBoolForKey("isFXOn"))
		{
			SimpleAudioEngine::sharedEngine()->playEffect("FX/buttonClick.wav");
		}
		SCENECHANGE(UIMainMenu, 1.0f);
	}
}

bool UIStageSelect::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	_touchPos = pTouch->getLocation();
	if (_scrollRect.containsPoint(_touchPos))
	{
		this->unscheduleAllSelectors();
		playAnimationOfEvaluation(_isOnDraging);
		animationForStageNum(_isOnDraging);
		_isInScrollRect = true;
		_isOnDraging = true;
		CCPoint relativePos = _scrollIndicator->convertToNodeSpace(_touchPos);
		_degreeOnIndicator = (-relativePos.y + 450)*0.72f;/*it is the radio of sinTheta multi Radius*/
		_degreeOnIndicator = _preDegree + _degreeOnIndicator;
		this->schedule(SEL_SCHEDULE(&UIStageSelect::scrollWhileTouchIndicator));
	}
	return true;
}
void UIStageSelect::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchDist = pTouch->getDelta();
	float degree = -touchDist.y;
	if (_isInScrollRect)
	{
		degree *= -0.72f / _scrollIndicator->getScaleX();
	}
	else
		degree *= _ratioOfTouchDistToDegree;
	if (-touchDist.y && rollBalls(degree))
	{
		playAnimationOfEvaluation(_isOnDraging);
		animationForStageNum(_isOnDraging);
		_isOnDraging = true;
	}
}
void UIStageSelect::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!_isInScrollRect)
	{
		_isOnDraging = false;

		bounceOnRoll();
	}
	_isInScrollRect = false;
}
void UIStageSelect::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
	ccTouchEnded(pTouch, pEvent);
}

bool UIStageSelect::rollBalls(float degree)
{
	if (_distance - degree < 0 || _distance - degree > MIN(_unlockNum*72.0f,648))
	{
		return false;
	}
	_distance -= degree;

	int no = (_distance + 36.0f) / 72.0f;
	for (int i = 0; i < 5; ++i)
	{
		if (_arr[no][i] != _stageBall[i]->getstageNum())
		{
			_stageBall[i]->reloadBy(_arr[no][i]);
		}
	}
	for (int i = 0; i < 5; ++i)
	{
		float Sin = sinf(CC_DEGREES_TO_RADIANS(72.0f*i +36.0f + _preDegree + degree));
		float Cos = cosf(CC_DEGREES_TO_RADIANS(72.0*i +36.0f + _preDegree + degree));
		_stageBall[i]->setPosition(ccp(Cos * _circleRadius / 2 + 320 + _circleRadius / 2, Sin * _circleRadius + 480));
		_stageBall[i]->getEntity()->setTouchEnabled(false);
		//setOpacity
		_stageBall[i]->getEntity()->setOpacity((-Cos + 1) / 2 * 255);
		_stageBall[i]->getEntity()->setScale((-Cos + 1) / 2 * 0.3f);
	}
	_preDegree += degree;
	_indicator->setPositionY(-_distance*1.3888888 + 450.0f);
	return true;
}

void UIStageSelect::bounceOnRoll()
{
	int turn = _preDegree / 72.0f;
	float offset = _preDegree - turn*72.0f;
	if (!offset)
	{
		return;
	}
	//for the bounceBack
	if (abs(offset) < 36.0f)
	{
		for (int i = 0; i < 5; ++i)
		{
			float Sin = sinf(CC_DEGREES_TO_RADIANS(72.0f*i + 36.0f + _preDegree - offset));
			float Cos = cosf(CC_DEGREES_TO_RADIANS(72.0*i + 36.0f + _preDegree - offset));
			if (abs(Sin) <= 1e-05)
			{
				_curStageNum = _stageBall[i]->getstageNum();
				_stageBall[i]->getEntity()->setTouchEnabled(true);
				_frontBall = i;
			}
			float y = Sin * _circleRadius + 480;
			CCAction *action = CCMoveTo::create(0.1f, ccp(Cos * _circleRadius / 2 + 320 + _circleRadius / 2, y));
			CCAction *action1 = CCScaleTo::create(0.1f,(-Cos + 1) / 2 * 0.3f);
			CCAction *action2 = CCFadeTo::create(0.1f, (-Cos + 1) / 2 * 255);
			_stageBall[i]->getEntity()->runAction(action);
			_stageBall[i]->getEntity()->runAction(action1);
			_stageBall[i]->getEntity()->runAction(action2);
		}
		_preDegree = _preDegree - offset;
		_distance = abs(_preDegree);
	}
	else if (abs(offset) >= 36.0f)
	{
		int n = _preDegree / abs(_preDegree);
		for (int i = 0; i < 5; ++i)
		{
			float Sin = sinf(CC_DEGREES_TO_RADIANS(72.0f*i + 36.0f + (turn + n)*72.0f));
			float Cos = cosf(CC_DEGREES_TO_RADIANS(72.0f*i + 36.0f + (turn + n)*72.0f));
			if (abs(Sin) <= 1e-05)
			{
				_curStageNum = _stageBall[i]->getstageNum();
				_stageBall[i]->getEntity()->setTouchEnabled(true);
				_frontBall = i;
			}
			float y = Sin * _circleRadius + 480;
			CCAction *action = CCMoveTo::create(0.1f, ccp(Cos * _circleRadius / 2 + 320 + _circleRadius / 2, y));
			CCAction *action1 = CCScaleTo::create(0.1f,(-Cos + 1) / 2 * 0.3f);
			CCAction *action2 = CCFadeTo::create(0.1f, (-Cos + 1) / 2 * 255);
			_stageBall[i]->getEntity()->runAction(action);
			_stageBall[i]->getEntity()->runAction(action1);
			_stageBall[i]->getEntity()->runAction(action2);
		}
		_preDegree = 72.0f*(turn + n);
		_distance = abs(_preDegree);
	}
	CCAction *action3 = CCMoveTo::create(0.1f, ccp(_indicator->getPositionX(), -_distance*1.3888888 + 450.0f));
	char tmp[10];
	if (_curStageNum == _unlockNum + 1)
	{
		_LabelStageNum->setStringValue(":");
	}
	else
	{
		sprintf(tmp, "%d", _curStageNum);
		_LabelStageNum->setStringValue(tmp);
	}
	animationForStageNum(true);
	_indicator->runAction(action3);
	playAnimationOfEvaluation(true);
	//bounceBack end
}

void UIStageSelect::scrollWhileTouchIndicator(float delta)
{
	float degree = 12.0f;
	if (abs(_degreeOnIndicator) < degree / 2.0f)
	{
		this->unscheduleAllSelectors();
		if (!_isInScrollRect)
		{
			_isOnDraging = false;
			bounceOnRoll();
		}
		_degreeOnIndicator = 0;
		return;
	}
	if (_degreeOnIndicator > 0)
	{
		degree = -degree;
	}
	_degreeOnIndicator += degree;
	rollBalls(degree);
}

void UIStageSelect::playAnimationOfEvaluation(bool var)
{
	if (!_isOnDraging)
	{
		int evaluation = _stageBall[_frontBall]->getevaluation();
		if (evaluation)
		{
			if (var)
			{
				_evaluationAnimation->getAnimation()->playWithIndex(evaluation - 1);
			}
			else
				_evaluationAnimation->getAnimation()->playWithIndex(evaluation + 2);
		}
	}
}

void UIStageSelect::animationForStageNum(bool var)
{
	if (!_isOnDraging)
	{
		_LabelStageNum->stopAllActions();
		CCAction* action;
		if (var)
		{
			action = CCSequence::create(
				CCSpawn::createWithTwoActions(CCScaleTo::create(0.2f, 1.2f), CCFadeIn::create(0.2f)),
				CCScaleTo::create(0.1f, 0.8f),
				CCScaleTo::create(0.05f, 1.0f),
				NULL
				);
		}
		else
		{
				
			action = CCSpawn::createWithTwoActions(CCScaleTo::create(0.05f, 0.0f), CCFadeOut::create(0.05f));
		}
		_LabelStageNum->runAction(action);
	}
}