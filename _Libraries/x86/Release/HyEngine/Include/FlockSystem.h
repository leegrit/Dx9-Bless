#pragma once

namespace HyEngine
{
	class Transform;
	class FlockAgent;
	class FlockBehaviour;
	class ENGINE_DLL FlockSystem
	{
	public :
		FlockSystem();
		void Update();
		void PushAgent(std::wstring groupName, FlockAgent* flockAgent);
		void ClearAgents();

	private : 
		std::vector<Transform*> GetNearbyObjects(std::wstring groupName, FlockAgent* agent);
	private :
		std::vector<std::wstring> m_groupNames;
		std::unordered_map<std::wstring, std::vector<FlockAgent*>> m_agents;
		FlockBehaviour * m_pBehaviour;

	private :
		float m_driveFactor = 4;
		float m_maxSpeed = 100;

	public :
		float m_avoidDistance = 25;
		float m_neighborDistance = 300;
		float m_flockDelay = 0.5f;
		float m_currentFlockDelay = 0;

	private :
		// 시야각으로 주변 agent를 판단한다.
		float m_radiusFactor = 30;
		// 1 = 45도 늘어날수록 각도가 커짐
		float m_frontViewAngleFactor = 1;
		float m_backViewAngleFactor = 1;

		bool m_bWideView = true;
		bool m_bLimitedView = false;
		bool m_bNarrowView = false;
	};
}