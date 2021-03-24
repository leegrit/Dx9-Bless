#include "StandardEngineFramework.h"
#include "UpdateDispatcher.h"



std::vector<std::function<UpdateDispatcher::UpdateState(void)>> UpdateDispatcher::updates;
std::vector<std::function<void(void)>> UpdateDispatcher::onCompletes;