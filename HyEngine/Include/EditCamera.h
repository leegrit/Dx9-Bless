#pragma once
#include "Camera.h"

namespace Editor
{
	class EditCamera : public Camera
	{
	private :
		EditCamera(class Scene* scene, class GameObject* parent);
		virtual ~EditCamera();
	public:
		static EditCamera * Create(Scene* scene, GameObject* parent)
		{
			EditCamera * camera = new EditCamera(scene, parent);
			camera->Initialize();
			return camera;
		}
	public:
		virtual void Initialize() override;
		virtual void CameraUpdate() override;

	};
}

