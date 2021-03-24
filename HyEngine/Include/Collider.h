#pragma once
#include "Object.h"

namespace HyEngine
{
	class ENGINE_DLL Collider abstract : public Object
	{
	protected:
		Collider(EColliderShape colliderShape, EColliderType colliderType, GameObject* owner, UINT targetLayer,std::function<void(Collider*)> onCollision = nullptr );
		virtual ~Collider() = default;
	public:
		virtual void Initialize();
		void PositionUpdate();
		virtual void Render();
	public:

		virtual void Calculate(Collider* other) const;

		virtual bool CalculateToDot(D3DXVECTOR3 dotPos) = 0;
		// Getter
		bool GetActive() const;
		inline EColliderShape GetColliderShape() { return m_colliderShape; }
		inline EColliderType GetColliderType() { return m_colliderType; }

		inline Transform* GetTransform() const { return m_pTransform; }
		inline GameObject* GetGameObject() const { return m_pOwner; }

		inline UINT GetTargetLayer()const { return m_targetLayer; }
	public :
		inline void SetOffset(Vector3 position) { m_offset = position; }

	protected :
		EColliderType m_colliderType;
		EColliderShape m_colliderShape;
		//ECollisionLayer m_collisionLayer;
		// 해당 레이어만 충돌처리됨
		UINT m_targetLayer;

		GameObject* m_pOwner;
		Transform * m_pTransform;
	protected:
		Vector3 m_offset;
		public:
		std::function<void(Collider*)> m_onCollision;
	};

}

