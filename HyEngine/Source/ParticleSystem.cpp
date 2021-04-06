#include "StandardEngineFramework.h"
#include "ParticleSystem.h"

using namespace HyEngine;

HyEngine::ParticleSystem::ParticleSystem()
	:Object(L"ParticleSystem")
{
	m_pVB = nullptr;
	m_pTexture = nullptr;
	m_bActive = true;
	//ENGINE->GetActiveScene()->AddParticleSystem(this);
}

HyEngine::ParticleSystem::~ParticleSystem()
{
	SAFE_RELEASE(m_pVB);
	SAFE_RELEASE(m_pTexture);
}

void HyEngine::ParticleSystem::Init(std::wstring textureFileName)
{
	// vertex buffer's size does not equal the number of particles in our system.  We
	// use the vertex buffer to draw a portion of our particles at a time.  The arbitrary
	// size we choose for the vertex buffer is specified by the _vbSize variable.

	HRESULT hr = 0;

	hr = DEVICE->CreateVertexBuffer
	(
		m_vbSize * sizeof(Particle),
		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
		Particle::FVF,
		D3DPOOL_DEFAULT,
		&m_pVB,
		0
	);
	assert(SUCCEEDED(hr));

	hr = D3DXCreateTextureFromFile
	(
		DEVICE,
		textureFileName.c_str(),
		&m_pTexture
	);
	assert(SUCCEEDED(hr));
}

void HyEngine::ParticleSystem::Start()
{
	Reset();
}

void HyEngine::ParticleSystem::Stop()
{
	for (auto& particle : m_particles)
		particle.isAlive = false;
}

void HyEngine::ParticleSystem::Reset()
{
	std::list<Attribute>::iterator i;
	for (i = m_particles.begin(); i != m_particles.end(); i++)
	{
		ResetParticle(&(*i));
	}
}


void HyEngine::ParticleSystem::AddParticle()
{
	Attribute attribute;
	ResetParticle(&attribute);
	m_particles.push_back(attribute);
}


void HyEngine::ParticleSystem::PreRender()
{
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	DEVICE->SetTransform(D3DTS_WORLD, &mat);
	// 여긴 나중에
	// Scene으로 감
	//DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	DEVICE->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	DEVICE->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	DEVICE->SetRenderState(D3DRS_POINTSIZE,DxHelper::Float2DWORD(m_size));
	DEVICE->SetRenderState(D3DRS_POINTSIZE_MIN, DxHelper::Float2DWORD(0.0f));

	// control the size of the particle relative to distance
	DEVICE->SetRenderState(D3DRS_POINTSCALE_A, DxHelper::Float2DWORD(0.0f));
	DEVICE->SetRenderState(D3DRS_POINTSCALE_B, DxHelper::Float2DWORD(0.0f));
	DEVICE->SetRenderState(D3DRS_POINTSCALE_C, DxHelper::Float2DWORD(1.0f));

	// use alpha from texture
	//DEVICE->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	//DEVICE->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	/*DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);*/
}

void HyEngine::ParticleSystem::Render()
{
	//
	// Remarks:  The render method works by filling a section of the vertex buffer with data,
	//           then we render that section.  While that section is rendering we lock a new
	//           section and begin to fill that section.  Once that sections filled we render it.
	//           This process continues until all the particles have been drawn.  The benifit
	//           of this method is that we keep the video card and the CPU busy.  

	if (!m_particles.empty())
	{
		// set render states
		// 나중엔 씬에서 함
		PreRender();

		DEVICE->SetTexture(0, m_pTexture);
		DEVICE->SetFVF(Particle::FVF);
		DEVICE->SetStreamSource(0, m_pVB, 0, sizeof(Particle));

		// render batches on by one

		// start at beginning if we're at the end of the vb
		if (m_vbOffset >= m_vbSize)
			m_vbOffset = 0;

		Particle* vertices = 0;

		m_pVB->Lock
		(
			m_vbOffset * sizeof(Particle),
			m_vbBatchSize * sizeof(Particle),
			(void**)&vertices,
			m_vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD
		);

		DWORD numParticlesInBatch = 0;

		// until all particles have been rendered.

		std::list<Attribute>::iterator iter;
		for (iter = m_particles.begin(); iter != m_particles.end(); iter++)
		{
			if (iter->isAlive)
			{
				//
				// Copy a batch of the living particles to the
				// next vertex buffer segment
				//

				vertices->position = iter->position;
				vertices->color = iter->color;
				vertices++; // next element

				numParticlesInBatch++; // increase batch counter

				// if this batch full?
				if (numParticlesInBatch == m_vbBatchSize)
				{
					//
					// Draw the last batch of particles that was
					// copied to the vertex buffer. 
					//
					m_pVB->Unlock();

					DEVICE->DrawPrimitive
					(
						D3DPT_POINTLIST,
						m_vbOffset,
						m_vbBatchSize
					);

					//
					// While that batch is drawing, start filling the
					// next batch with particles.
					//

					// move the offset to the start of the next batch
					m_vbOffset += m_vbBatchSize;

					// don't offset into memory thats outside the vb's range.
					// If we're at the end, start at the beginning.
					if (m_vbOffset >= m_vbSize)
						m_vbOffset = 0;

					m_pVB->Lock
					(
						m_vbOffset * sizeof(Particle),
						m_vbBatchSize * sizeof(Particle),
						(void**)&vertices,
						m_vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD
					);
					numParticlesInBatch = 0;// reset for new batch

				}
			}
		}
		m_pVB->Unlock();

		// its possible that the LAST batch being filled never 
		// got rendered because the condition 
		// (numParticlesInBatch == _vbBatchSize) would not have
		// been satisfied.  We draw the last partially filled batch now.
		if (numParticlesInBatch)
		{
			DEVICE->DrawPrimitive
			(
				D3DPT_POINTLIST,
				m_vbOffset,
				numParticlesInBatch
			);
		}
		// next block
		m_vbOffset += m_vbBatchSize;


		// reset render state
		// 나중엔 씬에서 함
		PostRender();
	}
}

void HyEngine::ParticleSystem::PostRender()
{
	//DEVICE->SetRenderState(D3DRS_LIGHTING, true);
	DEVICE->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	DEVICE->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	//DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}



bool HyEngine::ParticleSystem::isEmpty()
{
	return m_particles.empty();
}

bool HyEngine::ParticleSystem::isDead()
{
	std::list<Attribute>::iterator iter;
	for (iter = m_particles.begin(); iter != m_particles.end(); iter++)
	{
		// is there at least one living particle?  If yes,
		// the system is not dead.
		if (iter->isAlive)
			return false;
	}
	return true;

}

bool HyEngine::ParticleSystem::GetActive()
{
	return m_bActive;
}

void HyEngine::ParticleSystem::SetActive(bool active)
{
	m_bActive = active;
}

void HyEngine::ParticleSystem::RemoveDeadParticles()
{
	std::list<Attribute>::iterator iter;
	iter = m_particles.begin();

	while (iter != m_particles.end())
	{
		if (iter->isAlive == false)
		{
			// erase returns the next iterator, so no need to
			// incrememnt to the next one ourselves.
			iter = m_particles.erase(iter);
		}
		else
		{
			iter++; // next in list
		}
	}
}
