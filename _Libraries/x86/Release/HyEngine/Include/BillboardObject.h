#pragma once
#include "TextureObject.h"


namespace HyEngine
{
	class ENGINE_DLL BillboardObject : public TextureObject
	{
	protected :
		explicit BillboardObject(class Scene* scene,
			class GameObject* parent,
			EBillboardType billboardType,
			std::wstring imageFilePath,
			std::wstring tag);
		virtual ~BillboardObject();

	public :
		virtual void Initialize() override;
		virtual void Render() override;

	private :
		D3DXMATRIX CalcBillboardAll();
		D3DXMATRIX CalcBillboardX();
		D3DXMATRIX CalcBillboardY();
		D3DXMATRIX CalcBillboardZ();


	private :
		EBillboardType m_billboardType;

	};

}