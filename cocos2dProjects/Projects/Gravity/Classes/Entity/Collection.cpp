/************************************************************************
*  Name: Collection.cpp
*  Purpose:
*  Author: Marskey
*  time: 2015-06-12	
*  version: 1.0
/************************************************************************/

#include "Entity\Collection.h"
#include "Entity\Planet.h"
#include "Entity\Rocket.h"
#include "Global\Global_Define.h"
#include "Config.h"

Collection::Collection()
{

}
Collection::~Collection()
{

}
Collection* Collection::createBy(CCObject *pObj)
{
	Collection *pRef = new Collection();
	if (pRef&&pRef->initWithCCObject(pObj))
	{
		pRef->autorelease();
		return pRef;
	}
	CC_SAFE_DELETE(pRef);
	return NULL;
	
}

bool Collection::initWithCCObject(CCObject *pObj)
{
	//------------------------------------------------------------------------
	m_collectionEntity = NULL;
	m_rocket = NULL;
	m_collectionEntity = dynamic_cast<ui::UIImageView*>(pObj);
	if (!m_collectionEntity)
	{
		return false;
	}
	m_fsm = new CollectionContext(*this);
	CCAssert(m_fsm, "fsm cannot be NULL");
	m_fsm->setDebugFlag(true);
	m_fsm->enterStartState();
	m_curVelocity = 150.0f;
	m_isDead = false;
	m_isOnGravity = false;
	m_radius = 80;
	m_naviDir = ccp(1.0f, 0.0f);
	m_elapsed = 0;

	return true;
}

void Collection::orbit()
{
	this->schedule(SEL_SCHEDULE(&Collection::onStateOrbit));
}

void Collection::navigate()
{
	this->schedule(SEL_SCHEDULE(&Collection::onStateNavi));
}

void Collection::idle()
{
	this->schedule(SEL_SCHEDULE(&Collection::onStateIdle));
}

void Collection::dead()
{
	//play animation on absorbed by the rocket
	CCCallFunc *callFun = CCCallFunc::create(this,SEL_CallFunc(&Collection::removeThis));
	CCAction *action = CCSequence::create(CCSpawn::createWithTwoActions(CCScaleBy::create(0.4f, 6.0f), CCFadeTo::create(0.4f, 30.0f)),callFun,NULL);
	m_collectionEntity->runAction(action);
	
}

void Collection::injection()
{
	this->schedule(SEL_SCHEDULE(&Collection::onStateInject));
}

void Collection::exit()
{
	this->unscheduleAllSelectors();
}

void Collection::pause()
{
	this->pauseSchedulerAndActions();
}

void Collection::resume()
{
	this->resumeSchedulerAndActions();
}

bool Collection::isBeAbsorbed()
{
	CCPoint pos = m_rocket->getPosition();
	CCPoint thisPos = this->getPosition();
	float distance = pos.getDistance(thisPos);
	float radius = m_collectionEntity->getContentSize().width*m_collectionEntity->getScaleX();
	if (distance <= radius)
	{
		return true;
	}
	return false;
}

void Collection::setPosition(const CCPoint &pos)
{
	m_collectionEntity->setPosition(pos);
}

const CCPoint& Collection::getPosition()
{
	return m_collectionEntity->getPosition();
}

float Collection::getScale()
{
	return m_collectionEntity->getScaleX();
}

const CCSize& Collection::getContentSize()const
{
	return m_collectionEntity->getContentSize();
}

int Collection::getState()
{
	return m_fsm->getState().getId();
}

bool Collection::isDead()
{
	return m_isDead;
}

void Collection::intoGravity(Planet *planet)
{
	m_curPlanet = planet;
	m_isOnGravity = true;
	this->setOrbitDir(m_curPlanet->getPosition());
	//------------calculate the arrivePoint
	CCPoint m_collectionEntityPos = m_collectionEntity->getPosition();
	CCPoint vecRTOP = m_curPlanet->getPosition() - m_collectionEntityPos;
	CCPoint point = vecRTOP.project(m_naviDir);
	m_arrivePoint = ccpAdd(point, m_collectionEntityPos);
	m_radius = m_arrivePoint.getDistance(m_curPlanet->getPosition());
}

