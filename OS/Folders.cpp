#include "Folders.h"

#include <vector>
#include <algorithm>

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
		return true;
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

bool Folders::union_of_files(const TCHAR** names, int file_count, const TCHAR* name) {
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