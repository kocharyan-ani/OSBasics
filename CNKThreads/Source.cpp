#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

void error_text_output() {}

struct Info {
	int m_number;
	int m_result;

	Info(int n)
		: m_number(n)
		, m_result(1)
	{}

	void factorial() {
		for (int i = 2; i <= m_number; ++i) {
			m_result *= i;
		}
	}
};

DWORD WINAPI entry_function(void* parameter) {
	Info* information = static_cast<Info*>(parameter);
	information->factorial();
	return 0;
}

int _tmain() {
	const int N = 6;
	const int K = 4;
	const int NK = N - K;

	Info* information[] = { new Info(N), new Info(K), new Info(NK) };

	const int thread_count = 3;
	HANDLE thread_handles[thread_count]{};
	DWORD thread_ids[thread_count]{};

	for (int i = 0; i < thread_count; ++i) {
		thread_handles[i] = CreateThread(NULL, 0, entry_function, information[i], 0, &thread_ids[i]);
		if (NULL == thread_handles[i]) {
			error_text_output();
			return 1;
		}
	}

	if (WAIT_FAILED == WaitForMultipleObjects(thread_count, thread_handles, TRUE, INFINITE)) {
		error_text_output();
		return 1;
	}

	int CNK = information[0]->m_result / information[1]->m_result / information[2]->m_result;
	_tprintf(_T("CNK for N = %d, K = %d is : %d\n"), N, K, CNK);

	for (int i = 0; i < thread_count; ++i) {
		CloseHandle(thread_handles[i]);
	}

	return 0;
}