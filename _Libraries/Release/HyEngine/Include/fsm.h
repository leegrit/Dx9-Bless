#pragma once
#include <unordered_map>
#include <assert.h>


using namespace std;

// 상태를 담고있는 인터페이스 -> 상태를 만들고 이 클래스를 상속받는다
// <T> 는 상태를 들고있는 부모의 클래스를 넣어준다 
template <typename T>
class IState
{
public:
	IState() = default;
	virtual ~IState() {}
public:
	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Late_Update() = 0;
	virtual void Exit() = 0;

	void SetParent(T* _component) { m_component = _component; }
protected:
	T* m_component = nullptr;
};

// FSM 을 관리해주는 최상위 객체
//
// -- 사용법 --
// 이 객체에 add함수를 통해 char* 키와 상태를 넣어준다.
// 그리고 initialize를 호출해 첫번째 시작할 상태를 char* 로 지정해 준다
// Set함수를 통해 바꿀 state를 지정해줄 수 있다.
template<typename T>
class StateController
{
public:
	template<typename S>
	void Add(T * _obj, const char* _stateName);
	// 상태 객체 컨트롤러 초기화 (객체의 포인터, 첫번째 상태 이름) ***주의점*** 모든 상태를 Add함수로 추가한 후 마지막으로 호출해야함
	void Initialize(const char* _startState);
	void Set(const char* _state);
	void Update() const;
	void Late_Update() const;
	void Release();

private:
	IState<T>* m_state = nullptr;
private:
	unordered_map<const char*, IState<T>*> m_stateList;
	// 객체의 생명주기 관리 변수 
	static int m_refCount;
};


template<typename T>
inline void StateController<T>::Initialize(const char * _startState)
{
	assert("StateController func:Initialize is already called" && !m_state);

	++m_refCount; // reference 카운트 증가!

	IState<T>* newState = m_stateList[_startState];
	assert("Please call valid string of State / StateController func:Initialize " && newState);

	m_state = newState;

	m_state->Enter();
}

template<typename T>
inline void StateController<T>::Set(const char * _state)
{
	IState<T>* newState = m_stateList[_state];

	assert("StateController set state Invalid Class name" &&  newState);

	/*if (m_state == newState)
	return;*/

	if (m_state)
		m_state->Exit();

	m_state = newState;

	m_state->Enter();
}


template<typename T>
inline void StateController<T>::Release()
{
	--m_refCount;

	if (0 < m_refCount)
		return;

	for (auto& s : m_stateList)
	{
		//cout << "delete !" << endl;
		IState<T>* pState = s.second;
		if (nullptr != pState)
		{
			delete pState;
			pState = nullptr;
		}
	}
	m_stateList.clear();
}



template<typename T>
inline void StateController<T>::Update() const
{
	assert("StateController' current state is null!" && m_state);

	m_state->Update();


}

template<typename T>
inline void StateController<T>::Late_Update() const
{
	assert("StateController' current state is null!" && m_state);

	m_state->Late_Update();


}

template<typename T>
template<typename S>
inline void StateController<T>::Add(T * _obj, const char * _stateName)
{
	if (nullptr == m_stateList[_stateName])
	{

		S* state = new S;

		state->SetParent(_obj);
		m_stateList[_stateName] = state;
	}
}
//template<typename T>
//unordered_map<const char*, IState<T>*>  StateController<T>::m_stateList;

template<typename T>
int StateController<T>::m_refCount;