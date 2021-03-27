#pragma once
#include "Component.h"

namespace HyEngine
{
	class Animator abstract: public Component
	{
		//////////////////////////////////////////////////////////////////////////
		// CONSTRUCTOR & DESTRUCTOR
		//////////////////////////////////////////////////////////////////////////
	protected :
		explicit Animator(class GameObject* owner);
		virtual ~Animator() override;

		//////////////////////////////////////////////////////////////////////////
		// INHERITED
		//////////////////////////////////////////////////////////////////////////
	public :
		// Inherited via Component
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void OnEnable() override;
		virtual void OnDisable() override;

	private :

	};

}