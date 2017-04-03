#ifndef __API_H__
#	define __API_H__

#	if defined _WIN32 || defined __CYGWIN__
#		ifdef __GNUC__
#			define DLL_PUBLIC __attribute__ ((dllexport))
#		else
#			define DLL_PUBLIC __declspec(dllexport)
#		endif
#	else
#		define DLL_PUBLIC 
#	endif

#	if defined _WIN32 || defined __CYGWIN__
#		ifdef __GNUC__
#			define DLL_PUBLIC_I __attribute__ ((dllimport))
#		else
#			define DLL_PUBLIC_I __declspec(dllimport)
#		endif
#	else
#		define DLL_PUBLIC_I 
#	endif

#	ifdef __cplusplus
#		define EXTERN_C	extern "C"
#	else
#		define EXTERN_C
#	endif
#endif