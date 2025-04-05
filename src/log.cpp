//
// Created by Dean Wilson on 2025/01/20
//

#include "log.h"

// TODO: can these be deleted?
// using std::make_shared;
// using std::shared_ptr;

namespace Umbra {
namespace Logging {

std::shared_ptr<Logger> Log::CoreLogger;
std::shared_ptr<Logger> Log::ClientLogger;

void Log::init(bool enableClientDebugLogging)
{
  CoreLogger = std::make_shared<Logger>("Umbra", true);
  ClientLogger = std::make_shared<Logger>("Client", enableClientDebugLogging);
}

}  // namespace Logging
}  // namespace Umbra
