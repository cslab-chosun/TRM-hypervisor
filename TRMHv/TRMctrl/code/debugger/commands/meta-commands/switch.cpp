/**
 * @file switch.cpp
 * @author Anonymized Author
 * @brief .switch command
 * @details
 * @version 0.1
 * @date 2022-01-31
 *
 * @copyright This project is released under the GNU Public License v3.
 *
 */
#include "pch.h"

//
// Global Variables
//
extern ACTIVE_DEBUGGING_PROCESS g_ActiveProcessDebuggingState;
extern BOOLEAN                  g_IsSerialConnectedToRemoteDebuggee;

/**
 * @brief help of the .switch command
 *
 * @return VOID
 */
VOID
CommandSwitchHelp()
{
    ShowMessages(".switch : shows the list of active debugging threads and switches "
                 "between processes and threads in VMI Mode.\n\n");

    ShowMessages("syntax : \t.switch \n");
    ShowMessages("syntax : \t.switch [pid ProcessId (hex)]\n");
    ShowMessages("syntax : \t.switch [tid ThreadId (hex)]\n");

    ShowMessages("\n");
    ShowMessages("\t\te.g : .switch list\n");
    ShowMessages("\t\te.g : .switch pid b60 \n");
    ShowMessages("\t\te.g : .switch tid b60 \n");
}

/**
 * @brief .switch command handler
 *
 * @param SplitCommand
 * @param Command
 * @return VOID
 */
VOID
CommandSwitch(vector<string> SplitCommand, string Command)
{
    UINT32 PidOrTid = NULL;

    if (SplitCommand.size() > 3 || SplitCommand.size() == 2)
    {
        ShowMessages("incorrect use of the '.switch'\n\n");
        CommandSwitchHelp();
        return;
    }

    //
    // .attach and .detach commands are only supported in VMI Mode
    //
    if (g_IsSerialConnectedToRemoteDebuggee)
    {
        ShowMessages("err, the '.switch' command is only usable in VMI Mode, "
                     "you can use the '.process', or the '.thread' "
                     "in Debugger Mode\n");
        return;
    }

    //
    // Perform switching or listing the threads
    //
    if (SplitCommand.size() == 1)
    {
        UdShowListActiveDebuggingProcessesAndThreads();
    }
    else if (!SplitCommand.at(1).compare("pid"))
    {
        if (!ConvertStringToUInt32(SplitCommand.at(2), &PidOrTid))
        {
            ShowMessages("please specify a correct hex value for process id\n\n");
            return;
        }

        //
        // Switch by pid
        //
        if (UdSetActiveDebuggingThreadByPidOrTid(PidOrTid, FALSE))
        {
            ShowMessages("switched to process id: %x\n", PidOrTid);
        }
    }
    else if (!SplitCommand.at(1).compare("tid"))
    {
        if (!ConvertStringToUInt32(SplitCommand.at(2), &PidOrTid))
        {
            ShowMessages("please specify a correct hex value for thread id\n\n");
            return;
        }

        //
        // Switch by tid
        //
        if (UdSetActiveDebuggingThreadByPidOrTid(PidOrTid, TRUE))
        {
            ShowMessages("switched to thread id: %x\n", PidOrTid);
        }
    }
    else
    {
        ShowMessages("err, couldn't resolve error at '%s'\n",
                     SplitCommand.at(1).c_str());
        return;
    }
}
