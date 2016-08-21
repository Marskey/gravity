/************************************************************************
*  Name: Stage.h
*  Purpose:
*  Author: Marskey
*  time: 2015-06-09	
*  version: 1.0
/************************************************************************/
#include "stdafx.h"
#ifndef HEADER__STAGE
#define HEADER__STAGE
#include "DBCSVService/DBCSVService.h"

class Stage :public CCNode 
{
public:
	Stage();
	~Stage();
	bool init(ui::UIButton* btn);
	static Stage* createBy(ui::UIButton* btn);
	void reloadBy(int num);
	virtual const CCPoint& getPosition();
	virtual void setPosition(const CCPoint& pos);
	CC_SYNTHESIZE(int, _stageNum, stageNum);
	CC_SYNTHESIZE(int, _evaluation, evaluation);
	ui::UIButton* getEntity(){ return _btn; }
private:	
	ui::UIButton* _btn;
private: 
	void rotate();

};
#endif // HEADER__STAGE