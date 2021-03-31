#include "ServiceLocator.h"

using namespace HyEngine;

// file logger
std::shared_ptr<Logger<FileLogPolicy> > ServiceLocator::fileLogger = NULL;
void ServiceLocator::provideFileLoggingService(const std::shared_ptr<Logger<FileLogPolicy> > providedFileLogger)
{
	fileLogger = providedFileLogger;
}
