#pragma once
#include "Geometry.h"

namespace HyEngine
{
	class ENGINE_DLL TextureQuad : public Geometry
	{
		friend class Geometry;
	public :
		TextureQuad() = default;
		virtual ~TextureQuad() = default;
	protected :
		// Inherited via Geometry
		virtual void Initialize(void * arg) override;
		virtual void CreateVertex() override;
		virtual void CreateIndex() override;


	public :
		class TextureVertex* LockVertices();
		void UnlockVertices();

		class Index16* LockIndices();
		void UnlockIndices();

	};

}

