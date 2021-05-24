#pragma once
#include "GameObject.h"


struct DamageFontDesc
{
	friend class DamageFontScatter;
public :
	std::wstring font; // damage
	bool isPlayer;
	bool isCritical;
	D3DXVECTOR3 position;
	float m_elapsed = 0;
	FontDesc fontDesc;

private :
	float size = 1; 
	D3DXVECTOR3 dir = D3DXVECTOR3(0, 0 ,0);
	float speed = 1.0f;


};
class DamageFontScatter  : public GameObject
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
protected  :
	explicit DamageFontScatter(Scene* pScene, std::wstring name);
	virtual ~DamageFontScatter();

	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public :
	virtual void Render() override;
	virtual void Update() override;


	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	void Initialize();
	void PushDamageFunt(float damage, bool isPlayer, bool isCritical, D3DXVECTOR3 center);
	void PushDamageFontForPlayer(float damage, bool isCritical, bool isGaurd, D3DXVECTOR3 center);


	//////////////////////////////////////////////////////////////////////////
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
private:
	std::vector<DamageFontDesc> m_damageFonts;
	float m_radius = 5;

private : /* for fade effect  */
	const float m_speed = 1;
	const float m_delay = 1.5f;
	const float m_fadeInTime = 0.2f;
	const float m_fadeOutTime = 0.5f;


	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	static DamageFontScatter* Create(Scene* pScene, std::wstring name);

};

