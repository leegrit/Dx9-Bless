#include "StandardEngineFramework.h"
#include "FireworkSystem.h"

using namespace HyEngine;

FireworkSystem::FireworkSystem(D3DXVECTOR3 * origin, int numParticles)
	:ParticleSystem()
{
	m_origin = *origin;
	m_size = 0.9f;
	m_vbSize = 2048;
	m_vbOffset = 0;
	m_vbBatchSize = 512;

	for (int i = 0; i < numParticles; i++)
		AddParticle();
}

void FireworkSystem::ResetParticle(Attribute * attribute)
{
	attribute->isAlive = true;
	attribute->position = m_origin;
	
	D3DXVECTOR3 min = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	D3DXVECTOR3 max = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	DxHelper::GetRandomVector
	(
		&attribute->velocity,
		&min,
		&max
	);

	// normalize to make spherical
	D3DXVec3Normalize
	(
		&attribute->velocity,
		&attribute->velocity
	);
	attribute->velocity *= 100.0f;

	attribute->color = D3DXCOLOR
	(
		DxHelper::GetRandomFloat(0.0f, 1.0f),
		DxHelper::GetRandomFloat(0.0f, 1.0f),
		DxHelper::GetRandomFloat(0.0f, 1.0f),
		1.0f
	);

	attribute->age = 0.0f;
	attribute->lifeTime = 2.0f; // lives for 2 seconds
}

void FireworkSystem::Update()
{
	std::list<Attribute>::iterator iter;

	for(iter = m_particles.begin(); iter != m_particles.end(); iter++)
	{
		// only update living particles
		if(iter->isAlive)
		{
			iter->position += iter->velocity * (float)TIMER->getDeltaTime();

			iter->age += (float)TIMER->getDeltaTime();

			if (iter->age > iter->lifeTime) // kill
				iter->isAlive = false;
		}
	}
}

void FireworkSystem::PreRender()
{
	ParticleSystem::PreRender();

	DEVICE->GetRenderState(D3DRS_SRCBLEND, &m_srcBlendOld);
	DEVICE->GetRenderState(D3DRS_DESTBLEND, &m_destBlendOld);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// read, but don't write particles to z-buffer
	DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, false);
}

void FireworkSystem::PostRender()
{
	ParticleSystem::PostRender();
	DEVICE->SetRenderState(D3DRS_SRCBLEND, m_srcBlendOld);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, m_destBlendOld);
	DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, true);
}
