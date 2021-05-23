#pragma once
#include "Geometry.h"

namespace HyEngine
{
	class ENGINE_DLL MouseQuad : public Geometry
	{
		friend class Geometry;

	public:
		MouseQuad() = default;
		virtual ~MouseQuad() = default;
	protected:
		// Inherited via Geometry
		virtual void Initialize(void * arg) override;
		virtual void CreateVertex() override;
		virtual void CreateIndex() override;


	public:
		class TextureVertex* LockVertices();
		void UnlockVertices();

		class Index16* LockIndices();
		void UnlockIndices();
	};
}

