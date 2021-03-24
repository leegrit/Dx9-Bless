#include "StandardEngineFramework.h"
#include "UIDGen.h"

using namespace HyEngine;

IMPLEMENT_SINGLETON(UIDGen)

UIDGen::UIDGen()
{

}
UIDGen::~UIDGen()
{
}

LONGLONG UIDGen::GetUID()
{
	return nextID++;
}

LONGLONG UIDGen::nextID;