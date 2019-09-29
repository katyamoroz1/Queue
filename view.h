#pragma once
#include "project.h"
#include "stdafx.h"

extern HINSTANCE hInst;
INT_PTR CALLBACK	DlgMain(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK	DlgAbout(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

enum class DialogType {Set, Get, Del, About };

class View {
public:
	void Paint(HWND hDlg, std::string str_to_out, std::string str_to_out_iter, std::string str_to_first, std::string str_to_last, HFONT hFont);

	void MakeDialog(HINSTANCE hInst, HWND hDlg, DialogType type);

	void PrintText(HWND hDlg, int ID, const char* outBuff);

	void Line(HDC hdc, int X0, int Y0, int X, int Y);

	void ChangeListBox(HWND nDlg, const char* outBuff, int ID);

	void DeleteFromList(HWND hDlg, int ID, int number);
};