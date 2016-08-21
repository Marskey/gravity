/************************************************************************
*  Name: EnergyBag.cpp
*  Purpose:
*  Author: Marskey
*  time: 2015-05-30	
*  version: 1.0
/************************************************************************/
#include "Entity/EnergyBag.h"
#include "Config.h"
#include "Entity/Planet.h"
#include "Entity/BlackHole.h"
#include "Entity/Rocket.h"
EnergyBag* EnergyBag::create(std::vector<Planet*> *starList)
{
	EnergyBag* pRef = new EnergyBag();
	if (pRef&&pRef->initWithFile("Character/PowerBag.png"))
	{
		pRef->init(starList);
		pRef->autorelease();
		return pRef;
	}
	else
		CC_SAFE_DELETE(pRef);
	return NULL;
}

bool EnergyBag::init(std::vector<Planet*> *starList)
{
	cc_timeval tv;
	CCTime::gettimeofdayCocos2d(&tv, NULL);
	unsigned long reed = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	srand(reed);
	m_fLife = CCRANDOM_0_1()*(4-2)+2;//2µ½4
	m_starList = starList;
	m_accelerate = CCPointZero;
	m_isAbsorb = false;
	//------------------------------------------------------------------------
	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
	bool isFindPos = false;
	float x, y;
	do 
	{
		x = CCRANDOM_0_1()*(winSize.width-2*this->getContentSize().width*this->getScale())+this->getContentSize().width*this->getScale();
		y = CCRANDOM_0_1()*(winSize.height-2*this->getContentSize().height*this->getScale())+this->getContentSize().height*this->getScale();
		for (std::vector<Planet*>::iterator it = starList->begin(); it != starList->end();++it)
		{
			CCPoint pPos = (*it)->getPosition();
			float pRadius = (*it)->getgravityRadius();
			if (pPos.getDistance(ccp(x, y)) - pRadius > 0)
			{
				isFindPos = true;
			}
			else
			{
				isFindPos = false;
				break;
			}
		}

	} while (!isFindPos);
	this->setPosition(ccp(x, y));
	//------------------------------------------------------------------------
	float theta = CCRANDOM_0_1()*6.283185307;
	CCPoint	m_direc = ccp(cosf(theta), sinf(theta));
	m_velocity = m_direc * 150;

	scheduleUpdate();
	return true;
}
void EnergyBag::update(float delta)
{
	//m_fLife -= delta;
	if (m_fLife <= 0)
	{
		this->removeFromParent();
	}
	else
	{
		if (!m_isAbsorb)
		{
			hitRocket();
			hidSide();
			hidStar();
		}
		else
			absorbedByRocket();
		setNextPos(delta);
	}
}
void EnergyBag::setNextPos(float delta)
{
	CCPoint distance = ccpMult(m_velocity,1/60.0f);
	CCPoint newPos;
	newPos.x = this->getPosition().x + distance.x;
	newPos.y = this->getPosition().y + distance.y;
	this->setPosition(newPos);
}

void EnergyBag::hidSide()
{
	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint posN = this->getPosition();
	if (posN.x + this->getContentSize().width*this->getScale() / 2 >= winSize.width)//left
	{
		m_velocity.x = -m_velocity.x;
	}
	else if (posN.x - this->getContentSize().width*this->getScale() / 2 <= 0)//right
	{
		m_velocity.x = -m_velocity.x;
	}

	if (posN.y + this->getContentSize().height*this->getScale() / 2 >= winSize.height)//top
	{
		m_velocity.y = -m_velocity.y;
	}
	else if (posN.y - this->getContentSize().height*this->getScale() / 2 <= 0)//bottom
	{
		m_velocity.y = -m_velocity.y;
	}
}
void EnergyBag::hidStar()
{
	for (std::vector<Planet*>::iterator it = m_starList->begin(); it != m_starList->end();++it)
	{
			CCPoint pPos = (*it)->getPosition();
			CCPoint thisPos = this->getPosition();
			float pRadius = (*it)->getPlanetRadius();
			float distance = pPos.getDistance(thisPos);
			if (dynamic_cast<BlackHole*>(*it))
			{
				if (distance - pRadius < 0)
				{
					CCPoint adirec = (pPos - thisPos).normalize();
					m_accelerate = ccpMult(adirec, 150.0f*(pRadius-distance)/pRadius);
					m_velocity = ccpAdd(m_velocity, m_accelerate);
					this->setOpacity(255*(distance/pRadius));
					if (distance <= 30)
					{
						m_velocity = CCPointZero;
						m_fLife = 0;
					}
				}

			}else if (distance - pRadius <= this->getContentSize().width*this->getScale() / 2)
			{
				CCPoint bounce = ccpMult(-m_velocity.project(pPos - thisPos),2.0f);
				m_velocity = ccpAdd(m_velocity, bounce);
				break;
			}
		
	}
}

void EnergyBag::hitRocket()
{
	CCPoint pos = this->getParent()->getChildByTag(22)->getPosition();
	CCPoint thisPos = this->getPosition();
	float distance = pos.getDistance(thisPos);
	if (distance <= 120.0f)
	{
		m_isAbsorb = true;
	}
}

void EnergyBag::absorbedByRocket()
{
	Rocket* rocket = dynamic_cast<Rocket*>(this->getParent()->getChildByTag(22));
	CCPoint thisPos = this->getPosition();
	CCPoint rocketPos = rocket->getPosition();
	CCPoint closingVelocity = rocket->getVelocity() - m_velocity;
	float speedR = closingVelocity.getLength();
	float distance = rocketPos.getDistance(thisPos);
	float timeToClose = distance / closingVelocity.getLength();
	CCPoint rocketPosByTime = rocketPos + rocket->getVelocity()*timeToClose;
	CCPoint newDirection = (rocketPosByTime - thisPos).normalize();
	m_velocity = ccpMult(newDirection, m_velocity.getLength());
	m_accelerate = ccpMult(newDirection, 10.0f);
	m_velocity = ccpAdd(m_velocity, m_accelerate);
	m_isAbsorb = true;
	if (distance - 30 <= 0)
	{
		m_fLife = 0;
		rocket->addEnergy(10.0f);
	}

}