#include "stdafx.h"
#ifndef _ROCKET_H__
#define _ROCKET_H__
#include "Entity\Rocket.h"
#include "Global\Global_Define.h"
#include "Entity\Rocket_sm.h"
class Planet;
class ParticleFire;
class Rocket  :public CCNode 
{
private:
	ui::UIImageView* m_rocketEntity;
public:
	Rocket();
	 ~Rocket();
	bool initWithCCObject(CCObject* pObj);
	static Rocket* createBy(CCObject* rocketEntity);
	void intoGravity(Planet* planet);
//环绕
	void setPosOnOrbit(float dt);
	void orbit();
//加速
	void boost();
//航行 
	void navigate();
	void separate();
	void dead();
	void injection();
	void runningOut();
	void exit();

	void createFire();
	void pause();
	bool isDead(){ return m_dead; }
	void resume();
	int getState();
	void setDead();
	void addEnergy(float var);
	CCPoint getVelocity();
	CCPoint nextPosOnFly(float dt);
	void playActionOfBlackHole();
	void setOnBlackHole(bool var){ m_onBlackHole = var; }
	void setOnGoalPlanet(bool var){ m_onGoalPlanet = var; }
	float getEnergy(){ return m_energy; }
	float getCurSpeed();
	//Planet* getCurPlanet();
	//CCNode* getEntity();
	//------------------------------------------------------------------------
	virtual void setPosition(const CCPoint &pos);
	virtual const CCPoint& getPosition();
	virtual float getScale();
	virtual void setRotation(float fRotation);
	virtual const CCSize& getContentSize() const;
	virtual float getRotation();
//状态
private:
	int m_direction;//-1 clockwise ,1 conter-clockwise
	RocketContext* _fsm;//状态机类对象的创建
	CCPoint m_flyDirection; //火箭飞行时的方向
	bool m_isBoost;
	bool m_onGravity;
	CCSize winSize;
	bool m_dead;
	bool m_onBlackHole;
	bool m_actionOfBlackHoleIsOn;
	CCPoint m_arrivePoint;
	bool m_onGoalPlanet;
	bool m_onNoControl;
	float m_elapsed;

/*********************************************
*@sideMarker x,y有1、-1 和0  
*          +1
*   +------------+
*   |            |
*   |            | +1
*   |            |
* -1|   (0,0)    |
*   |            |
*   |            |
*   +------------+
*          -1
*
*********************************************/
	CCPoint m_sideMarker;

//属性
private:
	float m_radius;//轨道半径
	float m_curVelocity;//火箭速度
	float m_minVelocity;
	float m_maxVelocity;
	float m_sptVelocity;//火箭脱离星球速度
	float m_energy;//火箭能量
//其他对象
private:
    //effect 
	ParticleFire *_emitterFire;
	Planet* m_curPlanet; //所在星球

//内部函数
private:
	bool isReachMax();
	void orbitCorrect();
	//检测是否碰到边界
	void rocketBoostOn(CCObject *pSender);
	void rocketBoostOff(CCObject *pSender);
	void hitSide();
	inline void setFireOnRocket();
	virtual void visit();
	bool isLeave();
	void onDead();
	void slowDown();
	void setBoost(bool enabled);
	void setDirection(CCPoint pPos);
	bool checkArriveOn(CCPoint newPos);
	void brake(float dt);
//状态机函数
	void onIdleOrbit(float dt);
	void onIdleBoost(float dt);
	void onIdleNavigate(float dt);	
	void onIdleSeparate(float dt);
	void onIdleInjection(float dt);
	void onIdleRunningOut(float dt);

};
#endif //_ROCKET_H__