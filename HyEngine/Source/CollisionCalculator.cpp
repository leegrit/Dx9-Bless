#include "StandardEngineFramework.h"
#include "CollisionCalculator.h"

using namespace HyEngine;


void CollisionCalculator::Calculate(const std::vector<Collider*>& dynamicColliders, const std::vector<Collider*>& staticColliders)
{
	auto& dynamicContainer = cpplinq::from_iterators(dynamicColliders.begin(), dynamicColliders.end())
		>> cpplinq::where([&](const Collider* col)
	{
		if (col->GetActive() == false)
			return false;
		if (col->m_bWantsDestroy == true)
			return false;
		return true;
	}) >> cpplinq::to_vector();
	auto& staticContainer = cpplinq::from_iterators(staticColliders.begin(), staticColliders.end())
		>> cpplinq::where([&](const Collider* col)
	{
		if (col->GetActive() == false)
			return false;
		if (col->m_bWantsDestroy == true)
			return false;
		return true;
	}) >> cpplinq::to_vector();


	for (auto& col : dynamicContainer)
	{
		auto& dynamicTargets = cpplinq::from_iterators(dynamicContainer.begin(), dynamicContainer.end())
			>> cpplinq::where([&](const Collider* targetCol)
		{
			if (col->GetTargetLayer() & targetCol->GetGameObject()->GetLayer())
				return true;
			else
				return false;
		}) >> cpplinq::to_vector();
		auto& staticTargets = cpplinq::from_iterators(staticContainer.begin(), staticContainer.end())
			>> cpplinq::where([&](const Collider* targetCol)
		{
			if (col->GetTargetLayer() & targetCol->GetGameObject()->GetLayer())
				return true;
			else
				return false;
		}) >> cpplinq::to_vector();

		for (auto& dynamicCol : dynamicTargets)
		{
			if (dynamicCol == col) continue;

			col->Calculate(dynamicCol);
		}
		for (auto& staticCol : staticTargets)
		{
			col->Calculate(staticCol);
		}
	}
}
