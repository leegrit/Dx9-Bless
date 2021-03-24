
#include "StandardEngineFramework.h"
#include "Path.h"
#include "CString.h"

using namespace HyEngine::Utility;

bool Path::ExistFile(string path)
{
	return ExistFile(CString::ToWstring(path));
}

bool Path::ExistFile(wstring path)
{

	DWORD fileValue = GetFileAttributes(path.c_str());
	// ���� ������ �������� �ʴ´ٸ� 0xFFFFFFFF�� ��ȯ�޴´�.
	return fileValue < 0xFFFFFFFF;
}

bool Path::ExistDirectory(string path)
{
	return ExistDirectory(CString::ToWstring(path));
}

bool Path::ExistDirectory(wstring path)
{

	DWORD attribute = GetFileAttributes(path.c_str());

	// ������ �����ϰ� ��ȯ���� attribute�� directory�� ��� true��ȯ
	BOOL temp = (attribute != INVALID_FILE_ATTRIBUTES &&
		(attribute & FILE_ATTRIBUTE_DIRECTORY));


	return temp == TRUE;
}

string Path::Combine(string path1, string path2)
{
	return path1 + path2;
}

wstring Path::Combine(wstring path1, wstring path2)
{
	return path1 + path2;
}

string Path::Combine(vector<string> paths)
{
	string temp = "";
	for (string path : paths)
		temp += path;

	return temp;
}

wstring Path::Combine(vector<wstring> paths)
{
	wstring temp = L"";
	for (wstring path : paths)
		temp += path;

	return temp;
}

string Path::GetDirectoryName(string path)
{
	CString::Replace(&path, "\\", "/");
	size_t index = path.find_last_of('/');

	return path.substr(0, index + 1);
}

wstring Path::GetDirectoryName(wstring path)
{
	CString::Replace(&path, L"\\", L"/");
	size_t index = path.find_last_of('/');

	return path.substr(0, index + 1);
}

string Path::GetExtension(string path)
{
	CString::Replace(&path, "\\", "/");
	size_t index = path.find_last_of('.');

	return path.substr(index + 1, path.length());;
}

wstring Path::GetExtension(wstring path)
{
	CString::Replace(&path, L"\\", L"/");
	size_t index = path.find_last_of('.');

	return path.substr(index + 1, path.length());;
}

string Path::GetFileName(string path)
{
	CString::Replace(&path, "\\", "/");
	size_t index = path.find_last_of('/');

	return path.substr(index + 1, path.length());
}

wstring Path::GetFileName(wstring path)
{
	CString::Replace(&path, L"\\", L"/");
	size_t index = path.find_last_of('/');

	return path.substr(index + 1, path.length());
}

string Path::GetFileNameWithoutExtension(string path)
{
	string fileName = GetFileName(path);

	size_t index = fileName.find_last_of('.');
	return fileName.substr(0, index);
}

wstring Path::GetFileNameWithoutExtension(wstring path)
{
	wstring fileName = GetFileName(path);

	size_t index = fileName.find_last_of('.');
	return fileName.substr(0, index);
}

const WCHAR* Path::ImageFilter = L"Image\0*.png;*.bmp;*.jpg";
const WCHAR* Path::ShaderFilter = L"HLSL file\0*.hlsl";
const WCHAR* Path::TextFilter = L"Text file\0*.txt";
const WCHAR* Path::TileFilter = L"Tile file\0*.png;*.bmp;*.jpg;*.json;*.data";
const WCHAR* Path::TMapFilter = L"TMap file\0*.tmap";
// top down shooter data / tdsd
const WCHAR* Path::TDSDFilter = L"TDS file\0*.tdsd";

