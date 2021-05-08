#pragma once

namespace HyEngine
{
	class ENGINE_DLL IMesh abstract
	{
	public:
		virtual void Load(std::string filePath) = 0;

	};

}