#include "stdafx.h"
#include "project.h"
#include <ctime>
#include <iterator>
#include <vector>
#include "controller.h"
#include "Model.h"

using std::vector;
using std::wstring;
using std::to_wstring;

#define MAX_LOADSTRING 100

HINSTANCE hInst;
INT_PTR CALLBACK	DlgMain(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

Queue<std::string> v;
Heap<std::string> h;
Controller<std::string> controller(&v, &h);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	return controller.Start(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}

INT_PTR CALLBACK DlgMain(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	
		return (INT_PTR)TRUE;
	case WM_COMMAND:
	case WM_PAINT:
		controller.Main(hDlg, message, wParam, lParam, Controller<std::string>::hFont);
		break;
	}
	return (INT_PTR)FALSE;
}


INT_PTR CALLBACK DlgAbout(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		break;
	}
	return (INT_PTR)FALSE;
}