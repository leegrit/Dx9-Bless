#pragma once

namespace HyEngine
{
		using namespace std;
		class Path
		{
		public:
			// ���ڷ� ���� ��ο� ������ �����ϴ��� Ȯ��
			static bool ExistFile(string path);
			static bool ExistFile(wstring path);

			// ���ڷ� ���� ��ΰ� �����ϴ��� Ȯ��
			static bool ExistDirectory(string path);
			static bool ExistDirectory(wstring path);

			// ���� ��ħ
			static string Combine(string path1, string path2);
			static wstring Combine(wstring path1, wstring path2);

			// vector�� �޾Ƽ� combine��� ����
			static string Combine(vector<string> paths);
			static wstring Combine(vector<wstring> paths);

			// ���ڷ� ���� ����� ������ ���� �̸��� ��ȯ�Ѵ�.
			static string GetDirectoryName(string path);
			static wstring GetDirectoryName(wstring path);

			// ���ڷ� ���� ����� ���� Ȯ���ڸ� ��ȯ�Ѵ�.
			static string GetExtension(string path);
			static wstring GetExtension(wstring path);

			// ���ڷ� ���� ����� �����̸��� ��ȯ�Ѵ�. Ȯ���� ����
			static string GetFileName(string path);
			static wstring GetFileName(wstring path);

			// Ȯ���� ���� ���� �̸� ��ȯ
			static string GetFileNameWithoutExtension(string path);
			static wstring GetFileNameWithoutExtension(wstring path);

			const static WCHAR* ImageFilter;
			const static WCHAR* ShaderFilter;
			const static WCHAR* TextFilter;
			const static WCHAR* TileFilter;
			const static WCHAR* TMapFilter;
			const static WCHAR* TDSDFilter;

			// ������ ����.
			static void OpenFileDialog(wstring file, const WCHAR* filter, wstring folder, function<void(wstring)> func, HWND hwnd = NULL);
			// ������ �����Ѵ�.
			static void SaveFileDialog(wstring file, const WCHAR* filter, wstring folder, function<void(wstring)> func, HWND hwnd = NULL);

			// ���ϴ� ����� ���� ��θ� ��� �޴´�.
			static void GetFiles(vector<string>* files, string path, string filter, bool bFindSubFolder);
			static void GetFiles(vector<wstring>* files, wstring path, wstring filter, bool bFindSubFolder);

			// ������ �����.
			static void CreateFolder(string path);
			static void CreateFolder(wstring path);

			static void CreateFolders(string path);
			static void CreateFolders(wstring path);
		};

}