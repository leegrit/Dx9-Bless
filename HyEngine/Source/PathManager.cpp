#include "StandardEngineFramework.h"
#include "PathManager.h"
#include <atlconv.h>
using namespace HyEngine;
IMPLEMENT_SINGLETON(PathManager)

PathManager::PathManager()
{
	wchar_t path[MAX_PATH] = { 0 };

	GetModuleFileName(NULL, path, MAX_PATH);

	std::wstring baseDir(path);

	int tempIndex = baseDir.find(DefaultPath::SolutionName);
	std::wstring tempString = baseDir.substr(0, tempIndex);
	CString::Replace(&tempString, L"\\", L"/");
	tempString = tempString + DefaultPath::SolutionName + L'/';

	m_resourcesPath = tempString + L"_Resources/";
	m_assetsPath = tempString + L"_Resources/Assets/";
	m_datasPath = tempString + L"_Resources/Datas/";
	m_shadersPath = tempString + L"_Shaders/";
	m_librariesPath = tempString + L"_Libraries/";
	bInit = true;
}


std::wstring HyEngine::PathManager::ResourcesPathW()
{
	assert(bInit);
	return m_resourcesPath;
}

std::wstring HyEngine::PathManager::AssetsPathW()
{
	assert(bInit);
	return m_assetsPath;
}

std::wstring HyEngine::PathManager::DatasPathW()
{
	assert(bInit);
	return m_datasPath;
}

std::wstring HyEngine::PathManager::ShadersPathW()
{
	assert(bInit);
	return m_shadersPath;
}

std::wstring HyEngine::PathManager::LibrariesPathW()
{
	assert(bInit);
	return m_librariesPath;
}

std::string HyEngine::PathManager::ResourcesPath()
{
	assert(bInit);
	return CString::ToString(ResourcesPathW());
}

std::string HyEngine::PathManager::AssetsPath()
{
	assert(bInit);
	return CString::ToString(AssetsPathW());
}

std::string HyEngine::PathManager::DatasPath()
{
	assert(bInit);
	return CString::ToString(DatasPathW());
}

 std::string HyEngine::PathManager::ShadersPath()
{
	assert(bInit);
	return CString::ToString(ShadersPathW());
}

std::string HyEngine::PathManager::LibrariesPath()
{
	assert(bInit);
	return CString::ToString(LibrariesPathW());
}
