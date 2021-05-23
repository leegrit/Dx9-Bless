#pragma once
#include "GameObject.h"
#include "InteractManager.h"

namespace HyEngine
{
	class Billboard;
}
using namespace HyEngine;
class SpoilsObject : public GameObject
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
protected :
	explicit SpoilsObject(Scene* pScene, std::wstring name, SpoilsObjectDesc desc);
	virtual ~SpoilsObject();

	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public:
	virtual void Initialize();
	virtual void Update() override;

	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHOD
	//////////////////////////////////////////////////////////////////////////

	void Collecting(_Out_ bool * bEnd);
	void OutOfRange();
public :
	virtual void DoCollect();
	virtual void OnCollected();
	virtual void OnCollectBegin();
	virtual void OnCollectEnd();

private:
	Billboard* m_pBillboard = nullptr;
	float m_elpased = -20;
private :
	float m_interactRadius = 30;
	bool m_bCollecting = false;
	bool m_bCollectable = true;

	SpoilsObjectDesc m_desc;
	class InventoryData * m_pInventoryData = nullptr;
	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public:
	static SpoilsObject* Create(Scene* pScene, std::wstring name, SpoilsObjectDesc desc );
};

