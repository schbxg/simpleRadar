//
// MATLAB Compiler: 6.1 (R2015b)
// Date: Thu May 28 17:26:03 2020
// Arguments: "-B" "macro_default" "-W"
// "cpplib:libfunc_Main_VerticalLookingMode" "-T" "link:lib"
// "func_Main_VerticalLookingMode.m" 
//

#ifndef __libfunc_Main_VerticalLookingMode_h
#define __libfunc_Main_VerticalLookingMode_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#include "mclcppclass.h"
#ifdef __cplusplus
extern "C" {
#endif

#if defined(__SUNPRO_CC)
/* Solaris shared libraries use __global, rather than mapfiles
 * to define the API exported from a shared library. __global is
 * only necessary when building the library -- files including
 * this header file to use the library do not need the __global
 * declaration; hence the EXPORTING_<library> logic.
 */

#ifdef EXPORTING_libfunc_Main_VerticalLookingMode
#define PUBLIC_libfunc_Main_VerticalLookingMode_C_API __global
#else
#define PUBLIC_libfunc_Main_VerticalLookingMode_C_API /* No import statement needed. */
#endif

#define LIB_libfunc_Main_VerticalLookingMode_C_API PUBLIC_libfunc_Main_VerticalLookingMode_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_libfunc_Main_VerticalLookingMode
#define PUBLIC_libfunc_Main_VerticalLookingMode_C_API __declspec(dllexport)
#else
#define PUBLIC_libfunc_Main_VerticalLookingMode_C_API __declspec(dllimport)
#endif

#define LIB_libfunc_Main_VerticalLookingMode_C_API PUBLIC_libfunc_Main_VerticalLookingMode_C_API


#else

#define LIB_libfunc_Main_VerticalLookingMode_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_libfunc_Main_VerticalLookingMode_C_API 
#define LIB_libfunc_Main_VerticalLookingMode_C_API /* No special import/export declaration */
#endif

extern LIB_libfunc_Main_VerticalLookingMode_C_API 
bool MW_CALL_CONV libfunc_Main_VerticalLookingModeInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_libfunc_Main_VerticalLookingMode_C_API 
bool MW_CALL_CONV libfunc_Main_VerticalLookingModeInitialize(void);

extern LIB_libfunc_Main_VerticalLookingMode_C_API 
void MW_CALL_CONV libfunc_Main_VerticalLookingModeTerminate(void);



extern LIB_libfunc_Main_VerticalLookingMode_C_API 
void MW_CALL_CONV libfunc_Main_VerticalLookingModePrintStackTrace(void);

extern LIB_libfunc_Main_VerticalLookingMode_C_API 
bool MW_CALL_CONV mlxFunc_Main_VerticalLookingMode(int nlhs, mxArray *plhs[], int nrhs, 
                                                   mxArray *prhs[]);


#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__BORLANDC__)

#ifdef EXPORTING_libfunc_Main_VerticalLookingMode
#define PUBLIC_libfunc_Main_VerticalLookingMode_CPP_API __declspec(dllexport)
#else
#define PUBLIC_libfunc_Main_VerticalLookingMode_CPP_API __declspec(dllimport)
#endif

#define LIB_libfunc_Main_VerticalLookingMode_CPP_API PUBLIC_libfunc_Main_VerticalLookingMode_CPP_API

#else

#if !defined(LIB_libfunc_Main_VerticalLookingMode_CPP_API)
#if defined(LIB_libfunc_Main_VerticalLookingMode_C_API)
#define LIB_libfunc_Main_VerticalLookingMode_CPP_API LIB_libfunc_Main_VerticalLookingMode_C_API
#else
#define LIB_libfunc_Main_VerticalLookingMode_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_libfunc_Main_VerticalLookingMode_CPP_API void MW_CALL_CONV func_Main_VerticalLookingMode(int nargout, mwArray& flag, const mwArray& TrackFile_name, const mwArray& CaliFilePath, const mwArray& RCS_ball, const mwArray& MinLength_Den, const mwArray& MinLength_ParaEst, const mwArray& SampleTime, const mwArray& IntCali_Enable, const mwArray& OutputPathName);

#endif
#endif
