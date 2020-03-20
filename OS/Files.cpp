#include "Files.h"

bool Files::copy_file(const TCHAR* name1, const TCHAR* name2) {
	HANDLE h1 = CreateFile(name1, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (INVALID_HANDLE_VALUE == h1) {
		error_text_output();
		return false;
	}

	HANDLE h2 = CreateFile(name2, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == h2) {
		CloseHandle(h1);
		error_text_output();
		return false;
	}
	
	const int s = 10;
	BYTE buffer[s];
	DWORD r = -1, w;
	while (ReadFile(h1, buffer, s, &r, NULL) && r != 0) {
		if (!WriteFile(h2, buffer, r, &w, NULL) || r != w) {
			CloseHandle(h1);
			CloseHandle(h2);
			error_text_output();
			return false;
		}
	}
	CloseHandle(h1);
	CloseHandle(h2);
	if (r != 0) {
		error_text_output();
		return false;
	}

	return true;
}

bool Files::copy_file_reversed(const TCHAR* name1, const TCHAR* name2) {
	return true;
}

bool Files::copy_n_first_units_of_file(const TCHAR* name1, const TCHAR* name2, int unit_count, Mode mode) {
	return true;
}

bool Files::copy_n_last_units_of_file(const TCHAR* name1, const TCHAR* name2, int unit_count, Mode mode) {
	return true;
}

bool Files::copy_last_n_units_to_console_of_files(const TCHAR** names, int file_count, int unit_count, Mode mode) {
	return true;
}

bool Files::word_counts_of_files_to_std_output(const TCHAR** names, int file_count) {
	return true;
}

bool Files::change_creation_date_file(const TCHAR* name) {
	SetLastError(0);
	HANDLE h = CreateFile(name, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == h) {
		error_text_output();
		return false;
	}
	if (ERROR_ALREADY_EXISTS != GetLastError()) {
		CloseHandle(h);
		return true;
	}
	FILETIME creationTime{};
	SYSTEMTIME currentTime{};
	GetSystemTime(&currentTime);
	if (!FileTimeToSystemTime(&creationTime, &currentTime)) {
		CloseHandle(h);
		return false;
	}
	if (!SetFileTime(h, &creationTime, NULL, NULL)) {
		CloseHandle(h);
		return false;
	}
	CloseHandle(h);
	return true;
}

bool Files::copy_file_to_std_output(const TCHAR* name) {
	HANDLE hFile = CreateFile(name, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (INVALID_HANDLE_VALUE == hFile) {
		error_text_output();
		return false;
	}

	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	if (INVALID_HANDLE_VALUE == hOutput) {
		CloseHandle(hFile);
		error_text_output();
		return false;
	}

	const int s = 10;
	BYTE buffer[s];
	DWORD r = -1, w;
	while (ReadFile(hFile, buffer, s, &r, NULL) && r != 0) {
		if (!WriteFile(hOutput, buffer, r, &w, NULL) || r != w) {
			CloseHandle(hFile);
			error_text_output();
			return false;
		}
	}
	CloseHandle(hFile);
	if (r != 0) {
		error_text_output();
		return false;
	}

	return true;
}

bool Files::copy_std_input_to_file(const TCHAR* name) {
	return true;
}

bool Files::copy_std_input_to_std_output() {
	return true;
}

bool Files::copy_environment_to_file(const TCHAR* name) {
	return true;
}

bool Files::add_folder_to_path(const TCHAR* name) {
	return true;
}