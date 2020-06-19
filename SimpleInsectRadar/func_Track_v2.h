//
// MATLAB Compiler: 6.1 (R2015b)
// Date: Thu Jun 04 18:48:06 2020
// Arguments: "-B" "macro_default" "-W" "cpplib:func_Track_v2" "-T" "link:lib"
// "func_Track_v2.m" 
//

#ifndef __func_Track_v2_h
#define __func_Track_v2_h 1

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

#ifdef EXPORTING_func_Track_v2
#define PUBLIC_func_Track_v2_C_API __global
#else
#define PUBLIC_func_Track_v2_C_API /* No import statement needed. */
#endif

#define LIB_func_Track_v2_C_API PUBLIC_func_Track_v2_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_func_Track_v2
#define PUBLIC_func_Track_v2_C_API __declspec(dllexport)
#else
#define PUBLIC_func_Track_v2_C_API __declspec(dllimport)
#endif

#define LIB_func_Track_v2_C_API PUBLIC_func_Track_v2_C_API


#else

#define LIB_func_Track_v2_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_func_Track_v2_C_API 
#define LIB_func_Track_v2_C_API /* No special import/export declaration */
#endif

extern LIB_func_Track_v2_C_API 
bool MW_CALL_CONV func_Track_v2InitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_func_Track_v2_C_API 
bool MW_CALL_CONV func_Track_v2Initialize(void);

extern LIB_func_Track_v2_C_API 
void MW_CALL_CONV func_Track_v2Terminate(void);



extern LIB_func_Track_v2_C_API 
void MW_CALL_CONV func_Track_v2PrintStackTrace(void);

extern LIB_func_Track_v2_C_API 
bool MW_CALL_CONV mlxFunc_Track_v2(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);


#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__BORLANDC__)

#ifdef EXPORTING_func_Track_v2
#define PUBLIC_func_Track_v2_CPP_API __declspec(dllexport)
#else
#define PUBLIC_func_Track_v2_CPP_API __declspec(dllimport)
#endif

#define LIB_func_Track_v2_CPP_API PUBLIC_func_Track_v2_CPP_API

#else

#if !defined(LIB_func_Track_v2_CPP_API)
#if defined(LIB_func_Track_v2_C_API)
#define LIB_func_Track_v2_CPP_API LIB_func_Track_v2_C_API
#else
#define LIB_func_Track_v2_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_func_Track_v2_CPP_API void MW_CALL_CONV func_Track_v2(int nargout, mwArray& RelevantFlag, mwArray& TrackOneMat, mwArray& CellNum, mwArray& EmptyFlag, mwArray& PackSuccessFlag, mwArray& PackName, const mwArray& Track, const mwArray& CellNum_in1, const mwArray& EmptyFlag_in1, const mwArray& file_name_output, const mwArray& PackFlag, const mwArray& TrackCellPath);

#endif
#endif
