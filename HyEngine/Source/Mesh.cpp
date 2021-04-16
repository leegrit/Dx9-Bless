#include "StandardEngineFramework.h"
#include "Mesh.h"

HyEngine::Mesh::Mesh(ERenderType renderType, Scene * scene, GameObject * parent, std::wstring name)
	: GameObject(ERenderType::RenderOpaque, scene, parent, name)
{
}

HyEngine::Mesh::~Mesh()
{
}

void HyEngine::Mesh::Render()
{
}

void HyEngine::Mesh::DrawPrimitive(ID3DXEffect* pShader)
{

}

void HyEngine::Mesh::UpdatedData(EDataType dataType)
{

}

bool HyEngine::Mesh::ComputeBoundingSphere(D3DXVECTOR3 * center, float * radius)
{
	*center = D3DXVECTOR3(0, 0, 0);
	*radius = 0;
	return false;
}
