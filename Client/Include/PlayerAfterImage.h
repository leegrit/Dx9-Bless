#pragma once
#include "DynamicMesh.h"

using namespace HyEngine;
class PlayerAfterImage : public DynamicMesh
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR
	//////////////////////////////////////////////////////////////////////////
protected :
	explicit PlayerAfterImage(Scene* scene, GameObject* parent,  ESkinningType skinningType = ESkinningType::SoftwareSkinning);
	virtual ~PlayerAfterImage();

	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public :
	virtual void Render() override;
	virtual void PostRender(ID3DXEffect* pEffect) override;
	virtual void OnRenderBegin(void*) override;
	virtual void OnRenderEnd(void*) override;


	static PlayerAfterImage* Create(Scene* scene, GameObject* parent,  std::wstring dataPath, ESkinningType skinningType = ESkinningType::SoftwareSkinning)
	{
		PlayerAfterImage* mesh = new PlayerAfterImage(scene, parent, skinningType);
		mesh->Initialize(dataPath);
		return mesh;
	}
};

