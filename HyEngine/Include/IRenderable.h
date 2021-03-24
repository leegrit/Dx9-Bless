#pragma once


namespace HyEngine
{
	// 게임 오브젝트 외 여러 종류가 그려질 수 있기 때문에
	// Renderable 인터페이스를 따로 뺐고 
	// Renderer에서는 이 인터페이스를 상속받은 클래스만 그린다.
	__interface ENGINE_DLL IRenderable
	{
		virtual void Render() = 0;
	};
}
