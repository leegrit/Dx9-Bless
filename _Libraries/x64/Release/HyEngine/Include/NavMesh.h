#pragma once
#include "GameObject.h"
namespace HyEngine
{
	class ENGINE_DLL NavMesh : public GameObject
	{
	public:
		// --------------------------------------------------------
		// CONSTRUCTOR & DESTRUCTOR
		// --------------------------------------------------------
		explicit NavMesh(class Scene* scene, GameObject* parent);
		virtual ~NavMesh();

	public:
		virtual void Render() override;
		static NavMesh* Create(Scene* scene, GameObject* parent)
		{
			//assert(false);
			NavMesh* mesh = new NavMesh(scene, parent);
			//assert(false);

			return mesh;
		}

		// for editor
		static NavMesh* Create(Scene* scene, GameObject* parent, int editID)
		{
			//assert(false);
			NavMesh* mesh = new NavMesh(scene, parent);
			mesh->SetEditID(editID);
			//assert(false);

			return mesh;
		}

		static NavMesh* Create(Scene* scene, GameObject * parent, std::wstring dataPath)
		{
			NavMesh* mesh = new NavMesh(scene, parent);
			mesh->Initialize(dataPath);
			return mesh;
		}



	public :
		// ---------------------------------------------------------
		// INHERITED
		// --------------------------------------------------------
		virtual void UpdatedData(EDataType dataType) override;

	public:
		// ------------------------------------------------------
		// GETTERS
		// ------------------------------------------------------
		const std::vector<class NavPrimitive*>& GetNavPrimitives();
		class NavPrimitive* GetNavPrimitive(const int& navPrimIndex);
		class std::vector<class Cell*> GetCells(const int& navPrimIndex);
		class Cell*			GetCell(const int& cellIndex);
		//const int& GetCurCellIndex() const;
		const  ECellOption& GetCellOption(const int& cellIndex);
		const int& GetGroup(const int& cellIndex);


	public:
		// --------------------------------------------------------
		// SETTERS
		// --------------------------------------------------------
		void SetCurrentIndex(const unsigned long cellIndex);
		void SetGroup(const unsigned long& cellIndex, const unsigned int& group);

	public :
	
		//////////////////////////////////////////////////////////////////////////
		// INITIALIZER
		//////////////////////////////////////////////////////////////////////////
	private :
		void Initialize(std::wstring dataPath);

		// ----------------------------------------------------------
		// FOR EDITOR 
		// ----------------------------------------------------------
	public:
		bool TryPickingCell(_Out_ VectorData* pickedPos, const D3DXVECTOR3& pickingPos, const  ECellOption& option, const unsigned int& group = 100);
		void AddCell(const D3DXVECTOR3& position, const ECellOption& option, const unsigned int& group);
		void ClearCell();
		void ClearPickedPoses();
		void ChangeCellOption(const unsigned long& cellIndex, const  ECellOption& option);
		void ChangeCellOption(const unsigned int& group, const  ECellOption& option);
		void CreateCell(CellData* data);
		void RemoveNavPrim(int navPrimIndex);
		void SetCellEditMode(ECellEditMode cellEditMode);


		//////////////////////////////////////////////////////////////////////////
		// PUBLIC METHODS
		//////////////////////////////////////////////////////////////////////////
	public :
		bool IsOnMesh(D3DXVECTOR3 position,  _Out_ float* yPos);
		bool PickOnMesh(D3DXVECTOR3 origin, D3DXVECTOR3 direction, _Out_ D3DXVECTOR3* pickedPos);



	private:
		// ---------------------------------------------------
		// VARIABLES
		// --------------------------------------------------
		std::vector<class NavPrimitive*> m_navPrimitives;
		static unsigned long m_nextCellIndex;
		static unsigned long m_nextNavPrimIndex;

		std::vector<class Cell*> m_pickedCell;
		float m_pickRadius = 50.f;
		ECellEditMode m_cellEditMode = ECellEditMode::Similar;
	};
}

