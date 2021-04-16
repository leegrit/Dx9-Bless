#pragma once
#include "ColorData.h"

namespace Json
{
	void GetValue(Json::Value& parent, string name, _Out_  bool& vec);
	void SetValue(Json::Value& parent, string name, _Out_  bool& vec);

	void GetValue(Json::Value& parent, string name, _Out_  float& vec);
	void SetValue(Json::Value& parent, string name, _Out_  float& vec);

	void GetValue(Json::Value& parent, string name, _Out_  int& vec);
	void SetValue(Json::Value& parent, string name, _Out_  int& vec);

	void GetValue(Json::Value& parent, string name, _Out_  D3DXVECTOR2& vec);
	void SetValue(Json::Value& parent, string name, _Out_  D3DXVECTOR2& vec);

	void GetValue(Json::Value& parent, string name, _Out_  D3DXVECTOR3& vec);
	void SetValue(Json::Value& parent, string name, _Out_  D3DXVECTOR3& vec);

	void GetValue(Json::Value& parent, string name, _Out_  Vector3& vec);
	void SetValue(Json::Value& parent, string name, _Out_  Vector3& vec);

	void GetValue(Json::Value& parent, string name, _Out_  VectorData& vec);
	void SetValue(Json::Value& parent, string name, _Out_  VectorData& vec);


	void GetValue(Json::Value& parent, string name, _Out_ D3DXCOLOR& color);
	void SetValue(Json::Value& parent, string name, _Out_ D3DXCOLOR& color);

	void GetValue(Json::Value& parent, string name, _Out_ ColorData& color);
	void SetValue(Json::Value& parent, string name, _Out_ ColorData& color);

	void GetValue(Json::Value& parent, string name, _Out_  string& value);
	void SetValue(Json::Value& parent, string name, _Out_  string& value);

	void GetValue(Json::Value& parent, string name, _Out_ char* value, int length);

	void ReadData(wstring file, Json::Value* root);
	void WriteData(wstring file, Json::Value* root);
}