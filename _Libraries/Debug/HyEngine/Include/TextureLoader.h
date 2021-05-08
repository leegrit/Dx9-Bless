#pragma once


namespace HyEngine
{
		class ENGINE_DLL TextureLoader
		{
		public:
			static IDirect3DBaseTexture9* GetTexture(std::wstring filePath);
			static IDirect3DBaseTexture9* GetCubeTexture(std::wstring filePath);
			static IDirect3DBaseTexture9* GetTexture(LPCWSTR filePath);


		private:
			static std::unordered_map<std::wstring, IDirect3DBaseTexture9*> textureMap;
		};
}


