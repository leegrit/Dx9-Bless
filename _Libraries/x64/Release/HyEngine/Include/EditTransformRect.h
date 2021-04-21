#pragma once
#include "GameObject.h"


namespace HyEngine
{
	class EditTransformRect : public GameObject
	{
	private :
		explicit EditTransformRect(Scene* scene, GameObject* parent);
		virtual ~EditTransformRect();

	public :
		virtual void Initialize();
		virtual void Render() override;

	public :
		static EditTransformRect* Create(Scene* scene, GameObject* parent);



	private :
		class DiffuseQuad* m_pXYRect = nullptr;
		class DiffuseQuad* m_pZYRect = nullptr;
		class DiffuseQuad* m_pZXRect = nullptr;

		LPD3DXEFFECT m_pEffect = nullptr;

	};

}