#include "StandardEngineFramework.h"
#include "DirectXDevice.h"
#include "PathManager.h"

IMPLEMENT_SINGLETON(DirectXDevice)

DirectXDevice::DirectXDevice()
{
	
}


DirectXDevice::~DirectXDevice()
{

}

HRESULT DirectXDevice::Init(HWND hwnd, bool bFullScreen)
{
	SEND_LOG("DirectDevice Initialize Start");

	//AddFontResourceEx((PATH->AssetsPathW() + L"Fonts/NanumBarunGothic.ttf").c_str(), FR_PRIVATE, NULL);
	AddFontResourceEx((PATH->AssetsPathW() + L"Fonts/InfinitySansR-Regular.ttf").c_str(), FR_PRIVATE, NULL);
	//AddFontResourceEx(L"../Resources/Fonts/koverwatch.ttf", FR_PRIVATE, NULL);

	m_hWnd = hwnd;
	D3DCAPS9 DeviceCap;
	ZeroMemory(&DeviceCap, sizeof(D3DCAPS9));
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);

	if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCap)))
	{
		return E_FAIL;
	}
	DWORD vp = 0;

	if (DeviceCap.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;
	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;

	// ��Ƽ ���� Ÿ�� �ִ� ����
	DWORD maxRT = DeviceCap.NumSimultaneousRTs;
	// ��Ƽ ���� Ÿ�� �����Ǿ����
	assert(maxRT > 1);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	d3dpp.BackBufferWidth = WinMaxWidth;
	d3dpp.BackBufferHeight = WinMaxHeight;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;

	DWORD qulityLevel = 0;
	m_pSDK->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_A8R8G8B8, true, D3DMULTISAMPLE_NONE, &qulityLevel);
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;// qulityLevel - 1;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = m_hWnd;

	if (bFullScreen)
	{
		d3dpp.Windowed = false;
	}
	else
	{
		d3dpp.Windowed = true;
	}
//#ifdef FULL_SCREEN
//	d3dpp.Windowed = false; 
//#else
//	d3dpp.Windowed = true;
//#endif 
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;//D3DPRESENT_INTERVAL_IMMEDIATE;//D3DPRESENT_INTERVAL_DEFAULT;


	if (FAILED(m_pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,m_hWnd, vp, &d3dpp, &m_pDevice)))
	{
		return E_FAIL;
	}

	HRESULT hr = D3DXCreateSprite(m_pDevice, &m_pSprite);
	


	D3DXFONT_DESC fontInfo;
	ZeroMemory(&fontInfo, sizeof(D3DXFONT_DESC));

	
	fontInfo.Width = 0;
	fontInfo.Height = 20;
	fontInfo.Weight = FW_NORMAL;
	fontInfo.CharSet = HANGEUL_CHARSET;
	lstrcpy(fontInfo.FaceName, L"Infinity Sans Regular");

	hr = D3DXCreateFontIndirect(m_pDevice, &fontInfo, &m_pFont);



	SEND_LOG("DirectDevice Initialize End");
	return S_OK;
}

void DirectXDevice::Shutdown()
{
	SAFE_RELEASE(m_pFont);
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pSDK);
}

void DirectXDevice::RenderBegin()
{
	m_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 255, 0, 0), 1.f, 0);
	m_pDevice->BeginScene();
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

}

void DirectXDevice::RenderEnd()
{
	m_pSprite->End();
	m_pDevice->EndScene();
	m_pDevice->Present(nullptr, nullptr, m_hWnd, nullptr);
}

HWND DirectXDevice::GetHWnd()
{
	return m_hWnd;
}
