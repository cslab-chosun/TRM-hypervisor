/**
 * @file connect.cpp
 * @author Anonymized Author
 * @brief .connect command
 * @details
 * @version 0.1
 * @date 2020-05-27
 *
 * @copyright This project is released under the GNU Public License v3.
 *
 */
#include "pch.h"

//
// Global Variables
//
extern BOOLEAN g_IsConnectedToTRMHvLocally;
extern BOOLEAN g_IsConnectedToRemoteDebuggee;
extern BOOLEAN g_IsConnectedToRemoteDebugger;
extern BOOLEAN g_IsSerialConnectedToRemoteDebuggee;
extern BOOLEAN g_IsSerialConnectedToRemoteDebugger;
extern string  g_ServerPort;
extern string  g_ServerIp;

/**
 * @brief help of the .connect command
 *
 * @return VOID
 */
VOID
CommandConnectHelp()
{
    ShowMessages(".connect : connects to a remote or local machine to start "
                 "debugging.\n\n");

    ShowMessages("syntax : \t.connect [local]\n");
    ShowMessages("syntax : \t.connect [Ip (string)] [Port (decimal)]\n");

    ShowMessages("\n");
    ShowMessages("\t\te.g : .connect local\n");
    ShowMessages("\t\te.g : .connect 192.168.1.5 50000\n");
}

/**
 * @brief .connect command handler
 *
 * @param SplitCommand
 * @param Command
 * @return VOID
 */
VOID
CommandConnect(vector<string> SplitCommand, string Command)
{
    string ip;
    string port;

    if (g_IsConnectedToTRMHvLocally || g_IsConnectedToRemoteDebuggee ||
        g_IsConnectedToRemoteDebugger)
    {
        ShowMessages("you're connected to a debugger, please use '.disconnect' "
                     "command\n");
        return;
    }

    if (g_IsSerialConnectedToRemoteDebuggee ||
        g_IsSerialConnectedToRemoteDebugger)
    {
        ShowMessages("you're connected to a an instance of TRMHv, please use "
                     "'.debug close' command\n");
        return;
    }

    if (SplitCommand.size() == 1)
    {
        //
        // Means that user entered just a connect so we have to
        // ask to connect to what ?
        //
        ShowMessages("incorrect use of the '.connect'\n\n");
        CommandConnectHelp();
        return;
    }
    else if (SplitCommand.at(1) == "local" && SplitCommand.size() == 2)
    {
        //
        // connect to local debugger
        //
        ShowMessages("local debugging (vmi-mode)\n");
        g_IsConnectedToTRMHvLocally = TRUE;
        return;
    }
    else if (SplitCommand.size() == 3 || SplitCommand.size() == 2)
    {
        ip = SplitCommand.at(1);

        if (SplitCommand.size() == 3)
        {
            port = SplitCommand.at(2);
        }

        //
        // means that probably wants to connect to a remote
        // system, let's first check the if the parameters are
        // valid
        //
        if (!ValidateIP(ip))
        {
            ShowMessages("incorrect ip address\n");
            return;
        }

        if (SplitCommand.size() == 3)
        {
            if (!IsNumber(port) || stoi(port) > 65535 || stoi(port) < 0)
            {
                ShowMessages("incorrect port\n");
                return;
            }

            //
            // connect to remote debugger
            //
            g_ServerIp   = ip;
            g_ServerPort = port;
            RemoteConnectionConnect(ip.c_str(), port.c_str());
        }
        else
        {
            //
            // connect to remote debugger (default port)
            //
            g_ServerIp   = ip;
            g_ServerPort = DEFAULT_PORT;
            RemoteConnectionConnect(ip.c_str(), DEFAULT_PORT);
        }
    }
    else
    {
        ShowMessages("incorrect use of the '.connect'\n\n");
        CommandConnectHelp();
        return;
    }
}
