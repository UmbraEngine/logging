#pragma once

#ifdef UMBRA_PLATFORM_MACOS
#define UMBRA_API __attribute__((visibility("default")))
#elif UMBRA_PLATFORM_WINDOWS
#define UMBRA_API __declspec(dllexport)
#else
#define UMBRA_API
#endif

#define BIT(x) (1 << x)

// Core Log Macros
#define LOG_CORE_TRACE(...)                                                    \
  Umbra::Logging::Log::getCoreLogger()->trace(__VA_ARGS__)
#define LOG_CORE_DEBUG(...)                                                    \
  Umbra::Logging::Log::getCoreLogger()->debug(__VA_ARGS__)
#define LOG_CORE_INFO(...)                                                     \
  Umbra::Logging::Log::getCoreLogger()->info(__VA_ARGS__)
#define LOG_CORE_WARNING(...)                                                  \
  Umbra::Logging::Log::getCoreLogger()->warning(__VA_ARGS__)
#define LOG_CORE_ERROR(...)                                                    \
  Umbra::Logging::Log::getCoreLogger()->error(__VA_ARGS__)
#define LOG_CORE_FATAL(...)                                                    \
  Umbra::Logging::Log::getCoreLogger()->fatal(__VA_ARGS__)
