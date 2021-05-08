#pragma once

namespace HyEngine
{

	class UIDGen
	{
		DECLARE_SINGLETON(UIDGen)

	private:
		UIDGen();
		~UIDGen();
	public:
		LONGLONG GetUID();
	private:
		static LONGLONG nextID;
	};

}