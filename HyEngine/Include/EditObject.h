#pragma once
#include "GameObject.h"

namespace HyEngine
{
	class EditObject : public GameObject
	{
	protected:
		EditObject() = delete;
		explicit EditObject(ERenderType renderType, Scene* scene, GameObject* parent, int editID);
		virtual ~EditObject();
	public:
		//virtual void Initialize();
		virtual void Render() override;

	public :
// 		void InsertGameData(class GameObjectData* data);
// 		void InsertMeshData(class MeshData* data);
		
		//EStaticType GetStaticType() const;
	protected :
		// ������ ������Ʈ �Ǿ��� �� �ֽ�ȭ�� �� �ֵ��� UpdatedData ȣ�����ش�.
		//virtual void UpdatedData(EDataType dataType) = 0;

	protected :
		//class EditData* m_pEditData[(int)EDataType::End];
		//class GameObjectData* m_pGameObjectData;
		//class MeshData* m_pMeshData;
	private :
		//int m_editID;
		//EStaticType m_staticType;
	};
}

