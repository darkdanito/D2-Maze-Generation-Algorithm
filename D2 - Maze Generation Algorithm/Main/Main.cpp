#include <Windows.h>
#include "Resource.h"
#include "Mazecommon.h"
#include "Maze.h"
#include "IOFile.h"

LPCWSTR g_szClassName = L"Main";									// Window Class stores information about a type of window

//Global Variables
HWND hwnd;
Maze newMaze;
IOFile newFile;
char arrayChecking;
HBITMAP mazeLogo = NULL;

//Function Prototype
void RegisterWindowClass(HINSTANCE hInstance);
void CreateAppWindow(HINSTANCE hInstance);
void init(HWND hwnd);
void FileOpen(HWND hwnd);
void ClearWindow(HWND hwnd);
bool LoadAndBlitBitmap(HBITMAP mazelogo);
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

/*Window Procedure*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)		// WindowProc
{
	int ret;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (Msg)
	{
	case WM_LBUTTONDOWN:														// Handle mouse clicks, we need to add a WM_LBUTTONDOWN handler (or WM_RBUTTONDOWN, WM_MBUTTONDOWN, for right and middle clicks respectively).
	{
		break;
	}
	case WM_COMMAND:
		HBRUSH hbrush;
		RECT recClient;
		recClient = { 0 };
		GetClientRect(hwnd, &recClient);

		hbrush = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
		hdc = GetDC(hwnd);
		FillRect(hdc, &recClient, hbrush);

		switch (LOWORD(wParam))
		{
		case IDM_RECALG:														// Generating the Algorithm for Recursive Back
		{
			arrayChecking = 'r';
			ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DLG1), hwnd, DlgProc);
			if (ret >= 0)
			{
				newMaze.generate((ALGORITHMS_ENUM)ret);
				InvalidateRect(hwnd, NULL, TRUE);								// Paint by sending message WM_PAINT
				UpdateWindow(hwnd);
			}
			return DefWindowProc(hwnd, Msg, wParam, lParam);					// If Break from Dialog it will return back to window
			break;
		}
		case IDM_HUNTALG:														// Generating the Algorithm for Hunt and Kill
		{
			arrayChecking = 'h';
			ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DLG1), hwnd, DlgProc);
			if (ret >= 0)
			{
				newMaze.generate((ALGORITHMS_ENUM)1);
				InvalidateRect(hwnd, NULL, TRUE);								// Paint by sending message WM_PAINT
				UpdateWindow(hwnd);
			}
			return DefWindowProc(hwnd, Msg, wParam, lParam); // If Break from Dialog it will return back to window
			break;
		}
		case IDM_RECBONUSALG:													// Generating the Algorithm for Recursive with Loop [Hybrid]
		{
			arrayChecking = 'r';
			ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DLG1), hwnd, DlgProc);
			if (ret >= 0)
			{
				newMaze.generate((ALGORITHMS_ENUM)2);
				InvalidateRect(hwnd, NULL, TRUE);								// Paint by sending message WM_PAINT
				UpdateWindow(hwnd);
			}
			return DefWindowProc(hwnd, Msg, wParam, lParam); // If Break from Dialog it will return back to window
			break;
		}
		case IDM_OPEN:															// Open File to Read Maze.txt
		{
			int result;
			result = newFile.FileOpen(hwnd);
			switch (result)
			{
				case IDYES:
				{
					arrayChecking = 'r';
					newMaze.createMazeSize(newFile.getWidth(), newFile.getHeight());
					newMaze.generateByFile(hwnd, newFile.getFileContent());
					InvalidateRect(hwnd, NULL, TRUE); // Paint by sending message WM_PAINT
					UpdateWindow(hwnd);
					break;
				}
				case IDNO:
				{
					// Do something
					break;
				}
			}
			break;
		}
		case IDM_EXIT:
		{
			DestroyWindow(hwnd);
			break;
		}
		case IDM_ABOUT:
		{
			MessageBox
				(
				NULL,
				L"OOP Maze Generator Studio 2015\n"
				L"Version 2.00\n"
				L"Copyright © OOP",
				L"About OOP Maze Generator Studio",
				MB_OK
				);
			return 0;
			break;
		}
		}
	case WM_CREATE:
	{
		mazeLogo = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDA_LOGO));
		if (mazeLogo == NULL)
			MessageBox(hwnd, L"Could not load IDB_BALL!", L"Error", MB_OK | MB_ICONEXCLAMATION);
	}
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		if (arrayChecking == 'r')	// Render the Maze for Recursive, Recursive and Loop and Open File
		{
			InvalidateRect(hwnd, NULL, true);
			UpdateWindow(hwnd);
			newMaze.renderMaze(hwnd);
		}
		else if(arrayChecking == 'h')	// Render the Maze for Hunt and Kill
		{
			InvalidateRect(hwnd, NULL, true);
			UpdateWindow(hwnd);
			newMaze.renderHKMaze(hwnd);
		}
		else							// Other conditions
		{
			InvalidateRect(hwnd, NULL, true);
			UpdateWindow(hwnd);

			LoadAndBlitBitmap( mazeLogo);
		}
		return DefWindowProc(hwnd, Msg, wParam, lParam);
		break;
	case WM_ERASEBKGND:
	{
		return 1;
		break;
	}
	case WM_CLOSE:
	{
		DestroyWindow(hwnd);
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	default:
	{
		return DefWindowProc(hwnd, Msg, wParam, lParam);
	}
	}
	return 0;
}

/*Dialog Procedure*/
BOOL CALLBACK DlgProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)		// DialogProc
{

	switch (Msg)
	{
	case WM_INITDIALOG:
	{
		if (arrayChecking == 'r')
		{
			SetDlgItemText(hwnd, IDC_STC4, L"Recursive BackTrack");
		}
		else if (arrayChecking == 'h')
		{
			SetDlgItemText(hwnd, IDC_STC4, L"Hunt-and-Kill");
		}
		else
		{
			SetDlgItemText(hwnd, IDC_STC4, L"Recursive Loop");
		}
		break;
	}
	case WM_CLOSE:
	{
		EndDialog(hwnd, -1);
		return TRUE;
		break;
	} case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDD_OK:
		{
			size_t width = GetDlgItemInt(hwnd, IDC_WIDTH, NULL, FALSE);		// Take in User Width Input
			size_t height = GetDlgItemInt(hwnd, IDC_HEIGHT, NULL, FALSE);	// Take in User Height Input

			int alg = SendDlgItemMessage(hwnd, IDM_EXIT, CB_GETCURSEL, 0, 0);

			if (width < MIN_WIDTH || height < MIN_HEIGHT || width > MAX_WIDTH || height > MAX_HEIGHT)
			{
				MessageBox(hwnd, L"Invalid width and height. \nMin Maze Size is 4 x 4. \nMax  Maze Size is 100 x 100. ", L"Alert", MB_ICONWARNING);
			}
			else
			{
				newMaze.createMazeSize(width, height); // Create Maze Size based on user input
				EndDialog(hwnd, alg);
			}
			return TRUE;
			break;
		}
		case IDD_CANCEL:
		{
			EndDialog(hwnd, -1);
			return TRUE;
			break;
		} default:
		{
			return FALSE;
		}
		}
		break;
	} default:
	{
		return FALSE;
	}
	}
}

