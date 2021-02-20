#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

void error_text_output() {}

const int BUFFER_SIZE = 10;

int factorial(int number) {
	int result{ 1 };
	for (int i = 2; i <= number; ++i) {
		result *= i;
	}
	return result;
}

int _tmain(int argc, TCHAR* argv[]) {
	if (argc >= 3) {
		TCHAR buffer[BUFFER_SIZE];
		if (0 == GetEnvironmentVariable(argv[1], buffer, BUFFER_SIZE)) {
			error_text_output();
			return 1;
		}

		int result = factorial(_ttoi(buffer));
		_itot_s(result, buffer, 10);
		
		HANDLE h = CreateFile(argv[2], GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (INVALID_HANDLE_VALUE == h) {
			error_text_output();
			return 1;
		}
		DWORD w{};
		if (!WriteFile(h, buffer, _tcslen(buffer) * sizeof(TCHAR), &w, NULL) || w == 0) {
			error_text_output();
			return 1;
		}
		CloseHandle(h);
	}

	return 0;
}