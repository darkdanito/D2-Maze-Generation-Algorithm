#include "IOFile.h"
#include <Windows.h>

IOFile::IOFile()																// Constructor initialization
{
	init();
}

void IOFile::init()																// Implementation functions for IOFile.cpp
{
	height = 0;
	width = 0;
}

int IOFile::FileOpen(HWND hwnd)													// File Open										
{

	/*Create a Data Structure on the Memory and pass the pointer as argument to OPENFILENAME FUNCTION.
	Return it normally fills up the OPENFILENAME Data Structure and so LpszFilename contain the path.
	*/
	OPENFILENAME ofn;															// Common dialog box structure
	char szFile[260];															// Memory Buffer to contain the File Name
	HANDLE hf;																	// File handle

	ZeroMemory(&ofn, sizeof(ofn));												// Initialize OPENFILENAME
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = (LPWSTR)szFile;
	ofn.lpstrFile[0] = '\0';  // Set lpstrFile[0] to '\0' so that GetOpenFileName does not use the contents of szFile to initialize itself
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = L"Text Files (*.txt)\0*.txt\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_ENABLEHOOK | OFN_EXPLORER;
	ofn.lpstrDefExt = L"txt";

	if (GetOpenFileName(&ofn) == TRUE)											// Display the Open dialog box
		if (FileRead(hwnd, ofn.lpstrFile))
		{
			const int result = MessageBox(hwnd, L"Generate Maze from File?", L"File loaded successful", MB_YESNO);
			return result;
		}
}

BOOL IOFile::FileRead(HWND hwnd, LPCTSTR lpstrFile)								// File Read
{
	HANDLE hf;
	BOOL bSuccess = FALSE;
	string line;
	ifstream infile;
	vector<string> filecontent;

	size_t width = 0;
	size_t height = 0;

	infile.open(lpstrFile);														// Read from file line by line, set width and height
	while (!infile.eof())														// To get you all the lines
	{
		getline(infile, line);													// Saves the line in STRING.
		filecontent.insert(filecontent.end(), line);							// Append into the vector
		width = line.length();
		height++;

		this->height = height;
		this->width = width;
		bSuccess = TRUE;
	}
	this->fileContent = filecontent;											// Store File Content
	infile.close();
	return bSuccess;
}