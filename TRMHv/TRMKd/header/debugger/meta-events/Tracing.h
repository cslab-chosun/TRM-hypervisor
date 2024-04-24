/**
 * @file Tracing.h
 * @author Anonymized Author
 * @brief Headers for the tracing functions
 * @details
 * @version 0.7
 * @date 2023-11-03
 *
 * @copyright This project is released under the GNU Public License v3.
 *
 */
#pragma once

//////////////////////////////////////////////////
//				   Functions					//
//////////////////////////////////////////////////

VOID
TracingHandleMtf(PROCESSOR_DEBUGGING_STATE * DbgState);

VOID
TracingRestoreSystemState(PROCESSOR_DEBUGGING_STATE * DbgState);

VOID
TracingCheckForContinuingSteps(PROCESSOR_DEBUGGING_STATE * DbgState);

VOID
TracingPerformInstrumentationStepIn(PROCESSOR_DEBUGGING_STATE * DbgState);

VOID
TracingPerformRegularStepInInstruction(PROCESSOR_DEBUGGING_STATE * DbgState);
