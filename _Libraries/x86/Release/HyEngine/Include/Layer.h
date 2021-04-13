#pragma once

namespace HyEngine
{

	class ENGINE_DLL Layer
	{
	public:
		// 추가할 때 반드시 string 값도 최신화 해줄 것.
		static const unsigned long long Default = 1;
		static const unsigned long long UI = 2;
		static const unsigned long long Player = 4;
		static const unsigned long long Enemy = 8;
		static const unsigned long long Slot1 = 16;
		static const unsigned long long Slot2 = 32;
		static const unsigned long long Slot3 = 64;
		static const unsigned long long Slot4 = 128;
		static const unsigned long long Slot5 = 256;
		static const unsigned long long Slot6 = 512;
		static const unsigned long long Slot7 = 1024;
		static const unsigned long long Slot8 = 2048;
		static const unsigned long long Slot9 = 4096;
		static const unsigned long long Slot10 = 8192;
		static const unsigned long long Slot11 = 16384;
		static const unsigned long long Slot12 = 32768;
		static const unsigned long long Slot13 = 65536;
		static const unsigned long long Slot14 = 131072;
		static const unsigned long long Slot15 = 262144;
		static const unsigned long long Slot16 = 524288;




		static void AddLayer(std::wstring layerName, UINT layer);
		static  UINT GetLayer(std::wstring name);
		static std::wstring LayerToName(UINT layer);
		static UINT NameToLayer(std::wstring name);
		static UINT IndexToLayer(int index);
	private:
		static std::vector< unsigned long long> layersVec;
		static std::unordered_map<std::wstring, UINT> layersMap;

	};



	class ENGINE_DLL LayerMask
	{
	public:
		LayerMask(UINT value)
			: value(value)
		{

		}
		LayerMask(const LayerMask& value)
			: value(value.value)
		{

		}

		static LayerMask GetMask(const std::wstring& name)
		{
			LayerMask layerMask(Layer::NameToLayer(name));
			return layerMask;
		}
		UINT GetValue()
		{
			return value;
		}
	private:
		UINT value;
	};
}