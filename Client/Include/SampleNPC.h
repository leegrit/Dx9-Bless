#pragma once
#include "NonePlayer.h"


class SampleNPC : public NonePlayer
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
protected :
	explicit SampleNPC(Scene* pScene);
	virtual ~SampleNPC();

	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public:
	virtual void Initialize(std::wstring dataPath) override;
	virtual void QuestInitialize() override;
	virtual void Update() override;
	virtual std::wstring GetCharacterName() override;
	virtual std::wstring GetSubTitle() override;
	virtual std::wstring GetOnlyCharacterName() override;



	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	static SampleNPC* Create(Scene* scene, std::wstring dataPath)
	{
		SampleNPC* npc = new SampleNPC(scene);
		npc->Initialize(dataPath);
		return npc;
	}
 };

