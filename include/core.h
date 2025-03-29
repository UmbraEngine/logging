#pragma once

#ifdef UMBRA_PLATFORM_MACOS
#define UMBRA_API __attribute__((visibility("default")))
#elif UMBRA_PLATFORM_WINDOWS
#define UMBRA_API __declspec(dllexport)
#else
#define UMBRA_API
#endif

#define BIT(x) (1 << x)
