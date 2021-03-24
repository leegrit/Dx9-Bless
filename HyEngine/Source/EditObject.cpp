#include "StandardEngineFramework.h"
#include "EditObject.h"
#include "CString.h"
#include "EditData.h"
#include "GameObjectData.h"
#include "MeshData.h"

Editor::EditObject::EditObject(ERenderType renderType, Scene * scene, GameObject * parent, int editID)
	: GameObject(renderType, scene, parent, L"GameObject")
{
	/*m_pEditData
	strcpy_s(m_pGameObjectData.name, 256 ,CString::ToString(GetName()).c_str());
	strcpy_s(m_pGameObjectData.tag, 256, CString::ToString(GetTag()).c_str());
	SetEditID(editID);
	m_pGameObjectData.transform.position = m_pTransform->m_position;
	m_pGameObjectData.transform.rotation = m_pTransform->m_rotationEuler;
	m_pGameObjectData.transform.scale = m_pTransform->m_scale;
	m_pGameObjectData.layer = GetLayer();*/

	SetEditID(editID);
	m_pGameObjectData = nullptr;
	m_pMeshData = nullptr;
}

Editor::EditObject::~EditObject()
{

}

void Editor::EditObject::Render()
{
}

//void Editor::EditObject::InsertData(EditData* data)
//{
//	
//	GameObjectData* gameObjectData = nullptr;
//	gameObjectData = dynamic_cast<GameObjectData*>(data);
//	if (gameObjectData)
//	{
//		SetName(CString::CharToWstring(gameObjectData->name));
//		SetTag(CString::CharToWstring(gameObjectData->tag));
//		m_pTransform->m_position = gameObjectData->transform.position;
//		m_pTransform->m_rotationEuler = gameObjectData->transform.rotation;
//		m_pTransform->m_scale = gameObjectData->transform.scale;
//		SetLayer(gameObjectData->layer);
//
//		m_pEditData[(int)EDataType::GameObjectData] = gameObjectData;
//		UpdatedData(EDataType::GameObjectData);
//		return;
//	}
//
//	MeshData* meshData = nullptr;
//	meshData = dynamic_cast<MeshData*>(data);
//	if (meshData)
//	{
//		m_pEditData[(int)EDataType::MeshData] = meshData;
//		UpdatedData(EDataType::MeshData);
//		return;
//	}
//
//	
//
//}

void Editor::EditObject::InsertGameData(GameObjectData * data)
{
	GameObjectData* gameObjectData = data;
	if (gameObjectData)
	{
		SetName(CString::CharToWstring(gameObjectData->name));
		SetTag(CString::CharToWstring(gameObjectData->tag));
		m_pTransform->m_position = gameObjectData->transform.position;
		m_pTransform->m_rotationEuler = gameObjectData->transform.rotation;
		m_pTransform->m_scale = gameObjectData->transform.scale;
		SetLayer(gameObjectData->layer);

		m_pGameObjectData= gameObjectData;
		UpdatedData(EDataType::GameObjectData);
		return;
	}
}

void Editor::EditObject::InsertMeshData(MeshData * data)
{
	MeshData* meshData = data;
	if (meshData)
	{
		m_pMeshData = meshData;
		UpdatedData(EDataType::MeshData);
		return;
	}
}

void Editor::EditObject::SetEditID(int editID)
{
	m_editID = editID;
}

int Editor::EditObject::GetEditID() const
{
	return m_editID;
}
