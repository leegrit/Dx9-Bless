#include "StandardEngineFramework.h"
#include "QuadTree.h"
#include "Mesh.h"


HyEngine::QuadTree::QuadTree()
{
	m_center = Vector3::Zero;
	for (int i = 0; i < 4; i++)
	{
		m_pChild[i] = nullptr;
		m_corner[i] = Vector3::Zero;
	}
	m_radius = 0;

}

void HyEngine::QuadTree::Build(std::vector<GameObject*> objs)
{
	if (objs.size() <= 10) return;

	float minX = FLT_MAX;
	float minZ = FLT_MAX;
	float maxX = -FLT_MAX;
	float maxZ = -FLT_MAX;

	for (auto& obj : objs)
	{
		Mesh* mesh = dynamic_cast<Mesh*>(obj);
		if (mesh == nullptr)
			continue;

		
		float tempMinX = mesh->GetBoundingWorldPos().x - mesh->GetBoundingRadius();
		if (minX >= tempMinX)
		{
			minX = tempMinX;
		}
		float tempMinZ = mesh->GetBoundingWorldPos().z - mesh->GetBoundingRadius();
		if (minZ >= tempMinZ)
		{
			minZ = tempMinZ;
		}
		float tempMaxX = mesh->GetBoundingWorldPos().x + mesh->GetBoundingRadius();
		if (maxX <= tempMaxX)
		{
			maxX = tempMaxX;
		}
		float tempMaxZ = mesh->GetBoundingWorldPos().z + mesh->GetBoundingRadius();
		if (maxZ <= tempMaxZ)
		{
			maxZ = tempMaxZ;
		}

	}

	m_corner[(int)ECornerType::CORNER_FL] = D3DXVECTOR3(minX, 0, maxZ);
	m_corner[(int)ECornerType::CORNER_FR] = D3DXVECTOR3(maxX, 0, maxZ);
	m_corner[(int)ECornerType::CORNER_BL] = D3DXVECTOR3(minX, 0, minZ);
	m_corner[(int)ECornerType::CORNER_BR] = D3DXVECTOR3(maxX, 0, minZ);

	m_center =
	(
		m_corner[(int)ECornerType::CORNER_FL] +
		m_corner[(int)ECornerType::CORNER_FR] +
		m_corner[(int)ECornerType::CORNER_BL] +
		m_corner[(int)ECornerType::CORNER_BR]
		) / 4;

	m_radius = D3DXVec3Length(&(m_center - m_corner[(int)ECornerType::CORNER_FL]));

	BuildRecursively(objs);
}

void HyEngine::QuadTree::QuadTreeCull(Camera * cam)
{
	// 1차적으로 모두 cull해둔채로 tree를 순회한다.
	// 메쉬의 크기가 크기때문에 여러 쿼드트리에 걸칠 수도 있는데
	// 단 한곳에서라도 render가 되어도 cull되면 안되기때문에
	// 먼저 모두 cull해두고 그려야하는 것만 false하는식으로 순회한다.
	for (auto& obj : m_objects)
	{
		obj->SetViewFrustumCulled(true);
	}

	QuadTreeCullRecursively(cam);
}

bool HyEngine::QuadTree::SubDivide()
{
	/* 더이상 분할이 불가능하다면 종료한다. */
	if (m_radius <= QuadTree::MinimumRadius)
	{
		return false;
	}
	D3DXVECTOR3 topEdgeCenter;
	D3DXVECTOR3 bottomEdgeCenter;
	D3DXVECTOR3 leftEdgeCenter;
	D3DXVECTOR3 rightEdgeCenter;
	D3DXVECTOR3 centralPoint;

	/* Top Center */
	topEdgeCenter = (m_corner[(int)ECornerType::CORNER_FL] + m_corner[(int)ECornerType::CORNER_FR]) / 2;

	/* Bottom Center */
	bottomEdgeCenter = (m_corner[(int)ECornerType::CORNER_BL] + m_corner[(int)ECornerType::CORNER_BR]) / 2;

	/* Left Center */
	leftEdgeCenter = (m_corner[(int)ECornerType::CORNER_FL] + m_corner[(int)ECornerType::CORNER_BL]) / 2;

	/* Right Center */
	rightEdgeCenter = (m_corner[(int)ECornerType::CORNER_FR] + m_corner[(int)ECornerType::CORNER_BR]) / 2;

	/* Center */
	centralPoint =
		(
			m_corner[(int)ECornerType::CORNER_FL] +
			m_corner[(int)ECornerType::CORNER_FR] +
			m_corner[(int)ECornerType::CORNER_BL] +
			m_corner[(int)ECornerType::CORNER_BR]
			) / 4;

	/* Add Child */
	m_pChild[(int)ECornerType::CORNER_FL] = AddChild(m_corner[(int)ECornerType::CORNER_FL], topEdgeCenter, leftEdgeCenter, centralPoint);
	m_pChild[(int)ECornerType::CORNER_FR] = AddChild(topEdgeCenter, m_corner[(int)ECornerType::CORNER_FR], centralPoint, rightEdgeCenter);
	m_pChild[(int)ECornerType::CORNER_BL] = AddChild(leftEdgeCenter, centralPoint, m_corner[(int)ECornerType::CORNER_BL], bottomEdgeCenter);
	m_pChild[(int)ECornerType::CORNER_BR] = AddChild(centralPoint, rightEdgeCenter, bottomEdgeCenter, m_corner[(int)ECornerType::CORNER_BR]);

	return true;
}

