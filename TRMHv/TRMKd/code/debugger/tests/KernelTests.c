/**
 * @file KernelTests.c
 * @author Anonymized Author
 * @brief Implementation of kernel-side test functions
 * @details
 *
 * @version 0.1
 * @date 2021-04-06
 *
 * @copyright This project is released under the GNU Public License v3.
 *
 */
#include "pch.h"

/**
 * @brief Configures tags and calls target functions
 *
 * @details This function should not be called simultaneously
 * and only functions with at most 4 parameters should be called
 * the target function should be fast call
 * Note : Target test function should check r14 for Tag1 and r15 for Tag2
 *
 * @param Tag1 the first tag
 * @param Tag2 the second tag
 * @param TargetFunction function that needs to be called
 * @param Param1 parameter to the target function
 * @param Param2 parameter to the target function
 * @param Param3 parameter to the target function
 * @param Param4 parameter to the target function
 *
 * @return UINT64 Target function return result
 */
UINT64
TestKernelConfigureTagsAndCallTargetFunction(UINT64 Tag1,
                                             UINT64 Tag2,
                                             PVOID  TargetFunction,
                                             UINT64 Param1,
                                             UINT64 Param2,
                                             UINT64 Param3,
                                             UINT64 Param4)
{
    UINT64 TargetFuncResult = (UINT64)NULL;

    //
    // Configure tags and target functions (export them to assembly)
    //
    g_KernelTestTargetFunction = TargetFunction;
    g_KernelTestTag1           = (UINT64)Tag1;
    g_KernelTestTag2           = (UINT64)Tag2;
    g_KernelTestR15            = (UINT64)NULL;
    g_KernelTestR14            = (UINT64)NULL;
    g_KernelTestR13            = (UINT64)NULL;
    g_KernelTestR12            = (UINT64)NULL;

    //
    // Call the target function
    //
    TargetFuncResult = AsmTestWrapperWithTestTags(Param1, Param2, Param3, Param4);

    //
    // Null the exports
    //
    g_KernelTestTargetFunction = (PVOID)NULL;
    g_KernelTestTag1           = (UINT64)NULL;
    g_KernelTestTag2           = (UINT64)NULL;
    g_KernelTestR15            = (UINT64)NULL;
    g_KernelTestR14            = (UINT64)NULL;
    g_KernelTestR13            = (UINT64)NULL;
    g_KernelTestR12            = (UINT64)NULL;

    return TargetFuncResult;
}

/**
 * @brief Perform the kernel-side tests
 *
 * @param KernelTestRequest user-mode buffer to fill kernel test information
 * @return VOID
 */
VOID
TestKernelPerformTests(PDEBUGGER_PERFORM_KERNEL_TESTS KernelTestRequest)
{
    UINT64 TempPool = (UINT64)NULL;

    LogInfo("Starting kernel-test process...");

    //
    // Call wrapper for ExAllocatePool2
    //
    TempPool = TestKernelConfigureTagsAndCallTargetFunction(1,                      // Tag1 = r14
                                                            2,                      // Tag2 = r15
                                                            (PVOID)ExAllocatePool2, // Target function
                                                            NonPagedPool,           // PoolType
                                                            PAGE_SIZE,              // NumberOfBytes
                                                            POOLTAG,                // Tag
                                                            (UINT64)NULL);

    if (TempPool != (UINT64)NULL)
    {
        //
        // Free the previous pool
        //
        CrsFreePool((PVOID)TempPool);
    }

    LogInfo("All the kernel events are triggered");

    KernelTestRequest->KernelStatus = DEBUGGER_OPERATION_WAS_SUCCESSFUL;
}

/**
 * @brief Collect the kernel-side debugging information
 *
 * @param InfoRequest user-mode buffer to fill kernel information
 * @return UINT32 Filled entries
 */
UINT32
TestKernelGetInformation(PDEBUGGEE_KERNEL_AND_USER_TEST_INFORMATION InfoRequest)
{
    UINT32 Index = 0;

    //
    // Zero the memory
    //
    RtlZeroMemory(&InfoRequest[0], TEST_CASE_MAXIMUM_BUFFERS_TO_COMMUNICATE);

    //
    // *** Fill kernel functions information ***
    //

    // ------------------------------------------------------

    Index                    = 0;
    InfoRequest[Index].Value = (UINT64)ExAllocatePool2;
    memcpy(&InfoRequest[Index].Tag, "ExAllocatePool2", strlen("ExAllocatePool2") + 1);

    // ------------------------------------------------------

    Index                    = 1;
    InfoRequest[Index].Value = (UINT64)NtReadFile;
    memcpy(&InfoRequest[Index].Tag, "NtReadFile", strlen("NtReadFile") + 1);

    // ------------------------------------------------------

    Index                    = 2;
    InfoRequest[Index].Value = (UINT64)NtWriteFile;
    memcpy(&InfoRequest[Index].Tag, "NtWriteFile", strlen("NtWriteFile") + 1);

    // ------------------------------------------------------

    //
    // Check maximum index
    //
    if (Index > TEST_CASE_MAXIMUM_NUMBER_OF_KERNEL_TEST_CASES)
    {
        LogError("Err, test cases are above the supported buffers");
        return 0;
    }

    //
    // Return the index (add +1 because we start from zero)
    //
    return Index + 1;
}