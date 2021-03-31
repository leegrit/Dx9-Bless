#pragma once

namespace HyEngine
{
	class ENGINE_DLL Skybox
	{
	public:
		Skybox(class Camera* camera, std::wstring cubeTexPath);
		~Skybox();

		void Initialize();
		void Update();
		void Render();

	private :
		class TextureCubeVertex* LockVertices();
		void UnlockVertices();

		class Index16* LockIndices();
		void UnlockIndices();

		//void SetTarget(GameObject* pTarget) { m_pTarget = pTarget; }

	private :
		bool m_isInit = false;
		// vertex
		int m_vertexSize;
		int m_vertexCount;
		DWORD m_vertexFVF;
		IDirect3DVertexBuffer9 * m_pVertexBuffer = nullptr;

		// index
		int m_indexSize;
		int m_indexCount;
		int m_indexFMT;
		IDirect3DIndexBuffer9* m_pIndexBuffer = nullptr;

		int m_primitiveCount;

		IDirect3DCubeTexture9* m_pTexture = nullptr;

		class GameObject* m_pCamera;

		D3DLIGHT9 m_light;

		class Transform* m_pTransform;
	};

}