#pragma once
#include "Mesh.h"

namespace HyEngine
{

	class ENGINE_DLL DynamicMesh : public Mesh
	{
		//////////////////////////////////////////////////////////////////////////
		// CONSTRUCTOR & DESTRUCTOR
		//////////////////////////////////////////////////////////////////////////
	protected :
		explicit DynamicMesh(Scene* scene, GameObject* parent,std::wstring name, ESkinningType skinningType = ESkinningType::SoftwareSkinning);
		explicit DynamicMesh(Scene* scene, GameObject * parent, int editID, ESkinningType skinningType = ESkinningType::SoftwareSkinning);
		virtual ~DynamicMesh();

		//////////////////////////////////////////////////////////////////////////
		// INHERITED
		//////////////////////////////////////////////////////////////////////////
	public :
		virtual void Initialize(std::wstring dataPat);
		virtual void Initialize();
		virtual void Update() override;
		virtual void Render() override;
		virtual void PostRender(ID3DXEffect* pEffect) override;
		virtual void DrawPrimitive(ID3DXEffect* pShader) override;
		virtual void UpdatedData(EDataType dataType) override;
		virtual bool ComputeBoundingSphere(_Out_ D3DXVECTOR3 * center, _Out_ float * radius);

	

		//////////////////////////////////////////////////////////////////////////
		// INITIALIZERS
		//////////////////////////////////////////////////////////////////////////
	private:
		void InitializeMeshes(std::wstring filePath, std::wstring fileName);

		//////////////////////////////////////////////////////////////////////////
		// SETTER & GETTER
		//////////////////////////////////////////////////////////////////////////
	public :
		void SetSkinningType(ESkinningType type);
		ESkinningType GetSkinningType() const;

		//////////////////////////////////////////////////////////////////////////
		// PUBLIC METHODS
		//////////////////////////////////////////////////////////////////////////
	public:
		const D3DXFRAME_DERIVED* GetFrameByName(const char* frameName);
		bool IsAnimationSetEnd(double endTime = 0.1);
		bool IsAnimationAfterTrack(double afterTime);
		const unsigned int& GetAnimationNum();
		double GetCurAnimationPosition();
		const list<D3DXMESHCONTAINER_DERIVED*>& GetMeshContainerList();
		void SetAnimationSet(const unsigned int& index);
		void PlayAnimationSet(const float& timeDelta);

		//////////////////////////////////////////////////////////////////////////
		// CALLBACK
		//////////////////////////////////////////////////////////////////////////
	public:
		void OnRenderBegin(void*);
		void OnRenderEnd(void*);

		//////////////////////////////////////////////////////////////////////////
		// FOR EDITOR
		//////////////////////////////////////////////////////////////////////////
	public :
		void InitializeAnimationNames();
		int GetAnimationCount();
		void GetAnimationName(_Out_ class AnimNameData* outString, int index);

		//////////////////////////////////////////////////////////////////////////
		// PRIVATE METHODS
		//////////////////////////////////////////////////////////////////////////
	private:
		void UpdateFrameMatrix(D3DXFRAME_DERIVED* frame, const D3DXMATRIX* parentMatrix);
		void SetupFrameMatrixPointer(D3DXFRAME_DERIVED* frame);
		void UpdateBoneMatrix(D3DXFRAME_DERIVED* frame);
		void SetupBoneTextures();

		//////////////////////////////////////////////////////////////////////////
		// VARIABLES
		//////////////////////////////////////////////////////////////////////////
	private:
		D3DXFRAME* m_pRootFrame;
		class MeshHierarchy* m_pLoader;
		class AnimationController* m_pAniCtrl;
		std::vector<std::string> m_animationNames;
		std::list<D3DXMESHCONTAINER_DERIVED*> m_MeshContainerList;
		std::wstring m_lastMeshPath;
		ID3DXEffect* m_pShader = nullptr;
		std::vector<IDirect3DTexture9*> m_boneTextures;
		std::vector< D3DXMATRIX**>m_palettes;
		ESkinningType m_skinningType;

		//////////////////////////////////////////////////////////////////////////
		// FACTORY METHOD
		//////////////////////////////////////////////////////////////////////////
	public :
		static DynamicMesh* Create(Scene* scene, GameObject* parent, std::wstring name, std::wstring dataPath, ESkinningType skinningType = ESkinningType::SoftwareSkinning)
		{
			DynamicMesh* mesh = new DynamicMesh(scene, parent, name, skinningType);
			mesh->Initialize(dataPath);
			return mesh;
		}
		static DynamicMesh* Create(Scene* scene, GameObject* parent, int editID, ESkinningType skinningType = ESkinningType::SoftwareSkinning)
		{
			DynamicMesh * mesh = new DynamicMesh(scene, parent, editID, skinningType);
			mesh->Initialize();
			return mesh;
		}
	};

}