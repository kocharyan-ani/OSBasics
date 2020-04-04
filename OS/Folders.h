#pragma once

#include "Utility.h"

namespace Folders {
	bool traverse_current_folder();
	bool change_current_dir_and_copy_file(const TCHAR*);
	bool traverse_parent_folders();
	bool traverse_sub_folders();
	bool word_count_of_files_in_current_folder();
	bool union_of_files(const TCHAR*);
	bool traverse_last_created_sub_folder(const TCHAR*);
	bool last_n_lines_of_files_in_folder(const TCHAR*);
	bool sort_current_folder_by_sizes();
	bool sort_current_folder_by_names();
}
