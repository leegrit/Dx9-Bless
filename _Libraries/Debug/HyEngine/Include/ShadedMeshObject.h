// #pragma once
// #include "GameObject.h"
// 
// namespace HyEngine
// {
// 	class ENGINE_DLL ShadedMeshObject abstract : public GameObject
//  	{
// 	protected :
// 		explicit ShadedMeshObject(class Scene* scene,
// 			GameObject* parent,
// 			ERenderType renderType,
// 			const std::wstring& meshFilePath,
// 			const std::wstring& baseTexturePath,
// 			const std::wstring& normalTexturePath,
// 			const std::wstring& emissionTexturePath,
// 			const std::wstring& tag);
// 		virtual ~ShadedMeshObject();
// 
// 	public :
// 		virtual void Initialize();
// 		virtual void Render() override;
// 
// 	protected :
// 		void Draw();
// 	protected :
// 		IDirect3DTexture9* m_pBaseTex = nullptr;
// 		IDirect3DTexture9* m_pBumpTex = nullptr;
// 		IDirect3DTexture9* m_pEmission = nullptr;
// 		//class BumpMesh* m_pMesh = nullptr;
// 		std::shared_ptr<Mesh> m_pMesh = nullptr;
// 
// 		LPD3DXEFFECT m_pEffect = nullptr;
// 
// 	};
// 
// }