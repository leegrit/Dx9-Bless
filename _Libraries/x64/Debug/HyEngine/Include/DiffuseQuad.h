#pragma once
#include "Geometry.h"

namespace HyEngine
{
	class DiffuseQuad : public Geometry
	{
		friend class Geometry;
	protected :
		// Inherited via Geometry
		virtual void Initialize(void * arg) override;
		virtual void CreateVertex() override;
		virtual void CreateIndex() override;


	public :
		class ColorVertex * LockVertices();
		void UnlockVertices();

		class Index16* LockIndices();
		void UnlockIndices();

	private :
		D3DCOLOR m_color;
	};
}

