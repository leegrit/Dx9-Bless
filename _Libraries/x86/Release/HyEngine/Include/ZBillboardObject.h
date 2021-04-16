#pragma once
#include "ZTextureObject.h"

namespace HyEngine
{
	class ENGINE_DLL ZBillboardObject : public ZTextureObject
	{
	protected:
		explicit ZBillboardObject(class Scene* scene,
			class GameObject* parent,
			EBillboardType billboardType,
			std::wstring imageFilePath,
			std::wstring tag);
		virtual ~ZBillboardObject();

	public:
		virtual void Initialize() override;
		virtual void Render() override;

	private:
		D3DXMATRIX CalcBillboardAll();
		D3DXMATRIX CalcBillboardX();
		D3DXMATRIX CalcBillboardY();
		D3DXMATRIX CalcBillboardZ();


	private:
		EBillboardType m_billboardType;
	};
}
