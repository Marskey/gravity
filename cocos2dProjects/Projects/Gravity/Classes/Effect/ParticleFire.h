#include "stdafx.h"
#ifndef _ParticleFire_H__
#define _ParticleFire_H__
class ParticleFire :public CCParticleSystemQuad
{
public:
	static ParticleFire* create();
	ParticleFire(){}	
	virtual ~ParticleFire(){}
	bool init(){ return initWithTotalParticles(300); }
	virtual bool initWithTotalParticles(unsigned int numberOfParticles);
	void setBoostColor(bool enabled);
private:
	//CC_DISALLOW_COPY_AND_ASSIGN
};
#endif //_ParticleFire_H__