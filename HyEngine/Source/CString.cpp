#include "StandardEngineFramework.h"
#include "CString.h"

#include <iomanip>
#include <sstream>

using namespace std;
using namespace HyEngine;

void CString::SplitString(vector<string>* result, string origin, string tok)
{
	result->clear();
	int cutAt = 0; //�ڸ� ��ġ
	while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos)
	{
		if (cutAt > 0) //�ڸ��� ��ġ�� 0���� ũ�ٸ�
			result->push_back(origin.substr(0, cutAt));

		origin = origin.substr(cutAt + 1);
	}

	if (origin.length() > 0) //�ڸ��� �������� �մٸ�
		result->push_back(origin.substr(0, cutAt));
}

void CString::SplitString(vector<wstring>* result, wstring origin, wstring tok)
{
	result->clear();

	int cutAt = 0; //�ڸ� ��ġ
	while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos)
	{
		if (cutAt > 0) //�ڸ��� ��ġ�� 0���� ũ�ٸ�
			result->push_back(origin.substr(0, cutAt));

		origin = origin.substr(cutAt + 1);
	}

	if (origin.length() > 0) //�ڸ��� �������� �մٸ�
		result->push_back(origin.substr(0, cutAt));
}

bool CString::StartWith(string str, string comp)
{
	//npos no position �� ���ٴ� �Ҹ�
	wstring::size_type index = str.find(comp);
	if (index != wstring::npos && (int)index == 0)
		return true;

	return false;
}

bool CString::StartWith(wstring str, wstring comp)
{
	wstring::size_type index = str.find(comp);
	if (index != wstring::npos && (int)index == 0)
		return true;

	return false;
}

bool CString::Contain(string str, string comp)
{
	size_t found = str.find(comp);

	return found != wstring::npos;
}

bool CString::Contain(wstring str, wstring comp)
{
	size_t found = str.find(comp);

	return found != wstring::npos;
}

void CString::Replace(string * str, string comp, string rep)
{
	string temp = *str;

	size_t startPos = 0;
	while ((startPos = temp.find(comp, startPos)) != wstring::npos)
	{
		temp.replace(startPos, comp.length(), rep);
		startPos += rep.length();
	}

	*str = temp;

}

void CString::Replace(wstring * str, wstring comp, wstring rep)
{
	wstring temp = *str;

	size_t startPos = 0;
	// ���ڿ��� �ݺ��ؼ� ���鼭 ��� replace�� �����Ѵ�.
	while ((startPos = temp.find(comp, startPos)) != wstring::npos)
	{
		temp.replace(startPos, comp.length(), rep);
		startPos += rep.length();
	}

	*str = temp;
}
//sstream
string CString::ToString(D3DXVECTOR3 vec3, int precision)
{
	string temp;
	stringstream stream1, stream2, stream3;
	// �Ҽ��� �ڸ� �����ؼ� string���� ��ȯ �� ���
	stream1 << fixed << setprecision(precision) << vec3.x;
	stream2 << fixed << setprecision(precision) << vec3.y;
	stream3 << fixed << setprecision(precision) << vec3.z;
	temp = "X : " + stream1.str() + " Y : " + stream2.str()
		+ " Z : " + stream3.str();
	return temp;
}

wstring CString::ToWstring(D3DXVECTOR3 vec3, int precision)
{
	wstring temp;
	wstringstream stream1, stream2, stream3;
	stream1 << fixed << setprecision(precision) << vec3.x;
	stream2 << fixed << setprecision(precision) << vec3.y;
	stream3 << fixed << setprecision(precision) << vec3.z;
	temp = L"X : " + stream1.str() + L" Y : " + stream2.str()
		+ L" Z : " + stream3.str();
	return temp;
}

wstring CString::ToWstring(string str)
{
	wstring temp = L"";
	// string -> wstring
	temp.assign(str.begin(), str.end());
	return temp;
}

string CString::ToString(wstring str)
{
	string temp = "";
	// wstring -> string
	temp.assign(str.begin(), str.end());
	return temp;
}

std::wstring HyEngine::CString::CharToWstring(const char * utf8Bytes)
{
	//setup converter
	using convert_type = std::codecvt_utf8<typename std::wstring::value_type>;
	std::wstring_convert<convert_type, typename std::wstring::value_type> converter;

	//use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
	return converter.from_bytes(utf8Bytes);
}

std::wstring HyEngine::CString::stringToWstring(const char * utf8Bytes, const size_t numBytes)
{
	//setup converter
	using convert_type = std::codecvt_utf8<typename std::wstring::value_type>;
	std::wstring_convert<convert_type, typename std::wstring::value_type> converter;

	//use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
	return converter.from_bytes(utf8Bytes, utf8Bytes + numBytes);
}
