#include "UIElement.h"
#pragma once

namespace HyEngine
{
	class ENGINE_DLL UIElement
	{
	private:
		UIElement(class Scene* scene,
			std::wstring ImagePath,
			const Vector3 & position,
			const Quaternion & rotation,
			const Vector3 & scale);
		UIElement(const UIElement& other);
		inline UIElement::UIElement(Scene * scene, std::wstring imageFilePath, const Vector3 position, const Quaternion rotation, const Vector3 scale)
		{
		}
		virtual ~UIElement() = default;

	public:
		virtual HRESULT Initialize();
		virtual void Update();
		virtual void Render();

	protected:
		virtual void	OnMouseDown() {};
		virtual void	OnMouseUp() {};
		virtual void	OnMousePress() {};

	public:
		static	 UIElement* Create(class Scene* scene,
			std::wstring ImagePath,
			const Vector3 & position,
			const Quaternion & rotation,
			const Vector3 & scale);
		virtual void	Free();

	protected:
		std::wstring m_ImagePath;
		class Transform* m_pTransform = nullptr;
		IDirect3DTexture9* m_pTexture = nullptr;
		IDirect3DVertexBuffer9 * m_pVertexBuffer = nullptr;
		IDirect3DIndexBuffer9 * m_pIndexBuffer = nullptr;
		int m_vertexSize;
		int m_vertexCount;
		int m_triCount;
		int m_indexSize;

	private:
		bool useMouseInteraction = false;
	};
}
