/************************************************************************
*  Name: Stage.cpp
*  Purpose:
*  Author: Marskey
*  time: 2015-06-09	
*  version: 1.0
/************************************************************************/
#include "Entity/Stage.h"
Stage::Stage() 
{

}

Stage* Stage::createBy(ui::UIButton* btn)
{
	Stage* pRef = new Stage();
	if (pRef&&pRef->init(btn))
	{
		pRef->autorelease();
		return pRef;
	}
	CC_SAFE_DELETE(pRef);
	return NULL;
}

Stage::~Stage()
{

}

bool Stage::init(ui::UIButton* btn)
{
	_btn = btn;
	rotate();
	return true;
}
void Stage::reloadBy(int num)
{
	if (!num)
	{
		_stageNum = 0;
		_evaluation = -1;
		_btn->loadTextureNormal("Planet/empty.png");
	}
	else
	{
		_stageNum = num;
		int unlockNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("unlockNum",1);
		char tmp[30];
		sprintf(tmp, "stageEvaluation_%02d", num);
		_evaluation = CCUserDefault::sharedUserDefault()->getIntegerForKey(tmp,0);
		if (num <= unlockNum)
		{
			sprintf(tmp, "Planet/%dWithHalo.png", num);
			_btn->loadTextureNormal(tmp);
		}
		else if (num > unlockNum + 1)
		{
			_btn->loadTextureNormal("Planet/empty.png");
		}
		else 
			_btn->loadTextureNormal("Planet/0.png");
	}
}

const CCPoint& Stage::getPosition()
{
	return _btn->getPosition();
}

void Stage::setPosition(const CCPoint& pos)
{
	_btn->setPosition(pos);
}

void Stage::rotate()
{
	float rotSpeed = CCRANDOM_0_1()*(9 - 6) + 6;
	int sign;
	if (CCRANDOM_0_1() <= 0.5)
	{
		sign = -1;
	}
	else
		sign = 1;
	CCRotateBy *rotate = CCRotateBy::create(1.0f, rotSpeed*sign);
	CCAction *action = CCRepeatForever::create(rotate);
	_btn->runAction(action);
}