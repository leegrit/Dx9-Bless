#pragma once
#include "GameObject.h"

namespace HyEngine
{

	class ENGINE_DLL DynamicMesh : public GameObject
	{
		//////////////////////////////////////////////////////////////////////////
		// CONSTRUCTOR & DESTRUCTOR
		//////////////////////////////////////////////////////////////////////////
	protected :
		explicit DynamicMesh(Scene* scene, GameObject* parent,std::wstring name);
		virtual ~DynamicMesh();

		//////////////////////////////////////////////////////////////////////////
		// INHERITED
		//////////////////////////////////////////////////////////////////////////
	public :
		virtual void Initialize(std::wstring dataPat);
		virtual void Update() override;
		virtual void Render() override;
		virtual void UpdatedData(EDataType dataType) override;

		static DynamicMesh* Create(Scene* scene, GameObject* parent, std::wstring name, std::wstring dataPath)
		{
			DynamicMesh* mesh = new DynamicMesh(scene, parent,name);
			mesh->Initialize(dataPath);
			return mesh;
		}

		//////////////////////////////////////////////////////////////////////////
		// INITIALIZERS
		//////////////////////////////////////////////////////////////////////////
	private:
		void InitializeMeshes(std::wstring filePath, std::wstring fileName);

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
		// PRIVATE METHODS
		//////////////////////////////////////////////////////////////////////////
	private:
		void UpdateFrameMatrix(D3DXFRAME_DERIVED* frame, const D3DXMATRIX* parentMatrix);
		void SetupFrameMatrixPointer(D3DXFRAME_DERIVED* frame);

		//////////////////////////////////////////////////////////////////////////
		// VARIABLES
		//////////////////////////////////////////////////////////////////////////
	private:
		D3DXFRAME* m_pRootFrame;
		class MeshHierarchy* m_pLoader;
		class AnimationController* m_pAniCtrl;
		std::list<D3DXMESHCONTAINER_DERIVED*> m_MeshContainerList;
		std::wstring m_lastMeshPath;
	};

}