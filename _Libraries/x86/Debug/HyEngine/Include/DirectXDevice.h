#pragma once


class ENGINE_DLL DirectXDevice
{
	DECLARE_SINGLETON(DirectXDevice)

private :
	DirectXDevice();
	~DirectXDevice();

public :
	// -------------------------------------------
	// PUBLIC METHODS
	// -------------------------------------------------
	inline const LPDIRECT3DDEVICE9 GetDevice() const { return m_pDevice; }

	HRESULT Init(HWND hwnd);
	void Shutdown();

	void RenderBegin();
	void RenderEnd();

	HWND GetHWnd();

	void DrawNumber(float drawNumber, float xPos, float yPos, D3DCOLOR textColor = D3DCOLOR_ARGB(255, 0, 255, 0))
	{
		TCHAR szBuff[128];

		D3DXMATRIX matTrans,matscale;
		D3DXMatrixScaling(&matscale, 1000, 1000, 1000);
		wsprintf(szBuff, L"%d", drawNumber);
		D3DXMatrixTranslation(&matTrans, xPos, yPos, 0.f);
		matscale *= matTrans;
		m_pSprite->SetTransform(&matscale);
		m_pFont->DrawTextW(m_pSprite,
			szBuff, lstrlen(szBuff), nullptr, 0, textColor);
	}
	void DrawTextFormat(float x, float y, D3DCOLOR color, TCHAR* pszBuff, int args, ...)
	{
		TCHAR szBuff[128];

		D3DXMATRIX matTrans;
		wsprintf(szBuff, pszBuff, args);
		D3DXMatrixTranslation(&matTrans, x, y, 0.f);
		m_pSprite->SetTransform(&matTrans);
		m_pFont->DrawTextW(m_pSprite, szBuff,
			lstrlen(szBuff), nullptr, 0, color);
	}
	void DrawText(TCHAR* pszBuff, float x, float y, D3DCOLOR color)
	{
		TCHAR szBuff[128];

		D3DXMATRIX matTrans;
		wsprintf(szBuff, pszBuff);

		D3DXMatrixTranslation(&matTrans, x, y, 0.f);

		m_pSprite->SetTransform(&matTrans);
		m_pFont->DrawText(m_pSprite, szBuff,
			lstrlen(szBuff), nullptr, 0, color);
	}


	void TextNum(int num, float x, float y)
	{
		TCHAR szBuff[128];

		D3DXMATRIX matTrans;
		wsprintf(szBuff, L"%d", num);
		//wsprintf(szBuff, L"hi : %d", 5);
		D3DXMatrixTranslation(&matTrans, x, y, 0.f);
		m_pSprite->SetTransform(&matTrans);
		m_pFont->DrawText(m_pSprite,
			szBuff, lstrlen(szBuff), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
	}


	inline LPD3DXSPRITE GetSprite() { return m_pSprite; }
	inline LPD3DXFONT GetFont() { return m_pFont; }
private :
	// -------------------------------------------------
	// PROPERTIES
	// ----------------------------------------------
	LPDIRECT3D9 m_pSDK;
	LPDIRECT3DDEVICE9 m_pDevice;
	HWND m_hWnd;

	LPD3DXSPRITE m_pSprite;
	LPD3DXFONT m_pFont;
};

#define DEVICE DirectXDevice::Get()->GetDevice()
//#define RENDER_BEGIN DirectXDevice::Get()->RenderBegin();
//#define RENDER_END DirectXDevice::Get()->RenderEnd();
#define DIRECT_SPRITE DirectXDevice::Get()->GetSprite()
#define DIRECT_FONT DirectXDevice::Get()->GetFont()

