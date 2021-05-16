#include "stdafx.h"
#include "WeaponAfterImage.h"



WeaponAfterImage::WeaponAfterImage(Scene * pScene, GameObject * pOwner)
	: Equipment(pScene, pOwner, L"WeaponAfterImage")
{
}

WeaponAfterImage::~WeaponAfterImage()
{
}

void WeaponAfterImage::Render()
{
	return;
}

void WeaponAfterImage::DrawPrimitive(ID3DXEffect * pShader)
{
	pShader->SetValue("WorldMatrix", &m_worldMat, sizeof(m_worldMat));
	pShader->CommitChanges();

	m_pMesh->DrawSubset(0);
}

void WeaponAfterImage::SetWorldMatrix(D3DXMATRIX mat)
{
	m_worldMat = mat;
}

WeaponAfterImage * WeaponAfterImage::Create(Scene * pScene, GameObject * pOwner, std::wstring xFilePath, std::wstring boneName)
{
	WeaponAfterImage* obj = new WeaponAfterImage(pScene, pOwner);
	obj->Initialize(xFilePath, boneName);
	return obj;
}

