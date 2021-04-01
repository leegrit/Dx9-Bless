#pragma once
#include "UIButton.h"

namespace HyEngine
{

	class ENGINE_DLL ImageSwitchButton final: public UIButton
	{
	private :
		explicit ImageSwitchButton(class Scene* scene,
			std::wstring imageFilePath,
			std::wstring switchImagePath,
			const Vector3 position,
			const Quaternion rotation,
			const Vector3 scale,
			std::wstring tag);
		virtual ~ImageSwitchButton();


	public:
		virtual void Initialize() override;
		virtual void Render() override;

		static ImageSwitchButton* Create
		(
			Scene* scene,
			std::wstring imageFilePath,
			std::wstring switchImagePath,
			const Vector3 position,
			const Quaternion rotation,
			const Vector3 scale,
			std::wstring tag)
		{
			ImageSwitchButton* button = new ImageSwitchButton(scene, imageFilePath, switchImagePath, position, rotation, scale, tag);
			button->Initialize();
			return button;
		}
	protected :
		virtual void OnButtonDown();
		virtual void OnButtonUp();
		virtual void OnCollisionStayWithMouse();

	private :
		bool m_bImageChange = false;
		IDirect3DTexture9*m_pOriginTex;
		IDirect3DTexture9* m_pSwitchImage;
	};
}

