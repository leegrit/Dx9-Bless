#pragma once


namespace HyEngine
{

	class ENGINE_DLL Object /*: public IObject*/
	{
	protected:
		explicit Object(std::wstring name);
		virtual ~Object();

	protected:

		//virtual void Initialize() = 0;
	public:
		// ----------------------------------
		// PUBLIC METHODS
		// -----------------------------------
		// onlt editor
		//inline void SetEditID(int index) { m_editID = index; }
		//inline int GetEditID() { return m_editID; }
		inline LONGLONG GetInstanceID() { return m_id; }
		inline 	bool CompareName(std::wstring name) { return m_name == name; }
		//std::wstring ToString() { return m_name; }

		inline std::wstring GetName() const { return m_name; }
		inline void SetName(std::wstring name) { m_name = name; }

	public :

		// -----------------------------------
		// STATIC METHODS
		// -----------------------------------
		static void Destroy(Object* obj)
		{
			if(obj)
				obj->m_bWantsDestroy = true;
		}
		// this function must be called by scene.
		static void DestroyImmediate(Object* obj)
		{
			SAFE_DELETE(obj);
		}
		// ------------------------------------
		// OPERATORS
		// -----------------------------------
		//inline bool operator != (Object* other) { return this->GetInstanceID() != other->GetInstanceID(); }
		//inline bool operator == (Object* other) { return this->GetInstanceID() == other->GetInstanceID(); }

	private :

	private:
		std::wstring m_name;
		LONGLONG m_id;
		//int m_editID; // only editor


	public:
		bool m_bWantsDestroy;


	};
}