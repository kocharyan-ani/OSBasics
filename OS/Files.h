#pragma once

#include "Utility.h"

namespace Files {
	// work with files
	bool copy_file(const TCHAR*, const TCHAR*);
	bool copy_file_reversed(const TCHAR*, const TCHAR*);

	enum Mode { Bytes, Words, Lines };
	bool copy_n_first_units_of_file(const TCHAR*, const TCHAR*, int, Mode);
	bool copy_n_last_units_of_file(const TCHAR*, const TCHAR*, int, Mode);
	bool copy_last_n_units_to_console_of_files(const TCHAR**, int, int, Mode);
	bool word_counts_of_files_to_std_output(const TCHAR**, int);
	bool change_creation_date_file(const TCHAR*);

	// work with standard I/O
	bool copy_file_to_std_output(const TCHAR*);
	bool copy_std_input_to_file(const TCHAR*);
	bool copy_std_input_to_std_output();

	// work with env
	bool copy_environment_to_file(const TCHAR* = 0);
	bool add_folder_to_path(const TCHAR*);
}
