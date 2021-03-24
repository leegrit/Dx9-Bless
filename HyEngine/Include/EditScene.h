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
		// �׽�Ʈ��
		void AddMeshObject(int editIndex);
		GameObject* GetMeshObject(int editIndex);
		
	};

}