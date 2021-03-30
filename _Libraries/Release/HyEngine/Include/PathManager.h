#pragma once

namespace HyEngine
{
	class ENGINE_DLL PathManager
	{
		DECLARE_SINGLETON(PathManager)
		//////////////////////////////////////////////////////////////////////////
		// CONSTRUCTOR & DESTRUCTOR
		//////////////////////////////////////////////////////////////////////////
	private :
		PathManager();
		~PathManager() = default;

		//////////////////////////////////////////////////////////////////////////
		// GETTER
		//////////////////////////////////////////////////////////////////////////
	public:
		/* For wstring */
		std::wstring ResourcesPathW();
		std::wstring AssetsPathW();
		std::wstring DatasPathW();
		std::wstring ShadersPathW();
		std::wstring LibrariesPathW();

		/* for string */
		 std::string ResourcesPath();
		 std::string AssetsPath();
		 std::string DatasPath();
		 std::string ShadersPath();
		 std::string LibrariesPath();
	private :
		bool bInit;
	
		std::wstring m_resourcesPath;
		std::wstring m_assetsPath;
		std::wstring m_datasPath;
		std::wstring m_shadersPath;
		std::wstring m_librariesPath;
	};

#define PATH PathManager::Get()
}