#include "Rocket.h"
#include "Entity/Planet.h"
#include "Effect/ParticleFire.h"
#include "Global/Global_Define.h"
Rocket::Rocket()
{
}
bool Rocket::initWithCCObject(CCObject* pObj)
{
	//------------------------------------------------------------------------
	_fsm = new RocketContext(*this);
	CCAssert(_fsm, "_fsm cannot be NULL");
	_fsm->setDebugFlag(true);
	_fsm->enterStartState();
	//------------------------------------------------------------------------
	m_rocketEntity = dynamic_cast<ui::UIImageView*>(pObj);
	if (!m_rocketEntity)
	{
		return NULL;
	}
	winSize = CCDirector::sharedDirector()->getVisibleSize();
	m_isBoost = false;
	m_sideMarker = CCPointZero;
	m_curVelocity = 300.0f;
	m_minVelocity = 150.0f;
	m_dead = false;
	m_onGoalPlanet = false;
	m_onGravity = false;
	m_radius = 80;
	m_energy = 100;
	m_elapsed = 0;
	m_onBlackHole = false;
	m_flyDirection = ccp(1.0f, 0.0f);
	m_onNoControl = false;
	m_actionOfBlackHoleIsOn = false;
	//CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Effect/Boom/Boom.ExportJson");
	//CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("victoryAnimation/star2.ExportJson");
	//添加关注者
	CCNotificationCenter::sharedNotificationCenter()->addObserver(
		this,
		callfuncO_selector(Rocket::rocketBoostOn),
		"TouchBegan",
		NULL
		);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(
		this,
		callfuncO_selector(Rocket::rocketBoostOff),
		"TouchEnded",
		NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(
		this,
		callfuncO_selector(Rocket::rocketBoostOff),
		"TouchCancelled",
		NULL);

	return true;
}
Rocket::~Rocket()
{
	onExit();
	delete _fsm;
	CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
}

Rocket* Rocket::createBy(CCObject* rocketEntity)
{
	Rocket *pobSprite = new Rocket();
	if (pobSprite && pobSprite->initWithCCObject(rocketEntity))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

void Rocket::intoGravity(Planet* planet)
{
	m_curPlanet = planet;
	m_sideMarker = CCPointZero;
	m_sptVelocity = m_curPlanet->getsptSpeed();
	m_minVelocity = m_curPlanet->getminRocketSpeed();
	m_onGravity = true;
	setDirection(m_curPlanet->getPosition());
	//------------calculate the arrivePoint
	CCPoint m_rocketEntityPos = m_rocketEntity->getPosition();
	CCPoint vecRTOP = m_curPlanet->getPosition()- m_rocketEntityPos;
	CCPoint point = vecRTOP.project(m_flyDirection);
	m_arrivePoint = ccpAdd(point, m_rocketEntityPos);
	m_radius = m_arrivePoint.getDistance(m_curPlanet->getPosition());
}

bool Rocket::checkArriveOn(CCPoint newPos)
{
	CCPoint vectorAPtoNextPos = m_arrivePoint - newPos;
	//biger than pi mean rocket through by the arrivePoint
	if (abs(abs(vectorAPtoNextPos.getAngle(m_flyDirection)) - 3.1415926) < 1e-03)
	{
		return true;
	}
	return false;
	
}

void Rocket::setDirection(CCPoint pPos)
{
	CCPoint vec = ccp(m_flyDirection.y, -m_flyDirection.x);
	CCPoint vecToP = ccpSub(pPos, m_rocketEntity->getPosition());
	if (vec.dot(vecToP) > 0)
	{
		m_direction = kClockwise;
	}
	else if (vec.dot(vecToP) < 0)
	{
		m_direction = kConter_clockwise;
	}
}

void Rocket::orbitCorrect()
{
	if (m_radius - m_curPlanet->getorbitRadius() <= -1)
	{
		m_radius += 0.1f;
	}
	else if (m_radius - m_curPlanet->getorbitRadius() >= 1)
	{
		m_radius -= 0.1f;
	}
}

void Rocket::setPosOnOrbit(float dt)
{
	float x, y;
	CCPoint pos = m_rocketEntity->getPosition();
	x = m_curPlanet->getPosition().x;
	y = m_curPlanet->getPosition().y;
	float preOmega = atan2f(pos.y - y, pos.x - x);
	float omegaBy = m_curVelocity / m_radius;

	float omegaTo = preOmega + m_direction*omegaBy / 60.0f;
	pos.x = m_radius*cosf(omegaTo) + x;
	pos.y = m_radius*sinf(omegaTo) + y;

	m_rocketEntity->setRotation(CC_RADIANS_TO_DEGREES(-omegaTo) - m_direction*90.0f);
	m_rocketEntity->setPosition(pos);
}


void Rocket::brake(float dt)
{
	if ((m_curVelocity - m_minVelocity) > 1)//速度大于分离速度
	{
		float brake = -1.5f;
		m_curVelocity += brake;
		return;
	}
	else if ((m_curVelocity - m_minVelocity) < -1)//如果减速过头了
	{
		m_curVelocity += 0.2f;
		return;
	}
	else//如果误差在-1到1之间直接等于最小速度
	{
		m_curVelocity = m_minVelocity;
		return;
	}
}

CCPoint Rocket::nextPosOnFly(float dt)
{
	m_flyDirection = CCPoint::forAngle(-CC_DEGREES_TO_RADIANS(getRotation()));
	CCPoint distance = m_flyDirection*m_curVelocity / 60.0f;
	CCPoint newPos;
	newPos.x = m_rocketEntity->getPosition().x + distance.x;
	newPos.y = m_rocketEntity->getPosition().y + distance.y;
	return newPos;
}

//Planet* Rocket::getCurPlanet()
//{
//	return m_curPlanet;
//}

//CCNode* Rocket::getEntity()
//{
//	return m_rocketEntity;
//}

float Rocket::getCurSpeed()
{
	return m_curVelocity;
}
//状态机的相关逻辑
void Rocket::exit()
{
	this->unscheduleAllSelectors();
}
void Rocket::orbit()
{
	this->schedule(schedule_selector(Rocket::onIdleOrbit));
}

void Rocket::navigate()
{
	this->schedule(schedule_selector(Rocket::onIdleNavigate));
}
void Rocket::boost()
{
	this->schedule(schedule_selector(Rocket::onIdleBoost));
}
void Rocket::separate()
{
	this->schedule(schedule_selector(Rocket::onIdleSeparate));
}
void Rocket::injection()
{
	this->schedule(SEL_SCHEDULE(&Rocket::onIdleInjection));
}

void Rocket::runningOut()
{
	this->schedule(SEL_SCHEDULE(&Rocket::onIdleRunningOut));
}
void Rocket::dead()
{
	this->setDead();
}


//状态机的相关逻辑结束
void Rocket::setBoost(bool enabled)
{
	m_isBoost = enabled;
}

int Rocket::getState()
{
	return _fsm->getState().getId();
}
//穿屏的相关逻辑
void Rocket::hitSide()
{
	CCPoint posN = m_rocketEntity->getPosition();
	if (posN.x + m_rocketEntity->getContentSize().height*m_rocketEntity->getScale() >= winSize.width)
	{
		m_sideMarker.x = 1;
		if (posN.x - m_rocketEntity->getContentSize().height*m_rocketEntity->getScale() >= winSize.width)
		{
			m_sideMarker.x = 0;
			m_rocketEntity->setPositionX(posN.x - winSize.width);
		}
	}
	else if (posN.x - m_rocketEntity->getContentSize().height*m_rocketEntity->getScale() <= 0)
	{
		m_sideMarker.x = -1;
		if (posN.x + m_rocketEntity->getContentSize().height*m_rocketEntity->getScale() <= 0)
		{
			m_sideMarker.x = 0;
			m_rocketEntity->setPositionX(posN.x + winSize.width);
		}
	}

	if (posN.y + m_rocketEntity->getContentSize().height*m_rocketEntity->getScale() >= winSize.height)
	{
		m_sideMarker.y = 1;
		if (posN.y - m_rocketEntity->getContentSize().height*m_rocketEntity->getScale() >= winSize.height)
		{
			m_sideMarker.y = 0;
			m_rocketEntity->setPositionY(posN.y - winSize.height);
		}
	}
	else if (posN.y - m_rocketEntity->getContentSize().height*m_rocketEntity->getScale() <= 0)
	{
		m_sideMarker.y = -1;
		if (posN.y + m_rocketEntity->getContentSize().height*m_rocketEntity->getScale() <= 0)
		{
			m_sideMarker.y = 0;
			m_rocketEntity->setPositionY(posN.y + winSize.height);
		}
	}
}

void Rocket::visit()
{
	m_rocketEntity->ui::UIImageView::visit();
	if (m_sideMarker.x != 0 || m_sideMarker.y != 0)
	{
		kmGLPushMatrix();
		if (m_sideMarker.x == 1)//右边出去
		{
			kmGLTranslatef(-winSize.width, 0, 0);
		}
		else if (m_sideMarker.x == -1)//左边出去
		{
			kmGLTranslatef(winSize.width, 0, 0);
		}
		if (m_sideMarker.y == 1)//上边出去
		{
			kmGLTranslatef(0, -winSize.height, 0);
		}
		else if (m_sideMarker.y == -1)//下边出去
		{
			kmGLTranslatef(0, winSize.height, 0);
		}
		m_rocketEntity->ui::UIImageView::visit();
		if (!m_dead)
		{
			_emitterFire->ParticleFire::visit();
		}
		kmGLPopMatrix();
	}
	if (!m_dead)
	{
		setFireOnRocket();

	}
}
//穿屏的相关逻辑结束
void Rocket::setDead()
{
	m_dead = true;
	onDead();
	CCNotificationCenter::sharedNotificationCenter()->postNotification("gameOver", (CCObject*)"lose");
}
void Rocket::setFireOnRocket()
{
	do 
	{
		CCPoint p = m_rocketEntity->getPosition();
		float s = m_rocketEntity->getContentSize().width*m_rocketEntity->getScale() / 2;
		CCPoint vec = CCPoint::forAngle(-CC_DEGREES_TO_RADIANS(m_rocketEntity->getRotation()));
		CCPoint pos = ccpSub(p, ccpMult(vec, s));
		_emitterFire->setPosition(pos);
		if (this->getState() == 1)
			_emitterFire->setBoostColor(true);
		else
			_emitterFire->setBoostColor(false);
	} while (false);
}

void Rocket::createFire()
{
	//effect
	_emitterFire = ParticleFire::create();
	_emitterFire->setPositionType(kCCPositionTypeRelative);
	this->getParent()->addChild(_emitterFire,-1);
}

void Rocket::rocketBoostOn(CCObject *pSender)
{
	if (!m_dead||!m_onNoControl)
	{
		m_isBoost = true;
	}
}

void Rocket::rocketBoostOff(CCObject *pSender)
{
	if (!m_dead||!m_onNoControl)
	{
		m_isBoost = false;
	}
}

void Rocket::onDead()
{
	CCArmature* boom = CCArmature::create("Boom");
	boom->getAnimation()->play("Animation1");
	boom->setPosition(m_rocketEntity->getPosition());
	boom->setScale(0.5f);
	this->getParent()->addChild(boom);
	_emitterFire->removeFromParent();
	m_rocketEntity->setVisible(false);
	if (CCUserDefault::sharedUserDefault()->getBoolForKey("isFXOn"))
	{
		SimpleAudioEngine::sharedEngine()->playEffect("FX/boom.wav");
	}
}

bool Rocket::isLeave()
{
	CCPoint rPos = getPosition();
	float d = rPos.getDistance(m_curPlanet->getPosition());
	return (d >= m_curPlanet->getgravityRadius()) ? true : false;
}

bool Rocket::isReachMax()
{
	return (m_isBoost&&m_curVelocity >= m_sptVelocity&&abs(m_radius - m_curPlanet->getgravityRadius()) <= 1.0f);
}

void Rocket::slowDown()
{
	if (m_curVelocity > 0)
	{
		m_curVelocity = MAX(0, m_curVelocity - m_curVelocity*0.01f);
		_emitterFire->setLife(MAX(0, _emitterFire->getLife() - 0.004f));
		_emitterFire->setLifeVar(MAX(0, _emitterFire->getLifeVar() - 0.002f));
		if (m_curVelocity <= 40.0f)
		{
			_fsm->fsmDead();
		}
	}
}
const CCPoint& Rocket::getPosition()
{
	return m_rocketEntity->getPosition();
}

void Rocket::setPosition(const CCPoint &pos)
{
	m_rocketEntity->setPosition(pos);
}

float Rocket::getScale()
{
	return m_rocketEntity->getScale();
}

void Rocket::setRotation(float fRotation)
{
	m_rocketEntity->setRotation(fRotation);
}

const CCSize& Rocket::getContentSize() const
{
    return m_rocketEntity->getContentSize();
}

float Rocket::getRotation()
{
	return m_rocketEntity->getRotation();
}

void Rocket::playActionOfBlackHole()
{
	if (!m_actionOfBlackHoleIsOn)
	{
		CCAction* action = CCSequence::create(CCScaleTo::create(0.5f, 0.0f), CCCallFunc::create(this,SEL_CallFunc(&Rocket::dead)), NULL);
		m_rocketEntity->runAction(action);
		m_actionOfBlackHoleIsOn = true;
		//if (CCUserDefault::sharedUserDefault()->getBoolForKey("isFXOn"))
		//{
		//	SimpleAudioEngine::sharedEngine()->playEffect("FX/beAbsorbed.wav");
		//}
	}
}

CCPoint Rocket::getVelocity()
{
	m_flyDirection = CCPoint::forAngle(m_rocketEntity->getRotation());
	return ccpMult(m_flyDirection, m_curVelocity);
}


void Rocket::pause()
{
	this->pauseSchedulerAndActions();
	if (!m_dead)
	{
		_emitterFire->pauseSchedulerAndActions();
	}
}
void Rocket::resume()
{
	this->resumeSchedulerAndActions();
	if (!m_dead)
	{
		_emitterFire->resumeSchedulerAndActions();
	}
}

void Rocket::addEnergy(float var)
{
	m_energy = MIN(100, m_energy + var);
}

void Rocket::onIdleOrbit(float dt)
{
	if (m_onBlackHole)//if rocket touch blackhole
	{
		m_onNoControl = true;
		if (m_radius>=0)
		{
			m_radius -= 2.0f;
		}
		if (m_curPlanet->isHitMe(this->getPosition())&&!m_actionOfBlackHoleIsOn)
		{
			this->playActionOfBlackHole();
		}
	}
	else if (m_isBoost)
	{
		_fsm->fsmBoost();
	}
	else
	{
		brake(dt);
		orbitCorrect();
	}
	setPosOnOrbit(dt);
}
void Rocket::onIdleBoost(float dt)
{
	if (!m_isBoost&&m_curVelocity < m_sptVelocity)
	{
		_fsm->fsmOrbit();
	}
	else if ((!m_isBoost&&m_curVelocity >= m_sptVelocity) || isReachMax())
	{
		m_sptVelocity = 0;
		m_onGravity = false;
		_fsm->fsmSeparate();
	}
	else if (!m_energy&&!m_onBlackHole)
	{
		CCAction* action = CCScaleBy::create(CLOSETODURATION, 2.0f);
		this->getParent()->runAction(action);
		_fsm->fsmRunningOut();
		if (CCUserDefault::sharedUserDefault()->getBoolForKey("isFXon"))
		{
			SimpleAudioEngine::sharedEngine()->playEffect("FX/runningOut.wav");
		}
	}

	if (m_isBoost&&abs(m_radius - m_curPlanet->getgravityRadius()) > 1.0f)
	{
		m_radius += 9.0f*dt;
	}
	m_energy = MAX(0.0f,(m_energy - 0.2f));
	m_curVelocity = MIN(900.0f, m_curVelocity += 2.0f);
	setPosOnOrbit(dt);
}

void Rocket::onIdleSeparate(float dt)
{
	if (isLeave())
	{
		_fsm->fsmNavigate();
	}
	brake(dt);
	m_rocketEntity->setPosition(nextPosOnFly(dt));
}

void Rocket::onIdleNavigate(float dt)
{
	if (m_onGravity)//碰撞检测的代码
	{
		_fsm->fsmInjection();
	}
	brake(dt);
	m_rocketEntity->setPosition(nextPosOnFly(dt));
	hitSide();
}

void Rocket::onIdleInjection(float dt)
{
	CCPoint newPos = nextPosOnFly(dt);
	if (m_curPlanet->isHitMe(m_rocketEntity->getPosition())&&!m_onBlackHole)
	{
		_fsm->fsmDead();
	}
	else if (checkArriveOn(newPos))
	{
		//injectTimeBeforeArrivePoint,injectTimeAffterArrivePoint
		float itb, ita;
		float dist = m_arrivePoint.getDistance(m_rocketEntity->getPosition());
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
			float omegaTo = preOmega + m_direction*omegaBy * ita;
			pos.x = m_radius*cosf(omegaTo) + x;
			pos.y = m_radius*sinf(omegaTo) + y;
			m_rocketEntity->setRotation(CC_RADIANS_TO_DEGREES(-omegaTo) - m_direction*90.0f);
			m_rocketEntity->setPosition(pos);
		}
		_fsm->fsmOrbit();
		if (m_onGoalPlanet)
		{
			m_onNoControl = true;
			CCArmature* animate = CCArmature::create("star2");
			animate->getAnimation()->play("Animation1");
			animate->setPosition(m_curPlanet->getPosition());
			animate->setScale(m_curPlanet->getScale()*RADIO_HALOANDPLANET);
			this->getParent()->addChild(animate);
			CCNotificationCenter::sharedNotificationCenter()->postNotification("gameOver", (CCObject*)"win");
			if (CCUserDefault::sharedUserDefault()->getBoolForKey("isFXOn"))
			{
				SimpleAudioEngine::sharedEngine()->playEffect("FX/arriveGoal.wav");
			}
		}
		return;
	}
	brake(dt);
	m_rocketEntity->setPosition(newPos);
}

void Rocket::onIdleRunningOut(float dt)
{
	CCPoint curPos = m_rocketEntity->getPosition();
	CCPoint newPos = curPos - curPos*this->getParent()->getScale();
	CCPoint distanceToCenter = ccp(320 - curPos.x, 480 - curPos.y);
	newPos = ccpAdd(newPos, distanceToCenter*m_elapsed);
	this->getParent()->setPosition(newPos);
	if (m_elapsed <= CLOSETODURATION)
		m_elapsed += dt;
	if (m_elapsed > CLOSETODURATION)
	{
		slowDown();
	}
	orbitCorrect();
	setPosOnOrbit(dt);
}
	return m_rocketEntity->getContentSize();
