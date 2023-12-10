#include <iostream>
#include <windows.h>
#include <commctrl.h>	// Here are defined all controls
#include <windowsx.h>	// Here some macros to simplify operations, for example, of writing in textbox ('x' stands for 'extended')

HWND hwndWNDMain;

// These are handles for widgets (names are arbitrary)
HWND hwndTXT_input;
HWND hwndTXT_output;
HWND hwndBTN[4][4];		// This is a matrix of handle (for buttons this case)

// This is a matrix of string that contains symbols to be displayed on top of buttons
LPCWSTR symbols[4][4] = {
	{L"1",L"2",L"3",L"+"},
	{L"4",L"5",L"6",L"-"},
	{L"7",L"8",L"9",L"*"},
	{L"",L"0",L"=",L"/"}
};

LRESULT CALLBACK WndMainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CREATE:
		// Here I have to put all operations that I want to execute when the window is opening for the first time (so here I have to create standard widgets for my window)
		std::cout << "WM_CREATE!\n";

		// Here I assign to this handle a textbox widget
		hwndTXT_input = CreateWindow(
			WC_EDIT,								// This is the standard class name for a textbox widget. Other standard widget class name are documented on: https://learn.microsoft.com/it-it/training/?source=learn
			L"",									// Here I put nothing because I do not want to display nothing default in the textbox
			WS_CHILD | WS_VISIBLE | ES_RIGHT,		// These are styles specific for a widget. Documentation is on: https://learn.microsoft.com/it-it/training/?source=learn
			15,										// This is the origin x coord for the widget
			10,										// This is the origin y coord for the widget
			270,									// Height of the widget
			25,										// Width of the widget
			hWnd,									// This is the parent window (passed as parameter to WndMainProc)
			nullptr,								// Menu handle
			nullptr,								// This parameter has to be set to null because it is a widget
			nullptr									// ???
		);

		// Another textbox widget
		hwndTXT_output = CreateWindow(
			WC_EDIT,
			L"",
			WS_CHILD | WS_VISIBLE | ES_RIGHT,
			15,
			55,
			270,
			25,
			hWnd,
			nullptr,
			nullptr,
			nullptr
		);

		// Classic double-for for scroll instance of matrix
		for (int i = 0, id = 0; i < 4; i++) {		// id is an unambiguos identifier for every single button
			for (int j = 0; j < 4; j++) {
				// Button widgets
				hwndBTN[i][j] = CreateWindow(
					WC_BUTTON,									// This the standard class name for a button widget
					symbols[i][j],								// Here the text that we want to show into buttons
					WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
					15 + (j * 70),
					130 + (i * 70),
					60,
					60,
					hWnd,
					(HMENU)id,									// For WC_BUTTON widgets this parameter (his type is: HMENU) is used for identify the button (ignore the warning: conversion from 'int' to 'HMENU' of greater size) 
					nullptr,
					nullptr
				);
				id++;
			}
		}

		break;
	case WM_COMMAND:
		switch (HIWORD(wParam)) {		// HIWORD (high word) is a function that allows to get wParam first 16 bits (see "Vital parts of a window" for the complete explanation)
		case BN_CLICKED:
			switch (LOWORD(wParam)) {		// LOWORD (low word) do the same thing of HIWORD, but for 16 bits after. In this case these bits are the ids that I passed as HMENU parameter creating buttons
			// Here a case for every single id (maybe can I use a more intelligent and compact system?)
			case 0:
				WCHAR buffer[1000];		// Buffer to store the text which will be read from textbox (this way the text written before will be not lost). This is an advanced technique
				Edit_GetText(			// This function gets some text from a textbox
					hwndTXT_input,		// Handle of textbox from I want to read
					buffer,				// Buffer to store text read from textbox
					1000				// Buffer dimension
				);
				
				wcscat_s(buffer, L"1");		// Concatenating wstrings
				
				Edit_SetText(			// This function writes some text into a textbox
					hwndTXT_input,		// Handle of textbox where I want to write
					buffer				// Text to write
				);
				break;
			case 1:
				Edit_SetText(hwndTXT_input, L"2");
				break;
			case 2:
				Edit_SetText(hwndTXT_input, L"3");
				break;
			case 3:
				Edit_SetText(hwndTXT_input, L"+");
				break;
			case 4:
				Edit_SetText(hwndTXT_input, L"4");
				break;
			case 5:
				Edit_SetText(hwndTXT_input, L"5");
				break;
			case 6:
				Edit_SetText(hwndTXT_input, L"6");
				break;
			case 7:
				Edit_SetText(hwndTXT_input, L"-");
				break;
			case 8:
				Edit_SetText(hwndTXT_input, L"7");
				break;
			case 9:
				Edit_SetText(hwndTXT_input, L"8");
				break;
			case 10:
				Edit_SetText(hwndTXT_input, L"9");
				break;
			case 11:
				Edit_SetText(hwndTXT_input, L"*");
				break;
			case 12:
				break;
			case 13:
				Edit_SetText(hwndTXT_input, L"0");
				break;
			case 14:
				Edit_SetText(hwndTXT_input, L"=");
				break;
			case 15:
				Edit_SetText(hwndTXT_input, L"/");
				break;
			}
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
}

INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lCmdLine, _In_ int nCmdShow) {
	WNDCLASSEX wc;
	MSG msg;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.hInstance = hInstance;
	wc.cbWndExtra = 0;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hIcon = nullptr;
	wc.hIconSm = nullptr;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = L"wndMainClass";
	wc.lpfnWndProc = WndMainProc;

	if (!RegisterClassEx(&wc)) {
		MessageBox(nullptr, L"Error during the registration of window class", L"ERROR", MB_OK | MB_ICONERROR);

		return -1;
	}

	hwndWNDMain = CreateWindow(
		L"wndMainClass",
		L"WinMain",
		WS_BORDER | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		315,
		450,
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);

	if (!hwndWNDMain) {
		MessageBox(nullptr, L"Error creating window", L"ERROR", MB_OK | MB_ICONERROR);

		return -2;
	}

	ShowWindow(hwndWNDMain, SW_SHOWNORMAL);

	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}