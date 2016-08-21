#include "stdafx.h"
#ifndef _CONFIG_H__
#define _CONFIG_H__
extern CCArray* collectionArr;
class Config:public CCObject
{
public:
	static	Config* getInstance();
private:
	Config();	
	~Config();
	static Config* _instance;
	std::vector<CCPoint> _planetPos;
public:
	CC_SYNTHESIZE(int, _stageNum, stageNum);
	CC_SYNTHESIZE(float, _timeCounter, time);
	CC_SYNTHESIZE(float, _evaluation, evaluation);

};
#endif //_CONFIG_H__