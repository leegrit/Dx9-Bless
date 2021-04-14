#pragma once

#include "UIElement.h"

namespace HyEngine
{
	class ENGINE_DLL UIPanel : public UIElement
	{
		//////////////////////////////////////////////////////////////////////////
		// CONSTRUCTOR & DESTRUCTOR 
		//////////////////////////////////////////////////////////////////////////
	protected :
		explicit UIPanel(Scene* scene, GameObject* parent, int editID);
		explicit UIPanel(Scene* scene, std::wstring name);
		virtual ~UIPanel();

		//////////////////////////////////////////////////////////////////////////
		// INHERITED
		//////////////////////////////////////////////////////////////////////////
	public :
		virtual void Initialize() override;
		virtual void Initialize(std::wstring imageFilePath, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale);
		virtual void Render() override;
		virtual void UpdatedData(EDataType dataType) override;

		//////////////////////////////////////////////////////////////////////////
		// VARIABLES
		//////////////////////////////////////////////////////////////////////////
	private :
		ID3DXEffect* m_pShader = nullptr;
		class TextureQuad * m_pTextureQuad = nullptr;
		IDirect3DTexture9 * m_pTexture = nullptr;

		//////////////////////////////////////////////////////////////////////////
		// FACTORY METHOD
		//////////////////////////////////////////////////////////////////////////
	public :
		/* For Editor */
		static UIPanel* Create(Scene* scene, GameObject* parent, int editID);
		/* For Client */
		static UIPanel * Create(Scene* scene, std::wstring imageFilePath, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale, std::wstring name);


	};
}

