#pragma once
#include "GameObject.h"

namespace HyEngine
{
	class Mesh abstract : public GameObject
	{
		//////////////////////////////////////////////////////////////////////////
		// CONSTRUCTOR & DESTRUCTOR 
		//////////////////////////////////////////////////////////////////////////
	protected :
		explicit Mesh(ERenderType renderType, Scene * scene, GameObject* parent, std::wstring name);
		virtual ~Mesh();

		//////////////////////////////////////////////////////////////////////////
		// INHERITED
		//////////////////////////////////////////////////////////////////////////
	public :
		virtual void Render() override;
		virtual void DrawPrimitive() override;
		virtual void UpdatedData(EDataType dataType) override;

		//////////////////////////////////////////////////////////////////////////
		// VIRTUAL
		//////////////////////////////////////////////////////////////////////////
	public :
		virtual bool ComputeBoundingSphere(_Out_ D3DXVECTOR3 * center, _Out_ float * radius);


	};

}