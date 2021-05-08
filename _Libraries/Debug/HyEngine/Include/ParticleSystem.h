#pragma once
#include "ParticleStructure.h"
#include "Object.h"

namespace HyEngine
{
	class ENGINE_DLL ParticleSystem : public Object
	{
	public :
		ParticleSystem();
		virtual ~ParticleSystem();

		virtual void Init(std::wstring textureFileName);

		void Start();
		void Stop();

		virtual void Reset();

		// sometimes we don't want to free the memory of a dead particle,
		// but rather respawn it instead.
		virtual void ResetParticle(Attribute* attribute) = 0;
		virtual void AddParticle();

		virtual void Update() = 0;

		virtual void PreRender();
		virtual void Render();
		virtual void PostRender();
		

		bool isEmpty();
		bool isDead();

		bool GetActive();
		void SetActive(bool active);
	protected :
		virtual void RemoveDeadParticles();

	protected :
		bool m_bActive;
		D3DXVECTOR3 m_origin;
		float m_emitRate; // rate new particles are added to system
		float m_size; // size of particles
		IDirect3DTexture9* m_pTexture;
		IDirect3DVertexBuffer9* m_pVB;
		std::list<Attribute> m_particles;
		int m_maxParticles; // max allowed particles system can have

		// Following three data elements used for rendering the particle system efficiently
		DWORD m_vbSize; // size fo vb;
		DWORD m_vbOffset; // offset in vb to lock
		DWORD m_vbBatchSize; // number of vertices to lock starting at m_vbOffset
	};
}