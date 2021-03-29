#pragma once
#include "EditObject.h"

namespace HyEngine
{
	class EditDynamicMesh final : public EditObject
	{
	private :
		explicit EditDynamicMesh(Scene* scene, GameObject* parent, int editID);
		virtual ~EditDynamicMesh();

		//////////////////////////////////////////////////////////////////////////
		// INHERITED
		//////////////////////////////////////////////////////////////////////////
	public :
		virtual void Initialize();
		virtual void Render() override;
		virtual void UpdatedData(EDataType dataType) override;

		static EditDynamicMesh* Create(Scene* scene, GameObject* parent, int editID)
		{
			//assert(false);
			EditDynamicMesh* mesh = new EditDynamicMesh(scene, parent, editID);
			//assert(false);
			mesh->Initialize();
			return mesh;
		}


		//////////////////////////////////////////////////////////////////////////
		// INITIALIZERS
		//////////////////////////////////////////////////////////////////////////
	private :
		void InitializeMeshes(std::wstring filePath, std::wstring fileName);

		//////////////////////////////////////////////////////////////////////////
		// PUBLIC METHODS
		//////////////////////////////////////////////////////////////////////////
	public :
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
	private :
		void UpdateFrameMatrix(D3DXFRAME_DERIVED* frame, const D3DXMATRIX* parentMatrix);
		void SetupFrameMatrixPointer(D3DXFRAME_DERIVED* frame);

	private :
		D3DXFRAME* m_pRootFrame;
		// Hierarchy* m_pLoader;
		// MeshAnimator * m_pAnimator;

		std::list<D3DXMESHCONTAINER_DERIVED*> m_MeshContainerList;






	};

}