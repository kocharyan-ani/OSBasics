#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

CRITICAL_SECTION cs;
int variable = 0;

void error_text_output() {}

DWORD WINAPI first_thread(void*) {
	srand(0);
	int count = rand() % 100;
	for (int i = 0; i < count; ++i) {
		EnterCriticalSection(&cs);
		variable += rand();
		_tprintf(_T("Global variable's value on %d-st iteration is %d\n"), i, variable);
		LeaveCriticalSection(&cs);
	}

	return 0;
}

DWORD WINAPI second_thread(void*) {
	srand(1);
	int count = rand() % 100;
	for (int i = 0; i < count; ++i) {
		EnterCriticalSection(&cs);
		variable -= rand();
		_tprintf(_T("Global variable's value %d-st iteration is %d\n"), i, variable);
		LeaveCriticalSection(&cs);
	}

	return 0;
}

int _tmain() {
	InitializeCriticalSection(&cs);

	HANDLE thread1_handle = CreateThread(NULL, 0, first_thread, NULL, 0, NULL);
	if (NULL == thread1_handle) {
		error_text_output();
		return 1;
	}

	HANDLE thread2_handle = CreateThread(NULL, 0, second_thread, NULL, 0, NULL);
	if (NULL == thread2_handle) {
		error_text_output();
		return 1;
	}

	HANDLE handles[2] = { thread1_handle, thread2_handle };
	if (WAIT_FAILED == WaitForMultipleObjects(2, handles, TRUE, INFINITE)) {
		error_text_output();
		return 1;
	}

	CloseHandle(thread1_handle);
	CloseHandle(thread2_handle);
	DeleteCriticalSection(&cs);

	_tprintf(_T("Global variable's final value is %d\n"), variable);

	return 0;
}