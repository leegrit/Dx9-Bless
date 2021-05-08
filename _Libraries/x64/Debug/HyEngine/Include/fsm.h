#pragma once
#include <unordered_map>
#include <assert.h>


using namespace std;

// ���¸� ����ִ� �������̽� -> ���¸� ����� �� Ŭ������ ��ӹ޴´�
// <T> �� ���¸� ����ִ� �θ��� Ŭ������ �־��ش� 
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

// FSM �� �������ִ� �ֻ��� ��ü
//
// -- ���� --
// �� ��ü�� add�Լ��� ���� char* Ű�� ���¸� �־��ش�.
// �׸��� initialize�� ȣ���� ù��° ������ ���¸� char* �� ������ �ش�
// Set�Լ��� ���� �ٲ� state�� �������� �� �ִ�.
template<typename T>
class StateController
{
public:
	template<typename S>
	void Add(T * _obj, const char* _stateName);
	// ���� ��ü ��Ʈ�ѷ� �ʱ�ȭ (��ü�� ������, ù��° ���� �̸�) ***������*** ��� ���¸� Add�Լ��� �߰��� �� ���������� ȣ���ؾ���
	void Initialize(const char* _startState);
	void Set(const char* _state);
	void Update() const;
	void Late_Update() const;
	void Release();

private:
	IState<T>* m_state = nullptr;
private:
	unordered_map<const char*, IState<T>*> m_stateList;
	// ��ü�� �����ֱ� ���� ���� 
	static int m_refCount;
};


template<typename T>
inline void StateController<T>::Initialize(const char * _startState)
{
	assert("StateController func:Initialize is already called" && !m_state);

	++m_refCount; // reference ī��Ʈ ����!

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