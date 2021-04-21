#pragma once


namespace HyEngine
{
	class ENGINE_DLL UpdateDispatcher
	{
	public :
		enum UpdateState
		{
			Continue = 0,
			End,
		};
		static void Dispatch(std::function<UpdateState()> onUpdate, std::function<void()> onCompleted)
		{
			updates.push_back(onUpdate);
			onCompletes.push_back(onCompleted);
		}
		static void Update()
		{
			for (UINT i = 0; i < updates.size(); i++)
			{
				// true반환하면 끝
				if (updates[i]() == End)
				{
					onCompletes[i]();
					updates.erase(updates.begin() + i);
					onCompletes.erase(onCompletes.begin() + i);
				}
			}
		}

	private :
		static std::vector<std::function<UpdateState()>> updates;
		static std::vector<std::function<void()>> onCompletes;
	};
}

