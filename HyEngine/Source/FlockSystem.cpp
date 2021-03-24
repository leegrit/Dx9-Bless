#include "StandardEngineFramework.h"
#include "FlockSystem.h"
#include "FlockAgent.h"
#include "CompositeBehaviour.h"

HyEngine::FlockSystem::FlockSystem()
{
	m_pBehaviour = new CompositeBehaviour();
}

void HyEngine::FlockSystem::Update()
{
	for (auto& groupName : m_groupNames)
	{
		for (auto& agent : m_agents[groupName])
		{
			std::vector<Transform*> context = GetNearbyObjects(groupName, agent);

			Vector3 move = m_pBehaviour->CalculateMove(agent, context, this);
			move = move* m_driveFactor;

			agent->Move(move);
		}
	}
}

void HyEngine::FlockSystem::PushAgent(std::wstring groupName, FlockAgent* flockAgent)
{
	bool bExist = false;
	for(auto& name : m_groupNames)
	{
		if (name == groupName)
		{
			bExist = true;
			break;
		}
	}
	if (bExist == false)
		m_groupNames.push_back(groupName);
	auto& iter =  m_agents.find(groupName);
	if (iter == m_agents.end())
	{
		std::vector<FlockAgent*> agents;
		agents.push_back(flockAgent);
		m_agents.insert(std::make_pair(groupName, agents));
	}
	else
	{
		m_agents[groupName].push_back(flockAgent);
	}
}

void HyEngine::FlockSystem::ClearAgents()
{
	m_agents.clear();
}

std::vector<Transform*> HyEngine::FlockSystem::GetNearbyObjects(std::wstring groupName, FlockAgent * agent)
{
	std::vector<Transform*> context;

	for (auto& unit : m_agents[groupName])
	{
		if (unit == agent) continue;

		if (D3DXVec3Length(&(agent->GetTransform()->m_position - unit->GetTransform()->m_position).operator D3DXVECTOR3()) < m_neighborDistance)
			context.push_back(unit->GetTransform());

//		Vector3 dir = unit->GetTransform()->m_position - agent->GetTransform()->m_position;
//#pragma region Rotation Logic
//		D3DXMATRIX rotationMat;
//		D3DXMATRIX positionMat;
//		D3DXMatrixTranslation(&positionMat, dir.x(), dir.y(), dir.z());
//		D3DXMatrixRotationQuaternion(&rotationMat, &unit->GetTransform()->m_rotation.operator D3DXQUATERNION());
//		D3DXMATRIX result = positionMat * rotationMat;
//		D3DXVec3TransformCoord(&dir.operator D3DXVECTOR3(), &Vector3::Zero, &result);
//#pragma endregion
//		bool inView;
//		if (m_bWideView)
//		{
//			inView =  ((dir.y() > 0))
//		}

	}

	return context;
}
