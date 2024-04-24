/**
 * @file TRMHvCtrlImports.h
 * @author Anonymized Author
 * @brief Headers relating exported functions from controller interface
 * @version 0.2
 * @date 2023-02-02
 *
 * @copyright This project is released under the GNU Public License v3.
 *
 */
#pragma once

#ifdef TRMHv_HPRDBGCTRL
#    define IMPORT_EXPORT_CTRL __declspec(dllexport)
#else
#    define IMPORT_EXPORT_CTRL __declspec(dllimport)
#endif

//
// Header file of HPRDBGCTRL
// Imports
//
#ifdef __cplusplus
extern "C" {
#endif

//
// Support Detection
//
IMPORT_EXPORT_CTRL bool TRMHvVmxSupportDetection();
IMPORT_EXPORT_CTRL void TRMHvReadVendorString(char *);

//
// VMM Module
//
IMPORT_EXPORT_CTRL int TRMHvLoadVmm();
IMPORT_EXPORT_CTRL int TRMHvUnloadVmm();
IMPORT_EXPORT_CTRL int TRMHvInstallVmmDriver();
IMPORT_EXPORT_CTRL int TRMHvUninstallVmmDriver();
IMPORT_EXPORT_CTRL int TRMHvStopVmmDriver();

//
// General imports
//
IMPORT_EXPORT_CTRL int TRMHvInterpreter(char * Command);
IMPORT_EXPORT_CTRL void TRMHvShowSignature();
IMPORT_EXPORT_CTRL void TRMHvSetTextMessageCallback(Callback handler);
IMPORT_EXPORT_CTRL int TRMHvScriptReadFileAndExecuteCommandline(int argc, char * argv[]);
IMPORT_EXPORT_CTRL bool TRMHvContinuePreviousCommand();
IMPORT_EXPORT_CTRL bool TRMHvCheckMultilineCommand(char * CurrentCommand, bool Reset);

#ifdef __cplusplus
}
#endif
