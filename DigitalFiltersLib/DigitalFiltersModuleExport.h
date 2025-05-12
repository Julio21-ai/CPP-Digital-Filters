// DigitalFiltersModuleExport.h
#pragma once

#if defined(DIGITALFILTERS_STATIC_LIB)
#define DIGITALFILTERS_MODULE_LIB
#elif defined(DIGITALFILTERS_EXPORTS)
#define DIGITALFILTERS_MODULE_LIB __declspec(dllexport)
#else
#define DIGITALFILTERS_MODULE_LIB __declspec(dllimport)
#endif