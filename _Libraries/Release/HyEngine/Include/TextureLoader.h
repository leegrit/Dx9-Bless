#pragma once


namespace HyEngine
{
		class ENGINE_DLL TextureLoader
		{
		public:
			static std::shared_ptr<IDirect3DBaseTexture9> GetTexture(std::wstring filePath);
			static std::shared_ptr<IDirect3DBaseTexture9> GetCubeTexture(std::wstring filePath);
			static std::shared_ptr<IDirect3DBaseTexture9> GetTexture(LPCWSTR filePath);


		private:
			static std::unordered_map<std::wstring, std::shared_ptr<IDirect3DBaseTexture9>> textureMap;
		};
}


