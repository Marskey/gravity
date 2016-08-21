#include "stdafx.h"
#ifndef _PLANET_H__
#define _PLANET_H__
#include "DBCSVService\DBCSVService.h"
class Planet :public CCNode 
{
public:
	Planet(CCObject* pStar);
	~Planet();
	bool init();
	bool isMeetMe(CCPoint curPos);
	virtual bool isHitMe(CCPoint rPos);
	void setProperties();
	void drawCircle();
	const virtual CCPoint& getPosition();
	virtual float getScale();
	float getPlanetRadius();
	void pause();
	void resume();
	CC_SYNTHESIZE(float, _orbitRadius, orbitRadius);
	CC_SYNTHESIZE(float, _rotationSpeed, rotationSpeed);
	CC_SYNTHESIZE(float, _sptSpeed, sptSpeed);
	CC_SYNTHESIZE(float, _gravityRadius, gravityRadius);
	CC_SYNTHESIZE(float, _minRocketSpeed, minRocketSpeed);
protected:
	ui::UIImageView* m_pPlanet;


protected:
	void rotate();
};
#endif//_PLANET_H__