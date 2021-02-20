#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

void error_text_output() {}

int _tmain() {
    DWORD id = GetCurrentProcessId();
    const int size = 10;
    TCHAR id_as_string[size];
    _itot_s(id, id_as_string, 10);

    STARTUPINFO sInfo{ sizeof(sInfo) };
    PROCESS_INFORMATION pInfo{};

    TCHAR commandLine[MAX_PATH + size + 1];
    _tcscpy_s(commandLine, _T("B.exe "));  // or the full path of executable file
    _tcscat_s(commandLine, id_as_string);
    if (!CreateProcess(NULL, commandLine, NULL, NULL, FALSE, 0, NULL, NULL, &sInfo, &pInfo)) {
        error_text_output();
        return 1;
    }

    Sleep(5000);

    CloseHandle(pInfo.hProcess);
    CloseHandle(pInfo.hThread);

    return 0;
}