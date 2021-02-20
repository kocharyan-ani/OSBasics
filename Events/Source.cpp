#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

const int ARRAY_SIZE = 1000;
int ARRAY[ARRAY_SIZE];
HANDLE event1_handle, event2_handle;

void error_text_output() {}

DWORD WINAPI first_thread(void*) {
	for (int i = 0; i < ARRAY_SIZE / 2; ++i) {
		ARRAY[i] = 1;
	}

	SetEvent(event1_handle);

	WaitForSingleObject(event2_handle, INFINITE);
	for (int i = 0; i < ARRAY_SIZE; ++i) {
		_tprintf(_T("%d "), ARRAY[i]);
	}
	_tprintf(_T("\n"));

	return 0;
}

DWORD WINAPI second_thread(void*) {
	WaitForSingleObject(event1_handle, INFINITE);

	for (int i = ARRAY_SIZE / 2; i < ARRAY_SIZE; ++i) {
		ARRAY[i] = 2;
	}

	SetEvent(event2_handle);
	return 0;
}

int _tmain() {

	event1_handle = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (NULL == event1_handle) {
		error_text_output();
		return 1;
	}

	event2_handle = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (NULL == event2_handle) {
		error_text_output();
		return 1;
	}

	HANDLE thread1_handle = CreateThread(NULL, 0, first_thread, NULL, 0, NULL);
	if(NULL == thread1_handle) {
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

	return 0;
}