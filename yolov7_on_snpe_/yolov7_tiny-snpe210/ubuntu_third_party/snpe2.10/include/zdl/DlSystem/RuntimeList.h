//=============================================================================
//
//  Copyright (c) 2022 Qualcomm Technologies, Inc.
//  All Rights Reserved.
//  Confidential and Proprietary - Qualcomm Technologies, Inc.
//
//=============================================================================

#ifndef DL_SYSTEM_RUNTIME_LIST_H
#define DL_SYSTEM_RUNTIME_LIST_H

#include <stddef.h>

#include "DlSystem/DlEnums.h"
#include "DlSystem/DlError.h"


#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup c_apis C
@{ */

/** @name RuntimeList
 *  Description of RuntimeList.
 * @{ */

/**
   * A typedef to indicate a SNPE RuntimeList handle
 */
typedef void* Snpe_RuntimeList_Handle_t;

/**
 * @brief .
 *
 * Creates a new runtime list
 *
 */
SNPE_API
Snpe_RuntimeList_Handle_t Snpe_RuntimeList_Create();

/**
 * @brief Destroys the RuntimeList
 *
 * @param[in] runtimeListHandle : Handle needed to access the runtimeList
 *
 * @return Error code. Returns SNPE_SUCCESS if destruction successful
 */
SNPE_API
Snpe_ErrorCode_t Snpe_RuntimeList_Delete(Snpe_RuntimeList_Handle_t runtimeListHandle);

/**
 * @brief Returns the Runtime from list at position index
 *
 * @param[in] runtimeListHandle: Handle needed to access the runtimeList
 *
 * @param[in] index : position in runtimeList
 *
 * @return Error code. Returns SNPE_SUCCESS if destruction successful
 */
SNPE_API
Snpe_Runtime_t Snpe_RuntimeList_GetRuntime(Snpe_RuntimeList_Handle_t runtimeListHandle, int index) ;

/**
 * @brief Adds runtime to the end of the runtime list
 *        order of precedence is former followed by latter entry
 *
 * @param[in] runtimeListHandle: Handle needed to access the runtimeList
 *
 * @param[in] runtime to add
 *
 * @return Error code. Ruturns SNPE_SUCCESS If the runtime added successfully
 */
SNPE_API
Snpe_ErrorCode_t Snpe_RuntimeList_Add(Snpe_RuntimeList_Handle_t runtimeListHandle, Snpe_Runtime_t runtime);

/**
 * @brief Removes the runtime from the list
 *
 * @param[in] runtimeListHandle: Handle needed to access the runtimeList
 *
 * @param[in] runtime to be removed
 *
 * @return Error code. Ruturns SNPE_SUCCESS If the runtime added successfully
 */
SNPE_API
Snpe_ErrorCode_t Snpe_RuntimeList_Remove(Snpe_RuntimeList_Handle_t runtimeListHandle, Snpe_Runtime_t runtime) ;

/**
 * @brief Returns the number of runtimes in the list
 *
 * @param[in] runtimeListHandle: Handle needed to access the runtimeList
 *
 * @return number of entries in the runtimeList.
 */
SNPE_API
size_t Snpe_RuntimeList_Size(Snpe_RuntimeList_Handle_t runtimeListHandle) ;

/**
 * @brief Returns 1 if the list is empty
 *
 * @param[in] runtimeListHandle: Handle needed to access the runtimeList
 *
 * @return 1 if list empty, 0 otherwise.
 */
SNPE_API
int Snpe_RuntimeList_Empty(Snpe_RuntimeList_Handle_t runtimeListHandle) ;

/**
 * @brief .
 *
 * Removes all runtime from the list
 *
 * @param[in] runtimeListHandle: Handle needed to access the runtimeList
 *
 * @return Error code. Returns SNPE_SUCCESS if runtime list is cleared successfully.
 */
SNPE_API
Snpe_ErrorCode_t Snpe_RuntimeList_Clear(Snpe_RuntimeList_Handle_t runtimeListHandle);

/**
 * @brief .
 *
 * @param[in] runtime const char*
 * Returns a Runtime enum corresponding to the in param string
 *
 */
SNPE_API
Snpe_Runtime_t Snpe_RuntimeList_StringToRuntime(const char* str);

/**
 * @brief .
 *
 * @param[in] runtime
 * Returns a const char* corresponding to the in param runtime enum
 *
 */
SNPE_API
const char* Snpe_RuntimeList_RuntimeToString(Snpe_Runtime_t runtime);

/** @} */
/** @} */ /* end_addtogroup c_apis C */

#ifdef __cplusplus
}  // extern "C"
#endif

#endif // DL_SYSTEM_RUNTIME_LIST_H
