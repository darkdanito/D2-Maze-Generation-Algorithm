#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <vector>
#include <Windows.h>

using namespace std;

#ifndef IO_FILE_H
#define IO_FILE_H

class IOFile
{
	private:
		size_t  height;
		size_t  width;
		vector<string> fileContent;

	public:																		// Functions Constructors - for own class usage
		IOFile();
		size_t getHeight() { return height; };
		size_t getWidth() { return width; };
		vector<string> getFileContent() { return fileContent; };

		void IOFile::init();													// Functions Constructors
		int IOFile::FileOpen(HWND hwnd);
		BOOL IOFile::FileRead(HWND hwnd, LPCTSTR lpstrFile);
};
#endif