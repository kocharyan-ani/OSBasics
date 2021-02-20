#include "Folders.h"

#include <vector>
#include <algorithm>
#include <shellapi.h>

bool Folders::traverse_current_folder() {
	SetLastError(0);
	WIN32_FIND_DATA data;
	HANDLE h = FindFirstFile(_T("*"), &data);
	if (INVALID_HANDLE_VALUE == h) {
		error_text_output();
		return false;
	}

	SYSTEMTIME st;
	do {
		FileTimeToSystemTime(&data.ftCreationTime, &st);
		_tprintf(_T("Name: %s, Size %d, Date: %d/%d/%d\n"), data.cFileName, data.nFileSizeLow, st.wDay, st.wMonth, st.wYear);
	} while (FindNextFile(h, &data));
	if (GetLastError() != ERROR_NO_MORE_FILES) {
		error_text_output();
		return false;
	}

	FindClose(h);
	
	return true;
}

bool Folders::change_current_dir_and_copy_file(const TCHAR* name) {
	return true;
}

bool Folders::traverse_parent_folders() {
	return true;
}

namespace {
	bool is_directory(DWORD attributes) {
		return (attributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
	}

	bool contains_sub_directory(const TCHAR* dir) {
		TCHAR name[MAX_PATH];
		_tcscpy_s(name, dir);
		_tcscat_s(name, _T("\\\\*"));

		WIN32_FIND_DATA data;
		HANDLE h = FindFirstFile(name, &data);
		if (INVALID_HANDLE_VALUE == h) {
			error_text_output();
			return false;
		}

		do {
			if (is_directory(data.dwFileAttributes) && 
				_tcscmp(data.cFileName, _T(".")) != 0 && 
				_tcscmp(data.cFileName, _T("..")) != 0) {
				FindClose(h);
				return true;
			}
		} while (FindNextFile(h, &data));

		FindClose(h);
		return false;
	}
}

bool Folders::traverse_sub_folders() {
	WIN32_FIND_DATA data;
	HANDLE h = FindFirstFile(_T("*"), &data);
	if (INVALID_HANDLE_VALUE == h) {
		error_text_output();
		return false;
	}

	do {
		if (is_directory(data.dwFileAttributes) && !contains_sub_directory(data.cFileName)) {
			_tprintf(_T("Name: %s\n"), data.cFileName);
		}
	} while (FindNextFile(h, &data));

	FindClose(h);
	/*if (GetLastError() != ) {
		error_text_output();
		return false;
	}*/
	return true;
}

bool Folders::word_count_of_files_in_current_folder() {
	return true;
}

namespace {
	bool copy_with_handles(HANDLE hIn, HANDLE hOut) {
		const int s = 10;
		BYTE buffer[s];
		DWORD r = -1, w;
		while (ReadFile(hIn, buffer, s, &r, NULL) && r != 0) {
			if (!WriteFile(hOut, buffer, r, &w, NULL) || r != w) {
				error_text_output();
				return false;
			}
		}
		if (r != 0) {
			error_text_output();
			return false;
		}
		return true;
	}
}

// TEXT.txt
bool Folders::union_of_files(const TCHAR* name) {
	HANDLE hOut = CreateFile(name, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hOut) {
		error_text_output();
		return false;
	}

	int argc{};
	TCHAR** argv{};
	argv = (TCHAR**)CommandLineToArgvW(GetCommandLineW(), &argc);
	if (argv == NULL) {
		error_text_output();
		CloseHandle(hOut);
		return false;
	}
	TCHAR dir[MAX_PATH];
	_tcscpy_s(dir, (argc >= 2) ? argv[1] : _T("."));
	_tcscat_s(dir, _T("//*.txt"));

	WIN32_FIND_DATA info;
	HANDLE hSearch = FindFirstFile(dir, &info);
	if (INVALID_HANDLE_VALUE == hSearch) {
		error_text_output();
		CloseHandle(hOut);
		return 1;
	}

	HANDLE hIn;
	do {
		if (_tcscmp(info.cFileName, name) == 0) {
			continue;
		}
		hIn = CreateFile(info.cFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
		if (INVALID_HANDLE_VALUE == hIn) {
			error_text_output();
			CloseHandle(hOut);
			FindClose(hSearch);
			return 1;
		}
		if (!copy_with_handles(hIn, hOut)) {
			_tprintf(_T("Copy failed for file %s\n"), info.cFileName);
			CloseHandle(hOut);
			FindClose(hSearch);
			return 1;
		}
		CloseHandle(hIn);
	} while (FindNextFile(hSearch, &info));

	FindClose(hSearch);
	CloseHandle(hOut);
	return true;
}

bool Folders::traverse_last_created_sub_folder(const TCHAR* name) {
	return true;
}

bool Folders::last_n_lines_of_files_in_folder(const TCHAR* name) {
	return true;
}

namespace {
	bool less_by_sizes(WIN32_FIND_DATA d1, WIN32_FIND_DATA d2) {
		return d1.nFileSizeLow < d2.nFileSizeLow;
	}

	bool less_by_names(WIN32_FIND_DATA d1, WIN32_FIND_DATA d2) {
		return std::string(d1.cFileName) < std::string(d2.cFileName);
	}
}

bool Folders::sort_current_folder_by_sizes() {
	std::vector<WIN32_FIND_DATA> data_container;
	WIN32_FIND_DATA data;
	HANDLE h = FindFirstFile(_T("*"), &data);
	if (INVALID_HANDLE_VALUE == h) {
		error_text_output();
		return false;
	}

	do {
		data_container.push_back(data);
	} while (FindNextFile(h, &data));

	FindClose(h);
	/*if (GetLastError() != ) {
		error_text_output();
		return false;
	}*/

	std::sort(data_container.begin(), data_container.end() - 1, less_by_sizes);

	for (auto d : data_container) {
		_tprintf(_T("Name: %s, Size: %d\n"), d.cFileName, d.nFileSizeLow);
	}

	return true;
}

bool Folders::sort_current_folder_by_names() {
	std::vector<WIN32_FIND_DATA> data_container;
	WIN32_FIND_DATA data;
	HANDLE h = FindFirstFile(_T("*"), &data);
	if (INVALID_HANDLE_VALUE == h) {
		error_text_output();
		return false;
	}

	do {
		if (!is_directory(data.dwFileAttributes)) {
			data_container.push_back(data);
		}
	} while (FindNextFile(h, &data));

	FindClose(h);
	/*if (GetLastError() != ) {
		error_text_output();
		return false;
	}*/

	std::sort(data_container.begin(), data_container.end() - 1, less_by_names);

	for (auto d : data_container) {
		_tprintf(_T("Name: %s - %d\n"), d.cFileName, d.nFileSizeLow);
	}

	return true;
}