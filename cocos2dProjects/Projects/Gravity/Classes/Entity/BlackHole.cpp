#include "Entity/BlackHole.h"

BlackHole::BlackHole(CCObject* pStar) :Planet(pStar)
{

}
BlackHole::~BlackHole()
{

}
bool BlackHole::isHitMe(CCPoint rPos)
{
	CCPoint bPos = this->getPosition();
	float d = bPos.getDistance(rPos);
	if (d<=m_pPlanet->getScale()*65.0f)
	{
		return true;
	}
	return false;
}