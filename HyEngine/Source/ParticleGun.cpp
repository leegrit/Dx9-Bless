#include "StandardEngineFramework.h"
#include "ParticleGun.h"
#include "Transform.h"

ParticleGun::ParticleGun(Transform * firePos, int numParticles)
	: ParticleSystem()
{

	m_size = 0.8f;
	m_vbSize = 2048;
	m_vbOffset = 0;
	m_vbBatchSize = 512;
	m_pFirePos = firePos;
	m_origin = m_pFirePos->m_position.operator D3DXVECTOR3();

	for (int i = 0; i < numParticles; i++)
		AddParticle();
}

void ParticleGun::ResetParticle(Attribute * attribute)
{
	attribute->isAlive = true;

	attribute->position = m_pFirePos->m_position.operator D3DXVECTOR3();


	attribute->velocity = (m_pFirePos->Forward() * 100.0f).operator D3DXVECTOR3();

	// red
	attribute->color = D3DXCOLOR(0.3f, 0.0f, 0.0f, 1.0f);
	attribute->age = 0;
	attribute->lifeTime = 1.0f;
}

void ParticleGun::Update()
{
	std::list<Attribute>::iterator iter;

	for (iter = m_particles.begin(); iter != m_particles.end(); iter++)
	{
		iter->position += iter->velocity * (float)TIMER->getDeltaTime();

		iter->age += (float)TIMER->getDeltaTime();

		if (iter->age > iter->lifeTime)
			iter->isAlive = false;
	}
	RemoveDeadParticles();
}



void ParticleGun::PreRender()
{
	ParticleSystem::PreRender();

	DEVICE->GetRenderState(D3DRS_SRCBLEND, &m_srcBlendOld);
	DEVICE->GetRenderState(D3DRS_DESTBLEND, &m_destBlendOld);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// read, but don't write particles to z-buffer
	//DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, false);
}

void ParticleGun::PostRender()
{
	ParticleSystem::PostRender();
	DEVICE->SetRenderState(D3DRS_SRCBLEND, m_srcBlendOld);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, m_destBlendOld);
	DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, true);
}
