#pragma once
#include "GameObject.h"

namespace HyEngine
{
	class ENGINE_DLL GroupMapObject : public GameObject
	{
		//////////////////////////////////////////////////////////////////////////
		// CONSTRUCTOR & DESTRUCTOR
		//////////////////////////////////////////////////////////////////////////
	private :
		explicit GroupMapObject(Scene* scene, GameObject* parent, std::wstring name);
		virtual ~GroupMapObject();


		//////////////////////////////////////////////////////////////////////////
		// INHERITED
		//////////////////////////////////////////////////////////////////////////
	public:
		virtual void Initialize(std::wstring dataPath);
		virtual void Render() override;
		virtual void UpdatedData(EDataType dataType) override;

		static GroupMapObject* Create(Scene* scene, GameObject* parent, std::wstring name, std::wstring dataPath)
		{
			GroupMapObject* mesh = new GroupMapObject(scene, parent, name);
			mesh->Initialize(dataPath);
			return mesh;
		}



	};
}

