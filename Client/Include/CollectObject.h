#pragma once
#include "Mesh.h"
namespace HyEngine
{
	class HierarchyData;
}

using namespace HyEngine;
class CollectObject : public Mesh
{
	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR & DESTRUCTOR 
	//////////////////////////////////////////////////////////////////////////
protected:
	explicit CollectObject(Scene* pScene, std::wstring name);
	virtual ~CollectObject();

	//////////////////////////////////////////////////////////////////////////
	// INHERITED
	//////////////////////////////////////////////////////////////////////////
public :
	virtual void Initialize(std::wstring dataPath);
	virtual void Render() override;
	virtual void Update() override;
	void DrawPrimitive(ID3DXEffect* pEffect) override;
	void UpdatedData(EDataType dataType) override;
	bool ComputeBoundingSphere(_Out_ D3DXVECTOR3 * center, _Out_ float * radius);

	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	std::wstring GetMeshPath() const;

	void Collecting();
public : /* For Collect */
	virtual void DoCollect();
	virtual void OnCollected();
	virtual void OnCollectBegin();
	virtual void OnCollectEnd();


	//////////////////////////////////////////////////////////////////////////
	// VARIABLES
	//////////////////////////////////////////////////////////////////////////
private : /* For Render */
	ID3DXMesh * m_pMesh = nullptr;
	std::vector<D3DXMATERIAL> m_mtrls;
	std::vector<IDirect3DTexture9*> m_textures;
	std::vector<IDirect3DTexture9*> m_normals;
	std::vector<IDirect3DTexture9*> m_emissives;
	std::vector<IDirect3DTexture9*> m_speculars;
	std::vector<IDirect3DTexture9*> m_diffuseMasks; // green 사용
	std::vector<std::wstring> m_textureNames;
	std::vector<ID3DXEffect*> m_effects;
	std::wstring m_lastLoadedMeshPath;

private : /* For Interact */
	float m_interactRadius = 30;
	// 수집에 딜레이가 있다.
	bool m_bCollecting = false; 
	bool m_bCollectable = true;
	float m_collectDelay = 3.f;
	float m_elapsed = 0;

	//////////////////////////////////////////////////////////////////////////
	// FACTORY METHOD
	//////////////////////////////////////////////////////////////////////////
public :
	static CollectObject * Create(Scene* pScene, std::wstring name, std::wstring dataPath);
};

