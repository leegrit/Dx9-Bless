#pragma once

#ifdef EXPORTS_ENGINE
#define ENGINE_DLL _declspec(dllexport)
#else
#define ENGINE_DLL _declspec(dllimport)
#endif

#define SAFE_DELETE(p)  \
if(p)					\
{						\
delete p;				\
p = nullptr;			\
}
#define SAFE_RELEASE(p)  \
if(p)					\
{						\
p->Release();				\
p = nullptr;			\
}
#define SAFE_DELETE_ARRAY(p)\
if (p)\
{\
	delete[] p;\
	p = nullptr;\
}

#define WinMaxWidth 1024
#define WinMaxHeight 768
//#define WinMaxWidth 1280
//#define WinMaxHeight 720

#define WinMinWidth 200
#define WinMinHeight 200