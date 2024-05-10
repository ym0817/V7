//==============================================================================
//
//  Copyright (c) 2022 Qualcomm Technologies, Inc.
//  All Rights Reserved.
//  Confidential and Proprietary - Qualcomm Technologies, Inc.
//
//==============================================================================


#ifndef _DL_VERSION_H_
#define _DL_VERSION_H_

#include "DlSystem/SnpeApiExportDefine.h"
#include "DlSystem/DlError.h"
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup c_apis C
@{ */

/** @name DlVersion
 *  Description of DlVersion.
 * @{ */

/**
 * A class that contains the different portions of a version number.
 * A typedef to indicate a SNPE DlVersion handle
 */
typedef void* Snpe_DlVersion_Handle_t;

/**
 * Destroys/frees DlVersion
 *
 * @param[in] handle : Handle to access DlVersion
 *
 * @return SNPE_SUCCESS if Delete operation successful.
*/
SNPE_API
Snpe_ErrorCode_t Snpe_DlVersion_Delete(Snpe_DlVersion_Handle_t handle);

/**
 * Get the major version number.
 * @param[in] handle : Handle to access DlVersion
 * @return Major version
 */
SNPE_API
int32_t Snpe_DlVersion_GetMajor(Snpe_DlVersion_Handle_t handle);

/**
 * Get the minor version number.
 * @param[in] handle : Handle to access DlVersion
 * @return Minor version
 */
SNPE_API
int32_t Snpe_DlVersion_GetMinor(Snpe_DlVersion_Handle_t handle);

/**
 * Get the teeny version number.
 * @param[in] handle : Handle to access DlVersion
 * @return Teeny version
 */
SNPE_API
int32_t Snpe_DlVersion_GetTeeny(Snpe_DlVersion_Handle_t handle);

/**
 * Get the string holding information about the build version.
 *
 * @param[in] handle : Handle to access DlVersion
 * @return Build information
 */
SNPE_API
const char* Snpe_DlVersion_GetBuild(Snpe_DlVersion_Handle_t handle);

/**
 * @brief Returns a string in the form Major.Minor.Teeny.Build
 *
 * @param[in] handle : Handle to access DlVersion
 * @return A formatted char* holding the version information.
 *
 * @note the returned string will be invalidated by subsequent calls to this function
 */
SNPE_API
const char* Snpe_DlVersion_ToString(Snpe_DlVersion_Handle_t handle);


/** @} */
/** @} */ /* end_addtogroup c_apis C */


#ifdef __cplusplus
}  // extern "C"
#endif

#endif // _DL_VERSION_H_
