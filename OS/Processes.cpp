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
        CloseHandle(pInfo.hProcess);
        CloseHandle(pInfo.hThread);
        error_text_output();
        ExitProcess(1);
    }
    CloseHandle(pInfo.hProcess);
    CloseHandle(pInfo.hThread);

    ExitProcess(0);
}

void Processes::open_notepad_and_get_exit_code() {
    STARTUPINFO sInfo{ sizeof(sInfo) };
    PROCESS_INFORMATION pInfo{};

    TCHAR commandLine[] = _T("notepad.exe");
    if (!CreateProcess(NULL, commandLine, NULL, NULL, FALSE, 0, NULL, NULL, &sInfo, &pInfo)) {
        error_text_output();
        ExitProcess(1);
    }

    Sleep(5000);

    DWORD exit_code{};
    if (!GetExitCodeProcess(pInfo.hProcess, &exit_code)) {
        CloseHandle(pInfo.hProcess);
        CloseHandle(pInfo.hThread);
        error_text_output();
        ExitProcess(1);
    }
    if (exit_code == STILL_ACTIVE) {
        _tprintf(_T("notepad.exe process is still active\n"));
    }
    else {
        _tprintf(_T("notepad.exe process exited with code: %d\n"), exit_code);
    }

    CloseHandle(pInfo.hProcess);
    CloseHandle(pInfo.hThread);

    ExitProcess(0);
}

void Processes::open_notepad_and_wait() {
    STARTUPINFO sInfo{ sizeof(sInfo) };
    PROCESS_INFORMATION pInfo{};

    TCHAR commandLine[] = _T("notepad.exe");
    if (!CreateProcess(NULL, commandLine, NULL, NULL, FALSE, 0, NULL, NULL, &sInfo, &pInfo)) {
        error_text_output();
        ExitProcess(1);
    }

    DWORD r = WaitForSingleObject(pInfo.hProcess, 5000);
    switch (r) {
    case WAIT_OBJECT_0:
        _tprintf(_T("notepad.exe process exited\n"));
        break;
    case WAIT_TIMEOUT:
        _tprintf(_T("notepad.exe process is still active\n"));
        break;
    case WAIT_FAILED:
        CloseHandle(pInfo.hProcess);
        CloseHandle(pInfo.hThread);
        error_text_output();
        ExitProcess(1);
    }

    CloseHandle(pInfo.hProcess);
    CloseHandle(pInfo.hThread);

    ExitProcess(0);
}