#pragma once

class SpriteLoader
{
public :
	static IDirect3DTexture9* GetSprite(const std::wstring key, int index);
	static bool InsertTexture(std::wstring filePath, std::wstring key, int index);

	static void ReleaseAll();


public :
	static std::unordered_map<std::wstring, std::vector<IDirect3DTexture9*>> m_sprites;
};

