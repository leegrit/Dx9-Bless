#include "stdafx.h"
#include "Helper.h"

D3DXMATRIX Helper::CalcBillboardY(D3DXMATRIX viewMatrix)
{
	D3DXMATRIX matView = viewMatrix;

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

D3DXMATRIX Helper::GetWorldToBillboard(D3DXVECTOR3 position, D3DXVECTOR3 rotationEuler, D3DXVECTOR3 scale, D3DXMATRIX viewMatrix)
{
	D3DXMATRIX billMat = Helper::CalcBillboardY(viewMatrix);

	/* Scale문제때문에 scale을 1로 world행렬을 만들고 */
	/* billboard world 를 구성한 후에 scale을 다시 적용한다. */
	D3DXMATRIX tempWorld;
	D3DXMATRIX tempScale;
	D3DXMATRIX tempRot;
	D3DXMATRIX tempPos;
	D3DXMatrixScaling(&tempScale, 1, 1, 1);
	D3DXMatrixRotationYawPitchRoll(&tempRot, D3DXToRadian(rotationEuler.y), D3DXToRadian(rotationEuler.x), D3DXToRadian(rotationEuler.z));
	D3DXMatrixTranslation(&tempPos, position.x,position.y, position.z);
	tempWorld = tempScale * tempRot * tempPos;
	D3DXMATRIX scaleMat;
	D3DXMatrixScaling(&scaleMat, scale.x, scale.y, scale.z);

	D3DXMATRIX result = billMat * tempWorld;
	result = scaleMat* result;

	return result;
}
