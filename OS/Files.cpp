#include "Files.h"

namespace {
	void CloseHandles(HANDLE h[], int n) {
		for (int i = 0; i < n; ++i) {
			if (!CloseHandle(h[i])) {
				_tprintf(_T("Error while closing handle: "));
				error_text_output();
			}
		}
	}
}

bool Files::copy_file(const TCHAR* name1, const TCHAR* name2) {
	HANDLE h[2];
	h[0] = CreateFile(name1, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (INVALID_HANDLE_VALUE == h[0]) {
		error_text_output();
		return false;
	}

	h[1] = CreateFile(name2, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == h[1]) {
		CloseHandles(h, 1);
		error_text_output();
		return false;
	}
	
	const int s = 10;
	BYTE buffer[s];
	DWORD r = -1, w;
	while (ReadFile(h[0], buffer, s, &r, NULL) && r != 0) {
		if (!WriteFile(h[1], buffer, r, &w, NULL) || r != w) {
			CloseHandles(h, 2);
			error_text_output();
			return false;
		}
	}
	CloseHandles(h, 2);
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

	return true;
}

bool Files::copy_file_to_std_output(const TCHAR* name) {
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