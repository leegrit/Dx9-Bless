#include "StandardEngineFramework.h"
#include "ZBillboardObject.h"

HyEngine::ZBillboardObject::ZBillboardObject(Scene * scene, GameObject* parent, EBillboardType billboardType, std::wstring imageFilePath, std::wstring tag)
	: ZTextureObject(scene, parent, ERenderType::RenderOpaque, imageFilePath, tag)
{
	m_billboardType = billboardType;
}

HyEngine::ZBillboardObject::~ZBillboardObject()
{
}

void HyEngine::ZBillboardObject::Initialize()
{
	ZTextureObject::Initialize();
}

void HyEngine::ZBillboardObject::Render()
{
	ZTextureObject::Render();
	D3DXMATRIX billMat;
	switch (m_billboardType)
	{
	case EBillboardType::All:
		billMat = CalcBillboardAll();
		break;
	case EBillboardType::X:
		billMat = CalcBillboardX();
		break;
	case EBillboardType::Y:
		billMat = CalcBillboardY();
		break;
	case EBillboardType::Z:
		billMat = CalcBillboardZ();
		break;
	default:
		assert(false);
		break;
	}

	D3DXMATRIX tempWorld;
	D3DXMATRIX tempScale;
	D3DXMATRIX tempRot;
	D3DXMATRIX tempPos;
	D3DXMatrixScaling(&tempScale, 1, 1, 1);
	D3DXMatrixRotationQuaternion(&tempRot, &m_pTransform->m_rotation.operator D3DXQUATERNION());
	D3DXMatrixTranslation(&tempPos, m_pTransform->m_position.x(), m_pTransform->m_position.y(), m_pTransform->m_position.z());
	tempWorld = tempScale * tempRot * tempPos;
	D3DXMATRIX scaleMat;
	D3DXMatrixScaling(&scaleMat, m_pTransform->m_scale.x(), m_pTransform->m_scale.y(), m_pTransform->m_scale.z());

	D3DXMATRIX result = billMat * tempWorld;
	result = scaleMat* result;

	m_pEffect->SetValue("WorldMatrix", result, sizeof(D3DXMATRIX));

}

D3DXMATRIX HyEngine::ZBillboardObject::CalcBillboardAll()
{
	D3DXMATRIX matView = CAMERA->GetViewMatrix();
	D3DXMATRIX matWorld = m_pTransform->GetWorldMatrix();

	D3DXMATRIX matBill;
	D3DXMatrixIdentity(&matBill);

	memcpy(&matBill.m[0][0], &matView.m[0][0], sizeof(D3DXVECTOR3));
	memcpy(&matBill.m[1][0], &matView.m[1][0], sizeof(D3DXVECTOR3));
	memcpy(&matBill.m[2][0], &matView.m[2][0], sizeof(D3DXVECTOR3));


	/* 역행렬 반환 */
	D3DXMatrixInverse(&matBill, 0, &matBill);

	//matBill._11 /= matWorld._11;
	//matBill._22 /= matWorld._22;
	//matBill._33 /= matWorld._33;
	return matBill;
}

D3DXMATRIX HyEngine::ZBillboardObject::CalcBillboardX()
{
	D3DXMATRIX matView = CAMERA->GetViewMatrix();


	D3DXMATRIX matBillX;
	D3DXMatrixIdentity(&matBillX);

	matBillX._22 = matView._22;
	matBillX._23 = matView._23;
	matBillX._32 = matView._32;
	matBillX._33 = matView._33;

	/* 역행렬 반환 */
	D3DXMatrixInverse(&matBillX, 0, &matBillX);

	return matBillX;
}

D3DXMATRIX HyEngine::ZBillboardObject::CalcBillboardY()
{
	D3DXMATRIX matView = CAMERA->GetViewMatrix();


	D3DXMATRIX matBillY;
	D3DXMatrixIdentity(&matBillY);

	matBillY._11 = matView._11;
	matBillY._13 = matView._13;
	matBillY._31 = matView._31;
	matBillY._33 = matView._33;


	/* 역행렬 반환 */
	D3DXMatrixInverse(&matBillY, 0, &matBillY);

	return matBillY;
}

D3DXMATRIX HyEngine::ZBillboardObject::CalcBillboardZ()
{
	D3DXMATRIX matView = CAMERA->GetViewMatrix();


	D3DXMATRIX matBillZ;
	D3DXMatrixIdentity(&matBillZ);

	matBillZ._11 = matView._11;
	matBillZ._12 = matView._12;
	matBillZ._21 = matView._21;
	matBillZ._22 = matView._22;



	/* 역행렬 반환 */
	D3DXMatrixInverse(&matBillZ, 0, &matBillZ);

	return matBillZ;
}
