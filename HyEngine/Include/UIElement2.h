#pragma once
#include "GameObject.h"

namespace HyEngine
{
	/* �ӽ� */
	// �̸��� ���ļ� ��� Element2�� ������ ���߿� �����ؾ��Ѵ�.
	// ���߿� ui ����� ���� ����
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

