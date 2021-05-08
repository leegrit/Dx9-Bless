#pragma once
#include "GameObject.h"

namespace HyEngine
{
	/* 임시 */
	// 이름이 겹쳐서 잠시 Element2로 했지만 나중에 변경해야한다.
	// 나중에 ui 만들기 위한 깡통
	class ENGINE_DLL  UIElement2 abstract : public GameObject
	{
		//////////////////////////////////////////////////////////////////////////
		// CONSTRUCTOR & DESTRUCTOR
		//////////////////////////////////////////////////////////////////////////
	protected:
		/* For Editor */
		explicit UIElement2(Scene * scene, GameObject* parent, int editID);
		explicit UIElement2(Scene* scene, GameObject * parent);
		virtual ~UIElement2();

		//////////////////////////////////////////////////////////////////////////
		// INHERITED
		//////////////////////////////////////////////////////////////////////////
	public :
		virtual void Initialize();
		virtual void Initialize(std::wstring dataPath);
		virtual void Render() override;
		virtual void UpdatedData(EDataType dataType) override;

		//////////////////////////////////////////////////////////////////////////
		// VARIABLES
		//////////////////////////////////////////////////////////////////////////
	private :
		class TextureQuad * m_pTextureQuad;

		//////////////////////////////////////////////////////////////////////////
		// FACTORY METHOD
		//////////////////////////////////////////////////////////////////////////
	public :
		/* For Editor */
		static UIElement2 * Create(Scene * scene, GameObject* parent, int editID);
		/* For Client */
		static UIElement2 * Create(Scene* scene, GameObject * parent, std::wstring dataPath);
	};
}

