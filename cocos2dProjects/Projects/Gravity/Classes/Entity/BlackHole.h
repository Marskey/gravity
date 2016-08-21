#include "stdafx.h"
#ifndef _BlackHole_H__
#define _BlackHole_H__
#include "Entity/Planet.h"
class BlackHole :public Planet
{
public:
	BlackHole(CCObject* pStar);
	~BlackHole();
	virtual bool isHitMe(CCPoint rPos);
	//bool init();
private:	
	ui::UIImageView* _pBlackHole;
};
#endif// _BlackHole_H__