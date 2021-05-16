#include "stdafx.h"
#include "PlayerAfterImage.h"

PlayerAfterImage::PlayerAfterImage(Scene * scene, GameObject * parent, ESkinningType skinningType)
	: DynamicMesh(scene, parent, L"PlayerAfterImage", skinningType)
{

}

PlayerAfterImage::~PlayerAfterImage()
{
}

void PlayerAfterImage::Render()
{
	return;
}

void PlayerAfterImage::PostRender(ID3DXEffect * pEffect)
{
	DynamicMesh::PostRender(pEffect);
}

void PlayerAfterImage::OnRenderBegin(void *)
{
	return;
}

void PlayerAfterImage::OnRenderEnd(void *)
{
	return;
}
