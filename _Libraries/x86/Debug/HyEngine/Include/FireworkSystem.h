#pragma once

#include "ParticleSystem.h"


using namespace HyEngine;


class ENGINE_DLL FireworkSystem : public ParticleSystem
{
public :
	FireworkSystem(D3DXVECTOR3* origin, int numParticles);
	virtual void ResetParticle(Attribute* attribute) override;
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void PostRender() override;

private :
	DWORD m_srcBlendOld;
	DWORD m_destBlendOld;

};