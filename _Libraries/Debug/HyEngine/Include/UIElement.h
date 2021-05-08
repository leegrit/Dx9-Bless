#pragma once

#include "TextureObject.h"

namespace HyEngine
{

	class ENGINE_DLL UIElement abstract : public TextureObject
	{
	protected :
		explicit UIElement(class Scene* scene,
			std::wstring imageFilePath,
			const Vector3 position,
			const Quaternion rotation,
			const Vector3 scale,
			std::wstring tag);
		explicit UIElement(class Scene* scene,
			std::wstring imageFilePath,
			std::wstring name
		);
		virtual ~UIElement();

	public :
		virtual void Initialize() override;
		virtual void Render() override;



	};
}