void HyEngine::QuadTree::BuildRecursively(std::vector<GameObject*> objs)
{
	/* 범위에 들어온 오브젝트들을 선별하여 저장해둔다. */
	m_objects = cpplinq::from_iterators(objs.begin(), objs.end())
		>> cpplinq::where([&](GameObject* obj)
	{
		Mesh* mesh = dynamic_cast<Mesh*>(obj);
		if (mesh == nullptr)
			return false;

		if (m_corner[(int)ECornerType::CORNER_FL].x > mesh->GetBoundingWorldPos().x)
			return false;

		if (m_corner[(int)ECornerType::CORNER_FL].z < mesh->GetBoundingWorldPos().z)
			return false;

		if (m_corner[(int)ECornerType::CORNER_BR].x < mesh->GetBoundingWorldPos().x)
			return false;

		if (m_corner[(int)ECornerType::CORNER_BR].z > mesh->GetBoundingWorldPos().z)
			return false;

		return true;
	}) >> cpplinq::to_vector();


	if (SubDivide())
	{
		m_pChild[(int)ECornerType::CORNER_FL]->BuildRecursively(m_objects);
		m_pChild[(int)ECornerType::CORNER_FR]->BuildRecursively(m_objects);
		m_pChild[(int)ECornerType::CORNER_BL]->BuildRecursively(m_objects);
		m_pChild[(int)ECornerType::CORNER_BR]->BuildRecursively(m_objects);
	}
}

QuadTree * HyEngine::QuadTree::AddChild(D3DXVECTOR3 cornerFL, D3DXVECTOR3 cornerFR, D3DXVECTOR3 cornerBL, D3DXVECTOR3 cornerBR)
{
	QuadTree* pChild;

	pChild = new QuadTree();
	pChild->m_corner[(int)ECornerType::CORNER_FL] = cornerFL;
	pChild->m_corner[(int)ECornerType::CORNER_FR] = cornerFR;
	pChild->m_corner[(int)ECornerType::CORNER_BL] = cornerBL;
	pChild->m_corner[(int)ECornerType::CORNER_BR] = cornerBR;
	pChild->m_center =
		(
			cornerFL +
			cornerFR +
			cornerBL +
			cornerBR
			) / 4;
	pChild->m_radius = D3DXVec3Length(&(pChild->m_center - cornerFL));

	return pChild;
}

void HyEngine::QuadTree::QuadTreeCullRecursively(Camera * cam)
{
	bool isIn = cam->IsInFrustumWithRadius(D3DXVECTOR3(m_center.x, cam->m_pTransform->m_position.y(), m_center.z), m_radius);

	/* 절두체 밖인 경우  */
	if (isIn == false)
	{
		// 순회할 필요 없음
		return;
	}

	/* 모든 child가  nullptr인 경우 마지막 tree이기 때문에 cull결과를 적용해준다. */
	if (m_pChild[0] == nullptr
		&& m_pChild[1] == nullptr
		&& m_pChild[2] == nullptr
		&& m_pChild[3] == nullptr)
	{
		for (auto& obj : m_objects)
		{
			Mesh* mesh = dynamic_cast<Mesh*>(obj);
			if (mesh == nullptr) continue;


			bool result = cam->IsInFrustumWithRadius(mesh->GetBoundingWorldPos(), mesh->GetBoundingRadius());
			obj->SetViewFrustumCulled(!result);
		}
	}

	if (m_pChild[0])
		m_pChild[0]->QuadTreeCullRecursively(cam);
	if (m_pChild[1])
		m_pChild[1]->QuadTreeCullRecursively(cam);
	if (m_pChild[2])
		m_pChild[2]->QuadTreeCullRecursively(cam);
	if (m_pChild[3])
		m_pChild[3]->QuadTreeCullRecursively(cam);
}

const float QuadTree::MinimumRadius = 1000.0f;