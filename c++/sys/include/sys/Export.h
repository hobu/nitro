
#ifndef SYS_EXPORT_H
#define SYS_EXPORT_H

# if defined(WIN32)
#ifndef IMPORT_NITRO_API
#   define DLL_PUBLIC_FUNCTION extern "C" __declspec (dllexport)
#   define DLL_PUBLIC_CLASS __declspec (dllexport)
#else
#   define DLL_PUBLIC_FUNCTION extern "C" __declspec (dllimport)
#   define DLL_PUBLIC_CLASS __declspec (dllimport)

#endif

# else

#   define DLL_FLAGSET RTLD_LAZY
#   define DLL_PUBLIC_FUNCTION extern "C"
#   define DLL_PUBLIC_CLASS 

# endif


#endif