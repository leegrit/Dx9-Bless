#include "StandardEngineFramework.h"
#include "VertexTypes.h"

using namespace HyEngine;

const DWORD SimpleVertex::FVF = D3DFVF_XYZ;

const DWORD ColorVertex::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

const DWORD VertexNormal::FVF = D3DFVF_XYZ | D3DFVF_NORMAL;

const DWORD TextureVertex::FVF = D3DFVF_XYZ | D3DFVF_TEX1;

const DWORD ModelVertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

const DWORD TextureCubeVertex::FVF = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0);

const DWORD VTXSCREEN::FVF = D3DFVF_XYZRHW | D3DFVF_TEX1;
//const DWORD BumpModelVertex::DECL = D3DDECLUSAGE_POSITION | D3DDECLUSAGE_TEXCOORD | D3DDECLUSAGE_NORMAL | D3DDECLUSAGE_BINORMAL | D3DDECLUSAGE_TANGENT;