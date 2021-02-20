#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

#include "Files.h"
#include "Folders.h"

int _tmain(int argc, TCHAR* argv[]) {
	
	/*if (argc > 3) {
		_tprintf(_T("Console output before change of std output!\n"));	// output will be on console
		Files::copy_file_to_std_output(argv[1]);	// output will be on console

		// Change std output to a file
		HANDLE hFile = CreateFile(argv[2], GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (INVALID_HANDLE_VALUE == hFile) {
			error_text_output();
			return 1;
		}
		if (!SetStdHandle(STD_OUTPUT_HANDLE, hFile)) {
			error_text_output();
			return 2;
		}
		_tprintf(_T("\nConsole output after change of std output!\n"));	// output will be on console
		Files::copy_file_to_std_output(argv[1]);	// output will be in file

		// Get handle of console output
		HANDLE hConsole = CreateFile(_T("CONOUT$"), GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
		if (INVALID_HANDLE_VALUE == hConsole) {
			error_text_output();
			return 3;
		}
		TCHAR buffer[] = _T("TEST TEXT\n");
		if (!WriteFile(hConsole, buffer, 11, NULL, NULL)) {
			error_text_output();
			return 4;
		}	// Output will be on console
	}*/

	return 0;
}