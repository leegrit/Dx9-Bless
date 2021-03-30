#pragma once
#include "UIButton.h"

namespace HyEngine
{
	class ENGINE_DLL ImageButton final : public UIButton
	{
	private :
		explicit ImageButton(class Scene* scene,
			std::wstring imageFilePath,
			std::wstring switchImagePath,
			const Vector3 position,
			const Quaternion rotation,
			const Vector3 scale,
			std::wstring tag);
		virtual ~ImageButton();

	public :
		virtual void Initialize() override;
		virtual void Render() override;

		static ImageButton* Create
		(
			Scene* scene,
			std::wstring imageFilePath,
			std::wstring switchImagePath,
			const Vector3 position,
			const Quaternion rotation,
			const Vector3 scale,
			std::wstring tag)
		{
			ImageButton* button = new ImageButton(scene, imageFilePath, switchImagePath, position, rotation, scale, tag);
			button->Initialize();
			return button;
		}
	protected:
		virtual void OnButtonDown();
		virtual void OnButtonUp();
		virtual void OnCollisionStayWithMouse();
	public :
		void ImageChange() { m_bImageChange = !m_bImageChange; }
		void SetOriginImage() { m_bImageChange = false; }
		void SetSwitchImage() { m_bImageChange = true; }
	private:
		bool m_bImageChange = false;
		std::shared_ptr<IDirect3DTexture9> m_pOriginTex;
		std::shared_ptr<IDirect3DTexture9> m_pSwitchImage;

	};

}