#include "StandardEngineFramework.h"
#include "Billboard.h"
#include "TextureQuad.h"

HyEngine::Billboard::Billboard(Scene * pScene, GameObject * pParent, std::wstring name)
	:Texture(pScene, pParent, name)
{

}

HyEngine::Billboard::~Billboard()
{
}

void HyEngine::Billboard::Initialize()
{
	Texture::Initialize();
}

void HyEngine::Billboard::Render()
{
	D3DXMATRIX billMat = CalcBillboardY();

	/* Scale문제때문에 scale을 1로 world행렬을 만들고 */
	/* billboard world 를 구성한 후에 scale을 다시 적용한다. */
	D3DXMATRIX tempWorld;
	D3DXMATRIX tempScale;
	D3DXMATRIX tempRot;
	D3DXMATRIX tempPos;
	D3DXMatrixScaling(&tempScale, 1, 1, 1);
	D3DXMatrixRotationYawPitchRoll(&tempRot, D3DXToRadian(m_pTransform->m_rotationEuler.y()), D3DXToRadian(m_pTransform->m_rotationEuler.x()), D3DXToRadian(m_pTransform->m_rotationEuler.z()));
	D3DXMatrixTranslation(&tempPos, m_pTransform->m_position.x(), m_pTransform->m_position.y(), m_pTransform->m_position.z());
	tempWorld = tempScale * tempRot * tempPos;
	D3DXMATRIX scaleMat;
	D3DXMatrixScaling(&scaleMat, m_pTransform->m_scale.x(), m_pTransform->m_scale.y(), m_pTransform->m_scale.z());

	D3DXMATRIX result = billMat * tempWorld;
	result = scaleMat* result;

	m_pEffect->SetMatrix("WorldMatrix", &result);
	m_pEffect->SetValue("ViewMatrix", &CAMERA->GetViewMatrix(), sizeof(D3DXMATRIX));
	m_pEffect->SetMatrix("ProjMatrix", &CAMERA->GetProjectionMatrix());

	/* Set Diffuse */
	D3DXHANDLE diffuseHandle = m_pEffect->GetParameterByName(0, "DiffuseTex");
	m_pEffect->SetTexture(diffuseHandle, m_pDiffuse);

	/* Set Alpha */
	D3DXHANDLE alphaMaskHandle = m_pEffect->GetParameterByName(0, "AlphaMaskTex");
	m_pEffect->SetTexture(alphaMaskHandle, m_pAlphaMask);

	m_pEffect->SetTechnique("Texture");
	m_pEffect->Begin(0, 0);
	{
		m_pEffect->BeginPass(0);

		DEVICE->SetStreamSource(0, m_pTextureQuad->GetVertexBuffer(), 0, m_pTextureQuad->GetVertexSize());
		DEVICE->SetVertexDeclaration(m_pTextureQuad->GetDeclare());
		DEVICE->SetIndices(m_pTextureQuad->GetIndexBuffer());
		DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_pTextureQuad->GetVertexCount(), 0, m_pTextureQuad->GetPrimitiveCount());

		m_pEffect->EndPass();
	}
	m_pEffect->End();

}

void HyEngine::Billboard::Update()
{
	Texture::Update();
}

D3DXMATRIX HyEngine::Billboard::GetBillboardMatrix()
{
	D3DXMATRIX billMat = CalcBillboardY();

	/* Scale문제때문에 scale을 1로 world행렬을 만들고 */
	/* billboard world 를 구성한 후에 scale을 다시 적용한다. */
	D3DXMATRIX tempWorld;
	D3DXMATRIX tempScale;
	D3DXMATRIX tempRot;
	D3DXMATRIX tempPos;
	D3DXMatrixScaling(&tempScale, 1, 1, 1);
	D3DXMatrixRotationYawPitchRoll(&tempRot, D3DXToRadian(m_pTransform->m_rotationEuler.y()), D3DXToRadian(m_pTransform->m_rotationEuler.x()), D3DXToRadian(m_pTransform->m_rotationEuler.z()));
	D3DXMatrixTranslation(&tempPos, m_pTransform->m_position.x(), m_pTransform->m_position.y(), m_pTransform->m_position.z());
	tempWorld = tempScale * tempRot * tempPos;
	D3DXMATRIX scaleMat;
	D3DXMatrixScaling(&scaleMat, m_pTransform->m_scale.x(), m_pTransform->m_scale.y(), m_pTransform->m_scale.z());

	D3DXMATRIX result = billMat * tempWorld;
	result = scaleMat* result;

	return result;
}

D3DXMATRIX HyEngine::Billboard::CalcBillboardY()
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

Billboard * HyEngine::Billboard::Create(Scene * pScene, GameObject * pParent, std::wstring name)
{
	Billboard * obj = new Billboard(pScene, pParent, name);
	obj->Initialize();
	return obj;
}
