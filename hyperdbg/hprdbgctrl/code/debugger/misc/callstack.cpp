/**
 * @file callstack.cpp
 * @author Sina Karvandi (sina@hyperdbg.org)
 * @brief Callstack related routines
 * @details
 * @version 0.1
 * @date 2022-03-06
 *
 * @copyright This project is released under the GNU Public License v3.
 *
 */
#include "..\hprdbgctrl\pch.h"

//
// Global Variables
//
extern BOOLEAN g_AddressConversion;

/**
 * @brief Walkthrough the stack
 * @details This code is borrowed from here :
 * https://github.com/electronicarts/EAThread/blob/master/source/x86/eathread_callstack_x86.cpp
 * 
 * @param ReturnAddress  
 * @param IndexOfCallFromReturnAddress  
 * 
 * @return BOOLEAN
 */
BOOLEAN
CallstackReturnAddressToCallingAddress(UCHAR * ReturnAddress, PUINT32 IndexOfCallFromReturnAddress)
{
    //
    // While negative array indices can be considered non-idiomatic it
    // was felt that they are semantically appropriate as this code bases
    // its comparisons from the return address and that it would be cleaner
    // than using *(ReturnAddress - index).
    //

    //
    // Three op-codes are used for the call instruction, 9A, E8, and FF.
    // For a reference on the IA32 instruction format, see:
    // http://www.cs.princeton.edu/courses/archive/spr06/cos217/reading/ia32vol2.pdf
    //

    //
    // 9A cp - CALL ptr16:32 (7-byte)
    //
    if (ReturnAddress[-7] == 0x9A)
    {
        *IndexOfCallFromReturnAddress = 7;
        return TRUE;
    }
    // E8 cd - CALL rel32 (5-byte)
    else if (ReturnAddress[-5] == 0xE8)
    {
        *IndexOfCallFromReturnAddress = 5;
        return TRUE;
    }
    else
    {
        //
        // The third opcode to specify "call" instructions is FF.
        // Unfortunately this instruction also needs the succeeding ModR/M
        // byte to fully determine instruction length. The SIB value is
        // another byte used for extending the range of addressing modes
        // supported by the ModR/M byte. The values of this ModR/M byte
        // used in conjunction with the call instruction are as follows:
        //
        // 7-byte call:
        // FF [ModR/M] [SIB] [4-byte displacement]
        //    * ModR/M is either 0x94 or 0x9C
        //
        // 6-byte call:
        // FF [ModR/M] [4-byte displacement]
        //    * ModR/M can be:
        //      * 0x90 - 0x9F EXCLUDING 0x94 or 0x9C
        //      * 0x15 or 0x1D
        //
        // 4-byte call:
        // FF [ModR/M] [SIB] [1-byte displacement]
        //    * ModR/M is either 0x54 or 0x5C
        //
        // 3-byte call:
        // FF [ModR/M] [1-byte displacement]
        //    * ModR/M can be:
        //      * 0x50 - 0x5F EXCLUDING 0x54 or 0x5C
        // FF [ModR/M] [SIB]
        //    * ModR/M is either 0x14 or 0x1C
        //
        // 2-byte call:
        // FF [ModR/M]
        //    * ModR/M can be:
        //      * 0xD0 - 0xDF
        //      * 0x10 - 0x1F EXCEPT 0x14, 0x15, 0x1C, or 0x1D
        //

        //
        // The mask of F8 is used because we want to mask out the bottom
        // three bits (which are most often used for register selection)
        //
        const unsigned char rm_mask = 0xF8;

        //
        // 7-byte format:
        //
        if (ReturnAddress[-7] == 0xFF &&
            (ReturnAddress[-6] == 0x94 || ReturnAddress[-6] == 0x9C))
        {
            *IndexOfCallFromReturnAddress = 7;
            return TRUE;
        }

        //
        // 6-byte format:
        // FF [ModR/M] [4-byte displacement]
        //
        else if (ReturnAddress[-6] == 0xFF &&
                 ((ReturnAddress[-5] & rm_mask) == 0x90 || (ReturnAddress[-5] & rm_mask) == 0x98) &&
                 (ReturnAddress[-5] != 0x94 && ReturnAddress[-5] != 0x9C))
        {
            *IndexOfCallFromReturnAddress = 6;
            return TRUE;
        }

        //
        // Alternate 6-byte format:
        //
        else if (ReturnAddress[-6] == 0xFF &&
                 (ReturnAddress[-5] == 0x15 || ReturnAddress[-5] == 0x1D))
        {
            *IndexOfCallFromReturnAddress = 6;
            return TRUE;
        }

        //
        // 4-byte format:
        // FF [ModR/M] [SIB] [1-byte displacement]
        //
        else if (ReturnAddress[-4] == 0xFF &&
                 (ReturnAddress[-3] == 0x54 || ReturnAddress[-3] == 0x5C))
        {
            *IndexOfCallFromReturnAddress = 4;
            return TRUE;
        }

        //
        // 3-byte format:
        // FF [ModR/M] [1-byte displacement]
        //
        else if (ReturnAddress[-3] == 0xFF &&
                 ((ReturnAddress[-2] & rm_mask) == 0x50 || (ReturnAddress[-2] & rm_mask) == 0x58) &&
                 (ReturnAddress[-2] != 0x54 && ReturnAddress[-2] != 0x5C))
        {
            *IndexOfCallFromReturnAddress = 3;
            return TRUE;
        }

        //
        // Alternate 3-byte format:
        // FF [ModR/M] [SIB]
        //
        else if (ReturnAddress[-3] == 0xFF &&
                 (ReturnAddress[-2] == 0x14 || ReturnAddress[-2] == 0x1C))
        {
            *IndexOfCallFromReturnAddress = 3;
            return TRUE;
        }

        //
        // 2-byte calling format:
        // FF [ModR/M]
        //
        else if (ReturnAddress[-2] == 0xFF &&
                 ((ReturnAddress[-1] & rm_mask) == 0xD0 || (ReturnAddress[-1] & rm_mask) == 0xD8))
        {
            *IndexOfCallFromReturnAddress = 2;
            return TRUE;
        }

        //
        // Alternate 2-byte calling format:
        // FF [ModR/M]
        //
        else if (ReturnAddress[-2] == 0xFF &&
                 ((ReturnAddress[-1] & rm_mask) == 0x10 || (ReturnAddress[-1] & rm_mask) == 0x18) &&
                 (ReturnAddress[-1] != 0x14 && ReturnAddress[-1] != 0x15 &&
                  ReturnAddress[-1] != 0x1C && ReturnAddress[-1] != 0x1D))
        {
            *IndexOfCallFromReturnAddress = 2;
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }

    return FALSE;
}

/**
 * @brief Show stack frames
 * 
 * @param CallstackFrames  
 * 
 * @return VOid
 */
VOID
CallstackShowFrames(PDEBUGGER_SINGLE_CALLSTACK_FRAME CallstackFrames, UINT32 FrameCount)
{
    UINT32                                                 CallLength;
    UINT64                                                 CallAddress;
    UINT64                                                 UsedBaseAddress;
    std::map<UINT64, LOCAL_FUNCTION_DESCRIPTION>::iterator Iterate;

    //
    // Print callstack frames
    //
    for (size_t i = 0; i < FrameCount; i++)
    {
        if (CallstackFrames[i].IsValidAddress && CallstackFrames[i].IsExecutable)
        {
            ShowMessages("[%x] %llx ", i, CallstackFrames[i].Value);

            if (CallstackReturnAddressToCallingAddress(
                    (unsigned char *)&CallstackFrames[i].InstructionBytesOnRip[MAXIMUM_CALL_INSTR_SIZE],
                    &CallLength))
            {
                //
                // Computer the "call" instruction address
                //
                CallAddress = CallstackFrames[i].Value - CallLength;
                ShowMessages("- call from ");

                //
                // Apply addressconversion of settings here
                //
                if (g_AddressConversion)
                {
                    if (SymbolShowFunctionNameBasedOnAddress(CallAddress, &UsedBaseAddress))
                    {
                        ShowMessages("\n");
                    }
                    else
                    {
                        ShowMessages("%llx\n", CallAddress);
                    }
                }
                else
                {
                    ShowMessages("%llx\n", CallAddress);
                }
            }
            else
            {
                ShowMessages("(pointer to code - not call)\n");
            }
        }
        else
        {
            ShowMessages("[%x]\t%llx\n", i, CallstackFrames[i].Value);
        }
    }
}
