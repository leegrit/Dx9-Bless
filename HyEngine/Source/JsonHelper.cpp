#include "StandardEngineFramework.h"
#include "JsonHelper.h"
#include <fstream>

void Json::GetValue(Json::Value & parent, string name, bool & vec)
{
	vec = parent[name.c_str()].asBool();
}

void Json::SetValue(Json::Value & parent, string name, bool & vec)
{
	parent[name.c_str()] = vec;
}

void Json::GetValue(Json::Value & parent, string name, float & vec)
{
	Json::Value json = parent[name.c_str()];
	if (json == NULL)
		vec = 0;
	else
		vec = json.asFloat();
}

void Json::SetValue(Json::Value & parent, string name, float & vec)
{
	parent[name.c_str()] = vec;
}

void Json::GetValue(Json::Value & parent, string name, int & vec)
{
	Json::Value json = parent[name.c_str()];
	if (json == NULL)
		vec = 0;
	else
		vec = json.asInt();
	vec = parent[name.c_str()].asInt();
}

void Json::SetValue(Json::Value & parent, string name, int & vec)
{
	parent[name.c_str()] = vec;
}

void Json::GetValue(Json::Value & parent, string name, D3DXVECTOR2 & vec)
{
	for (int i = 0; i < 2; i++)
		vec[i] = parent[name.c_str()][i].asFloat();
}

void Json::SetValue(Json::Value & parent, string name, D3DXVECTOR2 & vec)
{
	for (int i = 0; i < 2; i++)
		parent[name.c_str()].append(vec[i]);
}

void Json::GetValue(Json::Value & parent, string name, D3DXVECTOR3 & vec)
{
	for (int i = 0; i < 3; i++)
		vec[i] = parent[name.c_str()][i].asFloat();
}

void Json::SetValue(Json::Value & parent, string name, D3DXVECTOR3 & vec)
{
	for (int i = 0; i < 3; i++)
		parent[name.c_str()].append(vec[i]);
}

void Json::GetValue(Json::Value & parent, string name, Vector3 & vec)
{
	Json::Value valueJson = parent[name];
	// TEST
	vec.x() = valueJson[JsonKey::X].asFloat();
	vec.y() = valueJson[JsonKey::Y].asFloat();
	vec.z() = valueJson[JsonKey::Z].asFloat();
}

void Json::SetValue(Json::Value & parent, string name, Vector3 & vec)
{
	assert(false);
}


void Json::GetValue(Json::Value & parent, string name, string & value)
{
	value = parent.get(name.c_str(), "").asString();

	/*value = "";

	for (size_t i = 0; i < parent[name.c_str()].size(); i++)
	value.append(parent[name.c_str()][i].asString());*/
}

void Json::SetValue(Json::Value & parent, string name, string & value)
{
	parent[name.c_str()].append(value);
}

void Json::GetValue(Json::Value & parent, string name, char * value, int length)
{
	std::string valueStr = parent[name].asString();
	strcpy_s(value, length, valueStr.c_str());
}

void Json::ReadData(wstring file, Json::Value * root)
{
// 	Json::Value root2;
// 	std::ifstream stream2(file, std::ifstream::binary);
// 
// 	Json::Reader reader;
// 	string str;
// 	char p;
// 	while (stream2 >> p)
// 		str += p;
// 
// 	bool ret = reader.parse(str, *root);
// 
// 	//int t = root2["Type"].asInt();



	ifstream stream;
	stream.open(file);
	{
		//Json::Reader reader;
		//reader.parse(stream, *root);
		Json::CharReaderBuilder builder;
		Json::parseFromStream(builder, stream, root, nullptr);
	}
	stream.close();
}

void Json::WriteData(wstring file, Json::Value * root)
{
	ofstream stream;

	string temp = CString::ToString(file);
	stream.open(temp);
	{
		Json::StreamWriterBuilder builder;
		builder.newStreamWriter()->write(*root, &stream);
		/*Json::StyledWriter writer;

		stream << writer.write(*root);*/
	}
	stream.close();
}