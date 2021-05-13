#include "stdafx.h"
#include "SpriteLoader.h"

IDirect3DTexture9 * SpriteLoader::GetSprite(const std::wstring key, int index)
{
	auto iter_find = m_sprites.find(key);
	if (m_sprites.end() == iter_find)
		return nullptr;
	return iter_find->second[index];
}

bool SpriteLoader::InsertTexture(std::wstring filePath, std::wstring key, int index)
{
	auto iter_find = m_sprites.find(key);
	if (iter_find != m_sprites.end())
		return false;

	TCHAR buf[MAX_PATH] = L"";
	IDirect3DTexture9* pTexture = nullptr;
	//for(UINT i = 0; i < index)

	for (UINT i = 0; i < index; i++)
	{
		swprintf_s(buf, filePath.c_str(), i);
		D3DXCreateTextureFromFile
		(
			DEVICE,
			buf,
			&pTexture
		);
		m_sprites[key].emplace_back(pTexture);
	}
	return true;
}

void SpriteLoader::ReleaseAll()
{
	for (auto pair : m_sprites)
	{
		for (auto sprite : pair.second)
		{
			SAFE_RELEASE(sprite);
		}
		pair.second.clear();
	}
}

std::unordered_map<std::wstring, std::vector<IDirect3DTexture9*>> SpriteLoader::m_sprites;