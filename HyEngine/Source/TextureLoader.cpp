#include "StandardEngineFramework.h"
#include "TextureLoader.h"

using namespace HyEngine;

IDirect3DBaseTexture9* TextureLoader::GetTexture(std::wstring filePath)
{
	auto& iter = textureMap.find(filePath);
	if (textureMap.end()== iter)
	{
		IDirect3DTexture9 * texture;
		HRESULT hr = D3DXCreateTextureFromFile
		(
			DEVICE,
			filePath.c_str(),
			&texture
		);
		if (SUCCEEDED(hr) == false)
			return nullptr;
		textureMap.insert(std::make_pair(filePath, texture));
	}
	return textureMap[filePath];
}
IDirect3DBaseTexture9* HyEngine::TextureLoader::GetCubeTexture(std::wstring filePath)
{
	auto& iter = textureMap.find(filePath);
	if (textureMap.end() == iter)
	{
		IDirect3DCubeTexture9 * texture;
		HRESULT hr=  D3DXCreateCubeTextureFromFile
		(
			DEVICE,
			filePath.c_str(),
			&texture
		);
		if (SUCCEEDED(hr) == false)
			return nullptr;
		textureMap.insert(std::make_pair(filePath, texture));
	}
	return textureMap[filePath];
}
IDirect3DBaseTexture9* TextureLoader::GetTexture(LPCWSTR filePath)
{
	auto& iter = textureMap.find(filePath);
	if (textureMap.end() == iter)
	{
		IDirect3DTexture9 * texture;
		HRESULT hr = D3DXCreateTextureFromFile
		(
			DEVICE,
			filePath,
			&texture
		);
		if (SUCCEEDED(hr) == false)
			return nullptr;
		textureMap.insert(std::make_pair(filePath, texture));
	}
	return textureMap[filePath];
}
std::unordered_map<std::wstring, IDirect3DBaseTexture9*> TextureLoader::textureMap;