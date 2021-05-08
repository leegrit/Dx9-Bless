#pragma once
#include "UIElement.h"

namespace HyEngine
{

	class ENGINE_DLL ProgressBar : public UIElement
	{
	private :
		explicit ProgressBar(class Scene* scene,
			std::wstring fillFilePath,
			std::wstring fillBackFilePath,
			float amount,
			const Vector3 position,
			const Quaternion rotation,
			const Vector3 scale,
			std::wstring name);
		virtual ~ProgressBar();

	public :
		virtual void Initialize() override;
		virtual void Render() override;

	public :
		static ProgressBar* Create
		(
			Scene* scene,
			std::wstring fillFilePath,
			std::wstring fillBackFilePath,
			float amount,
			const Vector3 position,
			const Quaternion rotation,
			const Vector3 scale,
			std::wstring name
		)
		{
			ProgressBar* bar = new ProgressBar(scene, fillFilePath, fillBackFilePath, amount, position, rotation, scale, name);
			bar->Initialize();
			return bar;
		}

	public :
		inline void SetAmount(float amount) { m_amount = amount; }

	private :
		IDirect3DTexture9* m_pFillTex;
		IDirect3DTexture9* m_pFillBack;

		float m_amount;
	};
}