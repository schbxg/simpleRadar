//
// MATLAB Compiler: 6.1 (R2015b)
// Date: Sun Mar 22 22:12:10 2020
// Arguments: "-B" "macro_default" "-W" "cpplib:libfunc_VerticalLookingMode"
// "-T" "link:lib" "func_VerticalLookingMode.m" 
//

#ifndef __libfunc_VerticalLookingMode_h
#define __libfunc_VerticalLookingMode_h 1

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

#ifdef EXPORTING_libfunc_VerticalLookingMode
#define PUBLIC_libfunc_VerticalLookingMode_C_API __global
#else
#define PUBLIC_libfunc_VerticalLookingMode_C_API /* No import statement needed. */
#endif

#define LIB_libfunc_VerticalLookingMode_C_API PUBLIC_libfunc_VerticalLookingMode_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_libfunc_VerticalLookingMode
#define PUBLIC_libfunc_VerticalLookingMode_C_API __declspec(dllexport)
#else
#define PUBLIC_libfunc_VerticalLookingMode_C_API __declspec(dllimport)
#endif

#define LIB_libfunc_VerticalLookingMode_C_API PUBLIC_libfunc_VerticalLookingMode_C_API


#else

#define LIB_libfunc_VerticalLookingMode_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_libfunc_VerticalLookingMode_C_API 
#define LIB_libfunc_VerticalLookingMode_C_API /* No special import/export declaration */
#endif

extern LIB_libfunc_VerticalLookingMode_C_API 
bool MW_CALL_CONV libfunc_VerticalLookingModeInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_libfunc_VerticalLookingMode_C_API 
bool MW_CALL_CONV libfunc_VerticalLookingModeInitialize(void);

extern LIB_libfunc_VerticalLookingMode_C_API 
void MW_CALL_CONV libfunc_VerticalLookingModeTerminate(void);



extern LIB_libfunc_VerticalLookingMode_C_API 
void MW_CALL_CONV libfunc_VerticalLookingModePrintStackTrace(void);

extern LIB_libfunc_VerticalLookingMode_C_API 
bool MW_CALL_CONV mlxFunc_VerticalLookingMode(int nlhs, mxArray *plhs[], int nrhs, 
                                              mxArray *prhs[]);


#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__BORLANDC__)

#ifdef EXPORTING_libfunc_VerticalLookingMode
#define PUBLIC_libfunc_VerticalLookingMode_CPP_API __declspec(dllexport)
#else
#define PUBLIC_libfunc_VerticalLookingMode_CPP_API __declspec(dllimport)
#endif

#define LIB_libfunc_VerticalLookingMode_CPP_API PUBLIC_libfunc_VerticalLookingMode_CPP_API

#else

#if !defined(LIB_libfunc_VerticalLookingMode_CPP_API)
#if defined(LIB_libfunc_VerticalLookingMode_C_API)
#define LIB_libfunc_VerticalLookingMode_CPP_API LIB_libfunc_VerticalLookingMode_C_API
#else
#define LIB_libfunc_VerticalLookingMode_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_libfunc_VerticalLookingMode_CPP_API void MW_CALL_CONV func_VerticalLookingMode(int nargout, mwArray& DenProf_X, mwArray& DenProf_X_N, mwArray& DenProf_Y, mwArray& DenProf_Y_N, mwArray& Orien_X, mwArray& Orien_X_N, mwArray& Orien_Y, mwArray& Orien_Y_N, mwArray& WingBeatFre_X, mwArray& WingBeatFre_X_N, mwArray& WingBeatFre_Y, mwArray& WingBeatFre_Y_N, mwArray& BodyLen_X, mwArray& BodyLen_X_N, mwArray& BodyLen_Y, mwArray& BodyLen_Y_N, mwArray& BodyMass_X, mwArray& BodyMass_X_N, mwArray& BodyMass_Y, mwArray& BodyMass_Y_N, mwArray& WBF_Ind_X, mwArray& WBF_Ind_X_N, mwArray& WBF_Ind_Y, mwArray& WBF_Ind_Y_N, mwArray& HTDiv_X, mwArray& HTDiv_T_N, mwArray& HTDiv_Y, mwArray& HTDiv_H_N, mwArray& PP_X, mwArray& PP_X_N, mwArray& PP_Y, mwArray& PP_Y_N, const mwArray& TrackFile_name, const mwArray& CaliFilePath, const mwArray& StartRan, const mwArray& SampleNum, const mwArray& PRT, const mwArray& PulseWid, const mwArray& WaveForm, const mwArray& CodeType, const mwArray& RCS_ball, const mwArray& MinLength_Den, const mwArray& MinLength_ParaEst, const mwArray& SampleTime, const mwArray& IntCali_Enable);

#endif
#endif
