#pragma once
#include "UIElement.h"

namespace HyEngine
{
	class ENGINE_DLL ProgressVerticalBar : public UIElement
	{
	private:
		explicit ProgressVerticalBar(class Scene* scene,
			std::wstring fillFilePath,
			std::wstring fillBackFilePath,
			float amount,
			const Vector3 position,
			const Quaternion rotation,
			const Vector3 scale,
			std::wstring name);
		virtual ~ProgressVerticalBar();

	public:
		virtual void Initialize() override;
		virtual void Render() override;

	public:
		static ProgressVerticalBar* Create
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
			ProgressVerticalBar* bar = new ProgressVerticalBar(scene, fillFilePath, fillBackFilePath, amount, position, rotation, scale, name);
			bar->Initialize();
			return bar;
		}

	public:
		inline void SetAmount(float amount) { m_amount = amount; }

	private:
		std::shared_ptr<IDirect3DTexture9> m_pFillTex;
		std::shared_ptr<IDirect3DTexture9> m_pFillBack;

		float m_amount;
	};


}