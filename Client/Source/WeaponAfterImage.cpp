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
	D3DXMATRIX worldMat = m_pTransform->GetWorldMatrix() * m_parentMat;
	pShader->SetValue("WorldMatrix", &worldMat, sizeof(worldMat));
	pShader->CommitChanges();

	m_pMesh->DrawSubset(0);
}

void WeaponAfterImage::SetWorldMatrix(D3DXMATRIX mat)
{
	m_worldMat = mat;
}

void WeaponAfterImage::Reset(Equipment * pOrigin)
{
	m_parentMat = pOrigin->GetParentBoneMatrix() * pOrigin->GetParentWorldMatrix();
	m_pTransform->m_position = pOrigin->m_pTransform->m_position;
	m_pTransform->m_rotationEuler = pOrigin->m_pTransform->m_rotationEuler;
	m_pTransform->m_scale = pOrigin->m_pTransform->m_scale;
}

void WeaponAfterImage::SetScale(D3DXVECTOR3 scale)
{
	m_afterImageScale = scale;
}

WeaponAfterImage * WeaponAfterImage::Create(Scene * pScene, GameObject * pOwner, std::wstring xFilePath, std::wstring boneName)
{
	WeaponAfterImage* obj = new WeaponAfterImage(pScene, pOwner);
	obj->Initialize(xFilePath, boneName);
	return obj;
}

