#pragma once


namespace HyEngine
{
	// ���� ������Ʈ �� ���� ������ �׷��� �� �ֱ� ������
	// Renderable �������̽��� ���� ���� 
	// Renderer������ �� �������̽��� ��ӹ��� Ŭ������ �׸���.
	__interface ENGINE_DLL IRenderable
	{
		virtual void Render() = 0;
	};
}
