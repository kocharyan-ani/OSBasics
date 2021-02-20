#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

void error_text_output() {}

const int BUFFER_SIZE = 10;
const TCHAR* result_file_names[] = { _T("..\\file1.txt"), _T("..\\file2.txt"), _T("..\\file3.txt") };

HANDLE create_child_process(int number, int process_number) {
	TCHAR number_as_string[BUFFER_SIZE];
	_itot_s(number, number_as_string, 10);
	if (!SetEnvironmentVariable(number_as_string, number_as_string)) {
		error_text_output();
		return NULL;
	}

	STARTUPINFO sInfo{ sizeof(sInfo) };
	PROCESS_INFORMATION pInfo{};

	TCHAR commandLine[MAX_PATH + 2 * BUFFER_SIZE + 2];
	_tcscpy_s(commandLine, _T("Factorial.exe "));  // or the full path of executable file
	_tcscat_s(commandLine, number_as_string);
	_tcscat_s(commandLine, _T(" "));
	_tcscat_s(commandLine, result_file_names[process_number]);
	if (!CreateProcess(NULL, commandLine, NULL, NULL, FALSE, 0, NULL, NULL, &sInfo, &pInfo)) {
		error_text_output();
		return NULL;
	}

	CloseHandle(pInfo.hThread);
	return pInfo.hProcess;
}

int _tmain() {
	const int N = 6;
	const int K = 4;
	const int NK = N - K;

	const int child_process_count = 3;
	int numbers[child_process_count] = { N, K, NK };
	HANDLE child_processes[child_process_count]{};
	for (int i = 0; i < child_process_count; ++i) {
		if ((child_processes[i] = create_child_process(numbers[i], i)) == NULL) {
			return 1;
		}
	}

	if (WAIT_FAILED == WaitForMultipleObjects(child_process_count, child_processes, TRUE, INFINITE)) {
		error_text_output();
		return 1;
	}

	for (HANDLE h : child_processes) {
		CloseHandle(h);
	}
	
	HANDLE result_files[child_process_count]{};
	for (int i = 0; i < child_process_count; ++i) {
		result_files[i] = CreateFile(result_file_names[i], GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
		if (INVALID_HANDLE_VALUE == result_files[i]) {
			error_text_output();
			return 1;
		}
	}

	int result_numbers[child_process_count]{};
	for (int i = 0; i < child_process_count; ++i) {
		TCHAR buffer[BUFFER_SIZE]{};
		DWORD r{};
		if (!ReadFile(result_files[i], buffer, BUFFER_SIZE * sizeof(TCHAR), &r, NULL) || r == 0) {
			error_text_output();
			return 1;
		}
		result_numbers[i] = _ttoi(buffer);
		CloseHandle(result_files[i]);
	}

	int CNK = result_numbers[0] / result_numbers[1] / result_numbers[2];
	_tprintf(_T("CNK for N = %d, K = %d is : %d\n"), N, K, CNK);

	return 0;
}
