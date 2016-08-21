/************************************************************************
*  Name: Collection.h
*  Purpose:
*  Author: Marskey
*  time: 2015-06-12	
*  version: 1.0
/************************************************************************/
#include "stdafx.h"
#ifndef HEADER__COLLECTION
#define HEADER__COLLECTION
#include "Entity\Collection_sm.h"
class Planet;
class Rocket;
class Collection :public CCNode 
{
private:
	ui::UIImageView* m_collectionEntity;
	Rocket *m_rocket;
private:
	int m_orbitDir;
	//fsm here
	CollectionContext *m_fsm;
	CCPoint m_naviDir;
	bool m_isOnGravity;
	bool m_isDead;
	CCPoint m_arrivePoint;
	float m_elapsed;
	Planet *m_curPlanet;
	//CCSize winSize;
	//bool m_onBlackHole;
	//bool m_actionOfBlackHoleIsOnRunning;
	//CCPoint m_sideMarker;

private:
	float m_radius;
	float m_curVelocity;
	//float m_minVelocity;
	//float m_maxVelocity;

	
public:
	Collection();
	~Collection();
	bool initWithCCObject(CCObject *pObj);
	static Collection* createBy(CCObject* pObj);
	//----------------------------------------FSM
	void orbit();
	void navigate();
	void idle();
	void dead();
	void injection();
	void exit();
	//----------------------------------------FSM End
	void pause();
	void resume();
	bool isBeAbsorbed();
	void intoGravity(Planet *planet);
	virtual void setPosition(const CCPoint &pos);
	virtual const CCPoint& getPosition();
	virtual float getScale();
	virtual const CCSize& getContentSize() const;
	int getState();
	bool isDead();

private:
	void setPosOnOrbit(float delta);
	CCPoint nextPosOnNavi(float delta);
	bool checkArriveOn(CCPoint pos);
	void setOrbitDir(CCPoint planetPos);
	void removeThis();

private:
	void onStateOrbit(float delta);
	void onStateNavi(float delta);
	void onStateInject(float delta);
	void onStateIdle(float delta);





};
#endif // HEADER__COLLECTION