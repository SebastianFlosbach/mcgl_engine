#pragma once

#ifdef MCGL_ENGINE_EXPORTS
#define MCGL_ENGINE_EXTERN __declspec(dllexport)
#else
#define MCGL_ENGINE_EXTERN __declspec(dllimport)
#endif
