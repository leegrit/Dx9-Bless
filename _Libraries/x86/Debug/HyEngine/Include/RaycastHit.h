#pragma once

namespace HyEngine
{

	class ENGINE_DLL RaycastHit
	{
	public :
		RaycastHit(class Collider* collider);
		RaycastHit();

		class Collider* m_pCollider;
		class Transform* m_pTransform;
	};
}
