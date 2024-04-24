/**
 * @file TRMHv-cli.cpp
 * @author Anonymized Author
 * @brief Main TRMHv Cli source coede
 * @details
 * @version 0.1
 * @date 2020-04-11
 *
 * @copyright This project is released under the GNU Public License v3.
 *
 */
#include <Windows.h>
#include <string>
#include <conio.h>
#include <iostream>
#include <vector>

#include "SDK/TRMHvSdk.h"
#include "SDK/Imports/TRMHvCtrlImports.h"

using namespace std;

#pragma comment(lib, "HPRDBGCTRL.lib")

/**
 * @brief CLI main function
 *
 * @param argc
 * @param argv
 * @return int
 */
int
main(int argc, char * argv[])
{
    bool   ExitFromDebugger = false;
    string PreviousCommand;
    bool   Reset = false;

    //
    // Set console output code page to UTF-8
    //
    SetConsoleOutputCP(CP_UTF8);

    printf("TRMHv Debugger [version: %s, build: %s]\n", CompleteVersion, BuildVersion);
    printf("TRMHv is released under the GNU Public License v3 (GPLv3).\n\n");

    if (argc != 1)
    {
        //
        // User-passed arguments to the debugger
        //
        if (!strcmp(argv[1], "--script"))
        {
            //
            // Handle the script
            //
            TRMHvScriptReadFileAndExecuteCommandline(argc, argv);
        }
        else
        {
            printf("err, invalid command line options passed to the TRMHv!\n");
            return 1;
        }
    }

    while (!ExitFromDebugger)
    {
        TRMHvShowSignature();

        string CurrentCommand = "";

        //
        // Clear multiline
        //
        Reset = true;

    GetMultiLinecCommand:

        string TempCommand = "";

        getline(cin, TempCommand);

        if (cin.fail() || cin.eof())
        {
            cin.clear(); // reset cin state

            printf("\n\n");

            //
            // probably sth like CTRL+C pressed
            //
            continue;
        }

        //
        // Check for multi-line commands
        //
        if (TRMHvCheckMultilineCommand((char *)TempCommand.c_str(), Reset) == true)
        {
            //
            // It's a multi-line command
            //
            Reset = false;

            //
            // Save the command with a space separator
            //
            CurrentCommand += TempCommand + "\n";

            //
            // Show a small signature
            //
            printf("> ");

            //
            // Get next command
            //
            goto GetMultiLinecCommand;
        }
        else
        {
            //
            // Reset for future commands
            //
            Reset = true;

            //
            // Either the multi-line is finished or it's a
            // single line command
            //
            CurrentCommand += TempCommand;
        }

        if (!CurrentCommand.compare("") &&
            TRMHvContinuePreviousCommand())
        {
            //
            // Retry the previous command
            //
            CurrentCommand = PreviousCommand;
        }
        else
        {
            //
            // Save previous command
            //
            PreviousCommand = CurrentCommand;
        }

        int CommandExecutionResult = TRMHvInterpreter((char *)CurrentCommand.c_str());

        //
        // if the debugger encounters an exit state then the return will be 1
        //
        if (CommandExecutionResult == 1)
        {
            //
            // Exit from the debugger
            //
            ExitFromDebugger = true;
        }
        if (CommandExecutionResult != 2)
        {
            printf("\n");
        }
    }

    return 0;
}
