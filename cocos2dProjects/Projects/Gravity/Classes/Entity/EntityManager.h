#include "stdafx.h"
#ifndef _ENTITIYMANAGER_H__
#define _ENTITIYMANAGER_H__
#include "Entity\Rocket.h"
#include "Entity\Planet.h"
#include "Entity\BlackHole.h"
#include "Entity\Collection.h"
//#include "Entity\EnergyBag.h"

class EntityManager :public CCNode
{
public:
	EntityManager();
	~EntityManager();
	static EntityManager* createWithLevel(int curLevel);
	bool initWithLevel(int curLevel);
	float getRocketEnergy(){ return _pRocket->getEnergy(); }
	void update(float dt);
	void pause();
	void resume();
	
	void setCameraClose();
	void setCameraFar();
//≥…‘±
private:
	std::vector<Planet*> _starList;
	std::vector<CCPoint> _starPosList;
	//std::vector<EnergyBag*> m_bagList;
	Rocket* _pRocket;
	//CCArray *_collectionArr;
	ParticleFire *_emitterFire;
	unsigned int _goalPlanetID;
	bool isCameraMove;
	float m_elapsed;//time
private:
	inline void resetElapsion();
	void rocketBoostOn(float dt);
	void rocketBoostOff(float dt);
	void createSrand();
	void createRocket();
	void createMapWithLevel(int curLevel);
	void createPowerBag(int num);
	void createHalo();
//foreach planet
	void checkMeetWithStar(float dt);
	void collectionMeetWithStar(float dt);
//do more
	//void checkMeetWithBlackHole(float dt);
};
#endif // _ENTITIYMANAGER_H__