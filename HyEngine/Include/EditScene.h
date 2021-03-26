#pragma once
#include "Scene.h"

namespace Editor
{
	class EditScene : public HyEngine::Scene
	{
	public:
		virtual void Update() override;
		virtual void Load() override;
		virtual void Unload() override;
		virtual void LoadAsync(std::function<void(int, int)> onProgress) override;

		virtual void LateLoadScene() override;

	public :
		// 테스트용
		void AddMeshObject(int editIndex);
		void AddNavMesh(int editIndex);
		
		GameObject* GetGameObject(int editIndex);
		class Camera* GetEditCamera();

		//void PickNavMesh(float xMousePos, float yMousePos);

		bool PickNavMesh(float xMousePos, float yMousePos, ECellOption option,VectorData* pickedPos);

	private :
		class EditCamera* m_pEditCamera = nullptr;
	};

}