void Collection::setPosOnOrbit(float delta)
{
	float x, y;
	CCPoint pos = m_collectionEntity->getPosition();
	x = m_curPlanet->getPosition().x;
	y = m_curPlanet->getPosition().y;
	float preOmega = atan2f(pos.y - y, pos.x - x);
	float omegaBy = m_curVelocity / m_radius;

	float omegaTo = preOmega + m_orbitDir*omegaBy / 60.0f;
	pos.x = m_radius*cosf(omegaTo) + x;
	pos.y = m_radius*sinf(omegaTo) + y;

	m_collectionEntity->setRotation(CC_RADIANS_TO_DEGREES(-omegaTo) - m_orbitDir*90.0f);
	m_collectionEntity->setPosition(pos);
}

CCPoint Collection::nextPosOnNavi(float delta)
{
	m_naviDir = CCPoint::forAngle(-CC_DEGREES_TO_RADIANS(getRotation()));
	CCPoint distance = m_naviDir*m_curVelocity / 60.0f;
	CCPoint newPos;
	newPos.x = m_collectionEntity->getPosition().x + distance.x;
	newPos.y = m_collectionEntity->getPosition().y + distance.y;
	return newPos;
}

bool Collection::checkArriveOn(CCPoint pos)
{
	CCPoint vectorAPtoNextPos = m_arrivePoint - pos;
	if (abs(abs(vectorAPtoNextPos.getAngle(m_naviDir)) - 3.1415926) < 1e-03)
	{
		return true;
	}
	return false;
}

void Collection::setOrbitDir(CCPoint planetPos)
{
	CCPoint vec = ccp(m_naviDir.y, - m_naviDir.x);
	CCPoint vecToP = ccpSub(planetPos, m_collectionEntity->getPosition());
	if (vec.dot(vecToP) > 0)
	{
		m_orbitDir = kClockwise;
	}
	else if (vec.dot(vecToP) < 0)
	{
		m_orbitDir = kConter_clockwise;
	}
}

void Collection::onStateOrbit(float delta)
{
	if (isBeAbsorbed())
	{
		m_fsm->fsmDead();
		return;
	}
	setPosOnOrbit(delta);
}

void Collection::onStateNavi(float delta)
{
	if (m_rocket == NULL)
	{
		m_rocket = dynamic_cast<Rocket*>(this->getParent()->getChildByTag(kRocketTag));
	}
	if (m_collectionEntity->isTouchEnabled())
	{
		m_curVelocity = 0;
		m_collectionEntity->setTouchEnabled(false);
		m_fsm->fsmIdle();
		return;
	}
	if (m_isOnGravity)
	{
		m_fsm->fsmInjection();
	}
	m_collectionEntity->setPosition(nextPosOnNavi(delta));
}

void Collection::onStateInject(float delta)
{
	CCPoint newPos = nextPosOnNavi(delta);
	if (checkArriveOn(newPos))
	{
		//injectTimeBeforeArrivePoint,injectTimeAffterArrivePoint
		float itb, ita;
		float dist = m_arrivePoint.getDistance(m_collectionEntity->getPosition());
		if (dist >= 1.0f)
		{
			itb = dist / m_curVelocity;
			ita = 1 / 60.0f - itb;
			float x, y;
			x = m_curPlanet->getPosition().x;
			y = m_curPlanet->getPosition().y;
			float preOmega = atan2f(m_arrivePoint.y - y, m_arrivePoint.x - x);
			float omegaBy = m_curVelocity / m_radius;
			CCPoint pos;
			float omegaTo = preOmega + m_orbitDir*omegaBy * ita;
			pos.x = m_radius*cosf(omegaTo) + x;
			pos.y = m_radius*sinf(omegaTo) + y;
			m_collectionEntity->setRotation(CC_RADIANS_TO_DEGREES(-omegaTo) - m_orbitDir*90.0f);
			m_collectionEntity->setPosition(pos);
		}
		m_fsm->fsmOrbit();
		return;
	}
	m_collectionEntity->setPosition(newPos);
}

void Collection::onStateIdle(float delta)
{
	if (isBeAbsorbed())
	{
		m_fsm->fsmDead();
	}
	float preRotation = m_collectionEntity->getRotation();
	m_collectionEntity->setRotation(preRotation + 1.5f);
}

void Collection::removeThis()
{
	m_isDead = true;
	collectionArr->removeObject(this);
	this->removeFromParent();
	m_collectionEntity->removeFromParent();
	CCNotificationCenter::sharedNotificationCenter()->postNotification("addCoreNum",NULL);
	if (CCUserDefault::sharedUserDefault()->getBoolForKey("isFXOn"))
	{
		SimpleAudioEngine::sharedEngine()->playEffect("FX/collecting.wav");
	}
	
}