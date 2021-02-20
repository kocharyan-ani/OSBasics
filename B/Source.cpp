#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

void error_text_output() {}

int _tmain(int argc, TCHAR* argv[]) {
	if (argc >= 2) {
        const int t = 7000; // or 7000

		DWORD parent_id = _ttoi(argv[1]);
        HANDLE parent_handle = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, parent_id);
        if (NULL == parent_handle) {
            error_text_output();
            return 1;
        }

        Sleep(t);

        DWORD exit_code{};
        if (!GetExitCodeProcess(parent_handle, &exit_code)) {
            CloseHandle(parent_handle);
            error_text_output();
            return 2;;
        }
        if (exit_code == STILL_ACTIVE) {
            _tprintf(_T("Parent process is still active\n"));
        }
        else {
            _tprintf(_T("Parent process exited with code: %d\n"), exit_code);
        }

        CloseHandle(parent_handle);
	}

	return 0;
}