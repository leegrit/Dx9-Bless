#pragma once
#include "UIElement.h"
namespace HyEngine
{
	class ENGINE_DLL UIPanel : public UIElement
	{
	private :
		explicit UIPanel(class Scene* scene,
			std::wstring imageFilePath,
			const Vector3 position,
			const Quaternion rotation,
			const Vector3 scale, 
			std::wstring tag);
		virtual ~UIPanel();

	public :
		virtual void Initialize() override;
		virtual void Render() override;

	public :
		static UIPanel * Create
		(
			Scene* scene,
			std::wstring imageFilePath,
			const Vector3 position,
			const Quaternion rotation,
			const Vector3 scale,
			std::wstring tag)
		{
			UIPanel* panel = new UIPanel(scene, imageFilePath, position, rotation, scale, tag);
			panel->Initialize();
			return panel;
		}



	};

}