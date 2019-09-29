#include "stdafx.h"
#include "view.h"

void View::Paint(HWND hDlg, std::string str_to_out, std::string str_to_out_iter, std::string str_for_first, std::string str_for_last, HFONT hFont) {
	PAINTSTRUCT ps;
	HDC hdc;
	hdc = BeginPaint(hDlg, &ps);
	tagRECT r = { 220, 120, 450, 800 };
	SelectObject(hdc, hFont);
	Line(hdc, 340, 20, 340, 260);
	PrintText(hDlg, IDC_STATIC1, str_to_out.c_str());
	PrintText(hDlg, IDC_STATIC4, str_to_out_iter.c_str());
	PrintText(hDlg, IDC_STATIC2, str_for_first.c_str());
	PrintText(hDlg, IDC_STATIC3, str_for_last.c_str());
	EndPaint(hDlg, &ps);
}

void View::MakeDialog(HINSTANCE hInst, HWND hDlg, DialogType type) {
	switch (type)
	{
	case DialogType::About:
		DialogBox(hInst, MAKEINTRESOURCE(IDM_ABOUT), hDlg, DlgAbout);
		break;
	default:
		break;
	}
}

void View::PrintText(HWND hDlg, int ID, const char* outBuff) {
	SetDlgItemText(hDlg, ID, outBuff);
}

void View::Line(HDC hdc, int X0, int Y0, int X, int Y) {
	MoveToEx(hdc, X0, Y0, NULL);
	LineTo(hdc, X, Y);
}
void View::ChangeListBox(HWND hDlg, const char* outBuff, int ID) {
	SendDlgItemMessage(hDlg, ID, LB_INSERTSTRING, -1, (LPARAM)outBuff);
}
void View::DeleteFromList(HWND hDlg, int ID) {
	SendDlgItemMessage(hDlg, ID, LB_DELETESTRING, 0, (LPARAM)NULL);
}

