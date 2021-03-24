#pragma once

namespace HyEngine
{
	class FlockSystem;
	class ENGINE_DLL FlockAgent
	{
	public :
		virtual void Move(Vector3 velocity) = 0;
		virtual Transform* GetTransform() = 0;

		void MoveDefault(Vector3 velocity);

		void SetFlock(FlockSystem* flock);
	private :
		FlockSystem* m_pAgentFlock;

	public :
		Vector3 m_currentVelocity = Vector3::Zero;
		Vector3 m_randomDir = Vector3::Zero;
		float m_currentRandomDelay = 0;
	};
}

