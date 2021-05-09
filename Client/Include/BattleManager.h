#pragma once

class BattleManager
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR 
	//////////////////////////////////////////////////////////////////////////
public :
	BattleManager(Scene* pScene);
	~BattleManager();

	//////////////////////////////////////////////////////////////////////////
	// CALLBACK
	//////////////////////////////////////////////////////////////////////////
public :


	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	void Initialize();
	void Update();

	GameObject* GetFocusedObject() const;

	//////////////////////////////////////////////////////////////////////////
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
private:
	class GameScene * m_pScene = nullptr;
	float m_maxRadius = 100;

private : /* For Focus */
	GameObject* m_pFocusedObj = nullptr;
};