/*Main Program*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) // WinMain handle Unicode arguments to your program.
{
	MSG msg;
	RegisterWindowClass(hInstance);												// Register Window Class
	CreateAppWindow(hInstance);													// Create AppWindow
	init(hwnd);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

/*Register Window Class*/
void RegisterWindowClass(HINSTANCE hInstance)
{
	WNDCLASSEX wc;																// Variable above stores the name of our window class
	ZeroMemory(&wc, sizeof(wc));

	wc.style = 0;																// CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpszMenuName = MAKEINTRESOURCE(IDC_MAKEWINDOW);							// L"IDC_MAKEWINDOW"; //lpszMenuName can't be NULL in 64-bit
	//When compiling for 64 - bit Windows, RegisterClass() will crash if lpszMenuName is NULL.Fortunately, using a WNDCLASSEX and calling RegisterClassEx() works with NULL.
	//The resource name of the class menu, as the name appears in the resource file.
	wc.lpszClassName = g_szClassName;											// If lpszClassName is a string, it specifies the window class name.
	wc.lpfnWndProc = WndProc;													// A pointer to the window procedure.
	wc.hInstance = hInstance;													// A handle to the instance that contains the window procedure for the class
	wc.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDA_ICON));
	wc.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDA_ICON), IMAGE_ICON, 20, 20, 0);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.cbWndExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;

	if (!RegisterClassEx(&wc))
	{
		LPCWSTR Error01 = L"Could not Register Class1";
		LPCWSTR Error01_Caption = L"Error";
		MessageBox(NULL, Error01, Error01_Caption, MB_OK | MB_ICONERROR);
	}
}

/*Create Application Window*/
void CreateAppWindow(HINSTANCE hInstance)
{
	LPCWSTR WindowTitle = L"OOP Maze Generator Studio";
	hwnd = CreateWindowEx
		(
		WS_EX_CLIENTEDGE, g_szClassName, WindowTitle, 
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | 
		WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 
		1024, 768, NULL, NULL, hInstance, NULL
		);

	if (hwnd == NULL)
	{
		LPCWSTR Error02 = L"Could not Register Class2";
		LPCWSTR Error02_Caption = L"Error";
		MessageBox(NULL, Error02, Error02_Caption, MB_OK | MB_ICONERROR);
	}
}

/*Center the Window*/
void init(HWND hwnd) 
{
	HDC hdc;
	RECT area;
	// Center Window
	hdc = GetDC(GetDesktopWindow());
	GetWindowRect(hwnd, &area);
	int x = GetDeviceCaps(hdc, HORZRES) / 2 - (area.right - area.left) / 2;
	int y = GetDeviceCaps(hdc, VERTRES) / 2 - (area.bottom - area.top) / 2;
	ReleaseDC(GetDesktopWindow(), hdc);
	MoveWindow(hwnd, x, y, (area.right - area.left), (area.bottom - area.top), true);

	hdc = GetDC(hwnd);
	ReleaseDC(hwnd, hdc);
}

/*Clear the Window*/
void ClearWindow(HWND hwnd)
{
	HDC hdc;
	HBRUSH hbrush;
	RECT recClient;
	recClient = { 0 };
	GetClientRect(hwnd, &recClient);

	hbrush = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
	hdc = GetDC(hwnd);
	FillRect(hdc, &recClient, hbrush);
}

/*Load Window Logo*/
bool LoadAndBlitBitmap(HBITMAP mazeLogo)
{
	BITMAP bm;
	PAINTSTRUCT ps;

	HDC hdc = BeginPaint(hwnd, &ps);

	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, mazeLogo);

	GetObject(mazeLogo, sizeof(bm), &bm);

	BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);

	SelectObject(hdcMem, hbmOld);
	DeleteDC(hdcMem);

	return true;
}