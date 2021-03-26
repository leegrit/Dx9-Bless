#pragma once
#include "GameObject.h"

namespace Editor
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
		void InsertGameData(class GameObjectData* data);
		void InsertMeshData(class MeshData* data);
		void SetEditID(int editID);
		int GetEditID() const;
		EStaticType GetStaticType() const;
	protected :
		// 데이터 업데이트 되었을 때 최신화할 수 있도록 UpdatedData 호출해준다.
		virtual void UpdatedData(EDataType dataType) = 0;

	protected :
		//class EditData* m_pEditData[(int)EDataType::End];
		class GameObjectData* m_pGameObjectData;
		class MeshData* m_pMeshData;
	private :
		int m_editID;
		EStaticType m_staticType;
	};
}

