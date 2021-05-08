#pragma once
#include "ParticleSystem.h"

using namespace HyEngine;

class ENGINE_DLL ParticleGun : public ParticleSystem
{
public:
	ParticleGun(class Transform* firePos, int numParticles);


	// Inherited via ParticleSystem
	virtual void ResetParticle(Attribute * attribute) override;

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void PostRender() override;
private :
	class Transform* m_pFirePos;
	DWORD m_srcBlendOld;
	DWORD m_destBlendOld;
};

