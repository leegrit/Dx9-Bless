#pragma once
#include "GameObject.h"

namespace HyEngine
{

	/* LightObject는 Editor를 위한 오브젝트, 통일성을 위해 사용된다.            */
	class ENGINE_DLL LightObject : public GameObject
	{
		//////////////////////////////////////////////////////////////////////////
		// CONSTRUCTOR & DESTRUCTOR
		//////////////////////////////////////////////////////////////////////////
	private :
		LightObject(Scene* scene, GameObject* parent, int editID);
		LightObject(Scene* scene, GameObject* parent);
		virtual ~LightObject();

		//////////////////////////////////////////////////////////////////////////
		// INITIALIZER
		//////////////////////////////////////////////////////////////////////////
	private :
		void Initialize();
		void Initialize(std::wstring dataPath);
		

		//////////////////////////////////////////////////////////////////////////
		// INHERITED
		//////////////////////////////////////////////////////////////////////////
	public :
		virtual void Update() override;
		virtual void UpdatedData(EDataType dataType) override;
		virtual void OnEnable() override;
		virtual void OnDisable() override;

		//////////////////////////////////////////////////////////////////////////
		// VARIABLES
		//////////////////////////////////////////////////////////////////////////
	private :
		Light* m_pLight = nullptr;
		
		//////////////////////////////////////////////////////////////////////////
		// FACTORY METHOD
		//////////////////////////////////////////////////////////////////////////
	public :
		static LightObject* Create(Scene* scene, GameObject* parent, int editID)
		{
			LightObject* obj = new LightObject(scene, parent, editID);
			obj->Initialize();
			return obj;
		}
		static LightObject * Create(Scene* scene, GameObject * parent, std::wstring dataPath)
		{
			LightObject * obj = new LightObject(scene, parent);
			obj->Initialize(dataPath);
			return obj;
		}
	};

}

