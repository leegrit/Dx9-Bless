#pragma once


namespace HyEngine
{

		using namespace std;
		class ENGINE_DLL EventController
		{
		private:
			unordered_map<string, vector<std::pair<std::string, function<void(void*)>>>> m_theRouter;

			vector<string> m_permanentEvents;

		public:
			unordered_map<string, vector<std::pair<std::string, function<void(void*)>>>>& GetRouter()
			{
				return m_theRouter;
			}

			void MarkAsPermanent(string eventType)
			{
				m_permanentEvents.push_back(eventType);
			}

			// 해당 키값이 m_theRouter안에 있는지 확인
			bool ContainsEvent(string eventType)
			{
				for (auto pair : m_theRouter)
				{
					if (pair.first == eventType)
						return true;
				}
				return false;
			}

			void Cleaup()
			{
				vector<string> eventToRemove;

				for (auto pair : m_theRouter)
				{
					bool wasFound = false;
					for (auto Event : m_permanentEvents)
					{
						if (pair.first == Event)
						{
							wasFound = true;
							break;
						}
					}
					if (!wasFound)
						eventToRemove.push_back(pair.first);
				}
				for (auto Event : eventToRemove)
				{
					m_theRouter.erase(Event);
				}
			}

			void AddEventListener(string eventType,string key, function<void(void* arg)> handler)
			{
				auto router = m_theRouter[eventType];
				router.push_back(std::make_pair(key, handler));
				m_theRouter[eventType] = router;
			}
			void RemoveEventListener(string eventType, string key)
			{
				auto events = m_theRouter[eventType];

				for (UINT i = 0; i < (int)events.size(); i++)
				{
					if (events[i].first == key)
					{
						events.erase(events.begin() + i);
					}
				}
				m_theRouter[eventType] = events;
			}
			// 함수 비교가 불가능해서 
			// 특정 함수만 제거할 수 없음
			/*void RemoveEventListener(string eventType, function<void(void)> handler)
			{
			if (ContainsEvent(eventType))
			{
			auto router = m_theRouter[eventType];
			for (UINT i = 0; i < router.size(); i++)
			{

			}
			}
			}*/


			void TriggerEvent(string eventType, void* arg = nullptr)
			{
				vector<function<void(void*)>> functionVec;

				if (!ContainsEvent(eventType))
					return;

				auto callbacks = m_theRouter[eventType];
				
				for (auto callback : callbacks)
				{
					try
					{
						callback.second(arg);
					}
					catch (exception e)
					{
						continue;
					}
				}
			}
		};

		class ENGINE_DLL EventDispatcher
		{
		public:
			static  EventController m_eventController;

		public:
			static unordered_map<string, vector<std::pair<std::string, function<void(void*)>>>>& GetRouter()
			{
				return m_eventController.GetRouter();
			}

			static void MarkAsPermanent(string eventType)
			{
				m_eventController.MarkAsPermanent(eventType);
			}

			static void Cleanup()
			{
				m_eventController.Cleaup();
			}

			static void AddEventListener(string eventType,string key, function<void(void* arg)> handler)
			{
				m_eventController.AddEventListener(eventType, key, handler);
			}
			static void RemoveEventListener(string eventType, string key)
			{
				m_eventController.RemoveEventListener(eventType, key);
			}

			static void TriggerEvent(string eventType)
			{
				m_eventController.TriggerEvent(eventType);
			}
			static void TriggerEvent(string eventType, void* arg)
			{
				m_eventController.TriggerEvent(eventType, arg);
			}
		};

	

}