// ������ ���ϴ�.
void Path::OpenFileDialog(wstring file, const WCHAR* filter, wstring folder, function<void(wstring)> func, HWND hwnd)
{
	WCHAR name[255];
	wcscpy_s(name, file.c_str());

	wstring tempFolder = folder;

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = name;
	ofn.lpstrFileTitle = (LPWSTR)L"�ҷ�����";
	ofn.nMaxFile = 255;
	ofn.lpstrInitialDir = tempFolder.c_str();
	ofn.Flags = OFN_NOCHANGEDIR;

	// ���ڷ� ���� ��θ� �ҷ����µ� �����ϸ�
	// �ݹ����� ������ ���� �̸��� ��ȯ�մϴ�.
	if (GetOpenFileName(&ofn) == TRUE)
	{
		if (func != NULL)
		{
			wstring loadName = name;
			CString::Replace(&loadName, L"\\", L"/");

			func(loadName);
		}
	}
}

void Path::SaveFileDialog(wstring file, const WCHAR* filter, wstring folder, function<void(wstring)> func, HWND hwnd)
{
	WCHAR name[255];
	wcscpy_s(name, file.c_str());

	wstring tempFolder = folder;

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = name;
	ofn.lpstrFileTitle = (LPWSTR)L"�����ϱ�";
	ofn.nMaxFile = 255;
	ofn.lpstrInitialDir = tempFolder.c_str();
	ofn.Flags = OFN_NOCHANGEDIR;

	// ���ڷ� ���� ��θ� �����ϴµ� �����ϸ�
	// �ݹ����� ������ ���� �̸��� ��ȯ�մϴ�.
	if (GetSaveFileName(&ofn) == TRUE)
	{
		if (func != NULL)
		{
			wstring saveName = name;
			CString::Replace(&saveName, L"\\", L"/");

			func(saveName);
		}
	}

}

void Path::GetFiles(vector<string>* files, string path, string filter, bool bFindSubFolder)
{
	vector<wstring> wFiles;
	wstring wPath = CString::ToWstring(path);
	wstring wFilter = CString::ToWstring(filter);

	GetFiles(&wFiles, wPath, wFilter, bFindSubFolder);

	for (wstring str : wFiles)
		files->push_back(CString::ToString(str));
}

//path : ../Temp/
//filter : *.txt
void Path::GetFiles(vector<wstring>* files, wstring path, wstring filter, bool bFindSubFolder)
{

	wstring file = path + filter;

	WIN32_FIND_DATA findData;
	// ���ڷ� ���� ����� ���� ù��° ������ �޽��ϴ�.
	HANDLE handle = FindFirstFile(file.c_str(), &findData);
	// ���ǹ��� ���� �޾��� ��� 
	if (handle != INVALID_HANDLE_VALUE)
	{
		do
		{
			// ���� ���� directory�� ���
			// �ش� ������ ���� GetFile�� ���ݴϴ�.
			// GetFiles���� ���ڷ� ���� vector�� push_back���ֱ� ������
			// �Ʒ��� ���(������ ���)�� �����ϰ� ó���˴ϴ�.
			if (findData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
			{
				if (bFindSubFolder == true && findData.cFileName[0] != '.')
				{
					wstring folder = path + wstring(findData.cFileName) + L"/";
					GetFiles(files, folder, filter, bFindSubFolder);

				}
			}
			else //�ش� ��ο� �Ӽ��� ������ �ƴҶ�. �� �����϶�
			{
				wstring fileName = path + wstring(findData.cFileName);
				files->push_back(fileName);
			}
			//���� ���ϵ� ���������� �����մϴ�.
		} while (FindNextFile(handle, &findData));

		FindClose(handle);
	}
}

void Path::CreateFolder(string path)
{
	CreateFolder(CString::ToWstring(path));
}

void Path::CreateFolder(wstring path)
{
	// ���ڷ� ���� ��ΰ� �������� ���� ��� Directory�� ����ϴ�.
	if (ExistDirectory(path) == false)
		CreateDirectory(path.c_str(), NULL);
}

void Path::CreateFolders(string path)
{
	CreateFolders(CString::ToWstring(path));
}

void Path::CreateFolders(wstring path)
{
	CString::Replace(&path, L"\\", L"/");

	vector<wstring> folders;
	CString::SplitString(&folders, path, L"/");

	wstring temp = L"";
	for (wstring folder : folders)
	{
		temp += folder + L"/";

		CreateFolder(temp);
	}
}
