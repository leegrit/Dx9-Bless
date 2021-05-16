#include "stdafx.h"
#include "Hieracon_Cora.h"
#include "FontTexture.h"
#include "PathManager.h"
#include "GameScene.h"


Hieracon_Cora::Hieracon_Cora(Scene * pScene)
	: NonePlayer(pScene, ESkinningType::SoftwareSkinning)
{
}

Hieracon_Cora::~Hieracon_Cora()
{
}

void Hieracon_Cora::Initialize(std::wstring dataPath)
{
	NonePlayer::Initialize(dataPath);

	SetAnimationSet(3);

	//ㄴm_pNameTexture = FontTexture::Create(GetScene(), L"LeoniName",
	//	PATH->AssetsPathW() + L"FontTexture/LeoniName.png", this, D3DXVECTOR3(0, 16.5f, 0));
	//auto titleTex = FontTexture::Create(GetScene(), L"LeoniName",
	//	PATH->AssetsPathW() + L"FontTexture/LeoniTitle.png", this, D3DXVECTOR3(0, 16.5f, 0));
	///titleTex->SetOffset(D3DXVECTOR3(0, 13.5, 0));
	//titleTex->m_pTransform->SetScale(6, 1, 1);
}

void Hieracon_Cora::Update()
{
	NonePlayer::Update();


	GameScene* pScene = static_cast<GameScene*>(SCENE);

	float sizeX = pScene->GetFloatA();
	float sizeY = pScene->GetFloatB();
	float yOffset = pScene->GetFloatC();
	//m_pNameTexture->m_pTransform->SetScale(3, 1.5, 1);
	//m_pNameTexture->SetOffset(D3DXVECTOR3(0, 15, 0));
}

std::wstring Hieracon_Cora::GetCharacterName()
{
	return L"레오니\n<그림자 순찰대장>";
}

std::wstring Hieracon_Cora::GetSubTitle()
{
	return L"";
}

std::wstring Hieracon_Cora::GetOnlyCharacterName()
{
	return L"레오니";
}

D3DXVECTOR3 Hieracon_Cora::GetZoomInOffset()
{
	return D3DXVECTOR3(0, 7, 10);
}
