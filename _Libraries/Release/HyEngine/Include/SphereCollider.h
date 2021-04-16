#pragma once
#include "Collider.h"

namespace HyEngine
{

	class ENGINE_DLL SphereCollider : public Collider
	{
	private :
		SphereCollider(EColliderType colliderType, GameObject* owner, int radius, UINT targetLayer, D3DXCOLOR color, std::function<void(Collider*)> onCollision = nullptr);
		virtual ~SphereCollider();

	public :
		static SphereCollider* Create(EColliderType colliderType, GameObject* owner, int radius,UINT targetLayer, std::function<void(Collider*)> onCollision = nullptr)
		{
			SphereCollider * col = new SphereCollider(colliderType, owner, radius,targetLayer, D3DCOLOR_ARGB(255, 0, 255, 0) , onCollision);
			col->Initialize();

			return col;
		}
		static SphereCollider* Create(EColliderType colliderType, GameObject* owner, int radius, UINT targetLayer,  D3DXCOLOR color,  std::function<void(Collider*)> onCollision = nullptr)
		{
			SphereCollider * col = new SphereCollider(colliderType, owner, radius, targetLayer,color,  onCollision);
			col->Initialize();

			return col;
		}

	public :
		virtual void Initialize() override;
		virtual void Render() override;
		virtual void Calculate(Collider* other) const override;
		virtual bool CalculateToDot(D3DXVECTOR3 dotPos) override;

		// Getter
		inline int GetRadius() const { return m_radius; };
		void SetRadius(float radius);

	private :
		bool CalcToSphere(Collider* other) const;
		bool CalcToBox(Collider* other) const;
		bool CalcToAABB(Collider* other) const;
		bool CalcToOBB(Collider* other) const;

	private :
		int m_radius;
		D3DXCOLOR m_color;
		ID3DXMesh * m_pSphereMesh;

		int m_slices = 10;
		int m_stacks = 10;
	};

}