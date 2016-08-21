/************************************************************************
*  Name: EnergyBag.h
*  Purpose:
*  Author: Marskey
*  time: 2015-05-30	
*  version: 1.0
/************************************************************************/
#include "stdafx.h"
#ifndef HEADER__ENERGYBAG
#define HEADER__ENERGYBAG
class Planet;
class EnergyBag :public CCSprite
{
public:
	EnergyBag(){}
	~EnergyBag(){}
	static EnergyBag* create(std::vector<Planet*> *starList );
	bool init(std::vector<Planet*> *starList);
private:
	float m_fLife;
	CCPoint m_velocity;
	CCPoint m_accelerate;
	bool m_isAbsorb;
	std::vector<Planet*>* m_starList;
private:
	void setNextPos(float delta);
	void hitRocket();
	void update(float delta);
	void hidSide();
	void hidStar();
	void absorbedByRocket();
};
#endif // HEADER__ENERGYBAG