#include "ParticleFire.h"

ParticleFire* ParticleFire::create()
{
	ParticleFire* ret = new (std::nothrow) ParticleFire();
	if (ret && ret->init())
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}
bool ParticleFire::initWithTotalParticles(unsigned int numberOfParticles)
{
	if (CCParticleSystemQuad::initWithTotalParticles(numberOfParticles))
	{
		// additive
		this->setBlendAdditive(true);
		
		// duration
		m_fDuration = kCCParticleDurationInfinity;

		// Gravity Mode 
		setEmitterMode(kCCParticleModeGravity);

		// Gravity Mode: gravity
		setGravity(ccp(0, 0));

		// Gravity Mode: radial acceleration
		setRadialAccel(0);
		setRadialAccelVar(0);

		// Gravity mode: speed of Particles
		setSpeed(0.0f);
		setSpeedVar(0);

		// angle
		m_fAngle = 180;
		m_fAngleVar = 0;

		// Emitter Position
		this->setPosition(CCPointZero);
		setPosVar(CCPointZero);

		// Life of Particles 
		m_fLife = 0.3f;
		m_fLifeVar = 0.08f;

		// Size, in pixels
		m_fStartSize = 20.0f;
		m_fStartSizeVar = 10.0f;
		m_fEndSize = 10.0f;

		// Emits per seconds
		m_fEmissionRate = m_uTotalParticles / m_fLife;

		// color of particles 
		m_tStartColor.r = 0.0f;
		m_tStartColor.g = 0.25f;
		m_tStartColor.b = 0.76f;
		m_tStartColor.a = 1.0f;
		m_tStartColorVar.r = 0.0f;
		m_tStartColorVar.g = 0.0f;
		m_tStartColorVar.b = 0.0f;
		m_tStartColorVar.a = 0.0f;
		m_tEndColor.r = 0.76f;
		m_tEndColor.g = 0.25f;
		m_tEndColor.b = 0.12f;
		m_tEndColor.a = 0.0f;
		m_tEndColorVar.r = 0.0f;
		m_tEndColorVar.g = 0.0f;
		m_tEndColorVar.b = 0.0f;
		m_tEndColorVar.a = 0.0f;

		CCTexture2D* pTexture = CCTextureCache::sharedTextureCache()->addImage("Effect/fire.png");
		if (pTexture != NULL)
		{
			setTexture(pTexture);
		}
		return true;
	}
	return false;
}
void ParticleFire::setBoostColor(bool enabled)
{
	if (enabled)
	{
		m_tStartColor.r = 0.76f;
		m_tStartColor.g = 0.25f;
		m_tStartColor.b = 0.12f;
		m_fStartSize = 21.0f;
	}
	else
	{
		m_tStartColor.r = 0.0f;
		m_tStartColor.g = 0.25f;
		m_tStartColor.b = 0.76f;
		m_fStartSize = 13.0f;
	}
}
