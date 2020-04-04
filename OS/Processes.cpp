#include "Processes.h"

void Processes::open_notepad() {
    STARTUPINFO sInfo{ sizeof(sInfo) };
    PROCESS_INFORMATION pInfo{};

    TCHAR commandLine[] = _T("notepad.exe");
    if (!CreateProcess(NULL, commandLine, NULL, NULL, FALSE, 0, NULL, NULL, &sInfo, &pInfo)) {
        error_text_output();
        ExitProcess(1);
    }

    Sleep(2000);

    CloseHandle(pInfo.hProcess);
    CloseHandle(pInfo.hThread);

    ExitProcess(0);
}

void Processes::open_notepad_minimized() {
}

void Processes::open_notepad_and_terminate() {
    STARTUPINFO sInfo{ sizeof(sInfo) };
    PROCESS_INFORMATION pInfo{};

    TCHAR commandLine[] = _T("notepad.exe");
    if (!CreateProcess(NULL, commandLine, NULL, NULL, FALSE, 0, NULL, NULL, &sInfo, &pInfo)) {
        error_text_output();
        ExitProcess(1);
    }

    Sleep(2000);

    if (!TerminateProcess(pInfo.hProcess, 0)) {
        error_text_output();
        ExitProcess(1);
    }
    CloseHandle(pInfo.hProcess);
    CloseHandle(pInfo.hThread);

    ExitProcess(0);
}