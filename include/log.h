#pragma once

#include "core.h"
#include "logger.h"

namespace Umbra {
namespace Logging {
class Log {
public:
  UMBRA_API static void init();
  UMBRA_API inline static std::shared_ptr<Logger> &getCoreLogger() {
    return CoreLogger;
  };
  UMBRA_API inline static std::shared_ptr<Logger> &getClientLogger() {
    return ClientLogger;
  }

private:
  static std::shared_ptr<Logger> CoreLogger;
  static std::shared_ptr<Logger> ClientLogger;
};
} // namespace Logging
} // namespace Umbra

// Client Log Macros
#define LOG_TRACE(...)                                                         \
  Umbra::Logging::Log::getClientLogger()->trace(__VA_ARGS__)
#define LOG_DEBUG(...)                                                         \
  Umbra::Logging::Log::getClientLogger()->debug(__VA_ARGS__)
#define LOG_INFO(...) Umbra::Logging::Log::getClientLogger()->info(__VA_ARGS__)
#define LOG_WARNING(...)                                                       \
  Umbra::Logging::Log::getClientLogger()->warning(__VA_ARGS__)
#define LOG_ERROR(...)                                                         \
  Umbra::Logging::Log::getClientLogger()->error(__VA_ARGS__)
#define LOG_FATAL(...)                                                         \
  Umbra::Logging::Log::getClientLogger()->fatal(__VA_ARGS__)
