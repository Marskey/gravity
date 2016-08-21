#include "Planet.h"
Planet::Planet(CCObject* pStar)
{
	m_pPlanet = dynamic_cast<ui::UIImageView*>(pStar);
	this->init();
}
bool Planet::init()
{
	this->setProperties();
	rotate();
	return true;
}
Planet::~Planet()
{
	
}
void Planet::setProperties()
{
	const PlanetDB *data = DBCSVService::getInstance()->getPlanetRecordByName(m_pPlanet->getName());
	CCAssert(data, "canot get data from DBService");
	_orbitRadius = data->orbitRadius*m_pPlanet->getScaleX();
	_rotationSpeed = data->omega;
	_sptSpeed = data->sptVelocity;
	_gravityRadius = data->gravityRadius*m_pPlanet->getScaleX();
	_minRocketSpeed = data->minVelocity;
}
void Planet::rotate()
{
	CCRotateBy *rotate = CCRotateBy::create(1.0f, _rotationSpeed);
	CCAction *action = CCRepeatForever::create(rotate);
	m_pPlanet->runAction(action);
}
bool Planet::isMeetMe(CCPoint curPos)
{
	CCPoint pp = this->getPosition();
	float d = pp.getDistance(curPos);
	if (d <= _gravityRadius)
	{
		return true;
	}
	return false;
}
 
bool Planet::isHitMe(CCPoint rPos)
{
	CCPoint pPos = this->getPosition();
	float d = pPos.getDistance(rPos);
	if (d <= m_pPlanet->getContentSize().width*m_pPlanet->getScaleX() / 2)
	{
		return true;
	}	
	return false;
}
const CCPoint& Planet::getPosition()
{
	return m_pPlanet->getPosition();
}

float Planet::getScale()
{
	return m_pPlanet->getScaleX();
}

float Planet::getPlanetRadius()
{
	return m_pPlanet->getContentSize().width*m_pPlanet->getScaleX() / 2;
}

void Planet::pause()
{
	m_pPlanet->pauseSchedulerAndActions();
}
void Planet::resume()
{
	m_pPlanet->resumeSchedulerAndActions();
}
