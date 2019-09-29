#pragma once
#include <memory>
#include "view.h"
#include "Model.h"
#include "Iterator.h"
#include "Visitor.h"

template<typename T>
class Controller {
public:

	explicit Controller(Model<T>* queue, Model<T>* heap) : view_(), queue_(queue), heap_(heap){}

	int Start(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
		UNREFERENCED_PARAMETER(hPrevInstance);
		UNREFERENCED_PARAMETER(lpCmdLine);

		if (!InitInstance(hInstance, nCmdShow))
		{
			return FALSE;
		}

		HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY5));

		MSG msg;
		while (GetMessage(&msg, nullptr, 0, 0))
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		return (int)msg.wParam;
	}
	char buff[100] = "";
	std::string element;
	VisitorSum<std::string> visitor;
	void Main(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam, HFONT hFont) {
		std::string str;
		QueueIterator<std::string> it((Queue<std::string>&)*queue_);
		
		switch (message)
		{
		case WM_COMMAND:
			switch (LOWORD(wParam)) {
			case IDC_BUTTON_1:
				Add(hDlg, message, wParam, lParam, IDC_LIST1, queue_);
				break;
			case IDC_BUTTON_3: 
				Del(hDlg, message, wParam, lParam, IDC_LIST1, queue_);
				break;
			case IDC_BUTTON_4:  
				Size(hDlg, message, wParam, lParam);
				break;
			case IDC_BUTTON1:
				Add(hDlg, message, wParam, lParam, IDC_LIST2, heap_);
				break;
			case IDC_BUTTON2:
				Del(hDlg, message, wParam, lParam, IDC_LIST2, heap_);
				break;
			case IDC_BUTTON3:
				for (it.First(); !it.IsDone(); it.Next()) {
					Element<std::string> element(it.CurrentItem());
					element.accept(visitor);
				}
				SendDlgItemMessage(hDlg, IDC_LIST3, LB_DELETESTRING, 0, (LPARAM)element.c_str());
				SendDlgItemMessage(hDlg, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)std::to_string(queue_->Size() == 0 ? 0 : visitor.result() / (double)queue_->Size()).c_str());
				break;
			case WM_DESTROY:
				DeleteObject(hFont);
				PostQuitMessage(0);
				break;
			}
			break;
		case WM_PAINT:
			view_.Paint(hDlg, queue_->str_to_out, queue_->str_to_out_iter, queue_->str_for_first, queue_->str_for_last, hFont);
			break;
		}
	}

	void Add(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam, int ID, Model<T>* model_) {
		GetDlgItemTextA(hDlg, IDC_EDIT1, buff, 100);
		SetDlgItemTextA(hDlg, IDC_EDIT1, "");
		if (std::string(buff) != "") {
			model_->Add(std::string(buff));
			view_.ChangeListBox(hDlg, buff, ID);
		}
	}

	void Del(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam, int ID, Model<T>* model_) {
		if (model_->Size() != 0) {
		    T& element =  model_->Accept(visitor);
			//auto index = SendDlgItemMessage(hDlg, ID, LB_FINDSTRINGEXACT, -1, (LPARAM)element.c_str());
			int index = model_->Find(element);
			view_.DeleteFromList(hDlg, ID, index);
		}
	}

	void Size(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
		element = std::to_string(queue_->Size());
		SendDlgItemMessage(hDlg, IDC_LIST3, LB_DELETESTRING, 0, (LPARAM)element.c_str());
		SendDlgItemMessage(hDlg, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)element.c_str());
	}

	const static HFONT hFont;

private:
	BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
		hInst = hInstance;

		HWND hWnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, DlgMain);

		if (!hWnd)
		{
			return FALSE;
		}

		ShowWindow(hWnd, nCmdShow);
		UpdateWindow(hWnd);

		return TRUE;
	}

	HWND hMainDlg;
	View view_;
	Model<T>* queue_;
	Model<T>* heap_;

};

template<typename T>
const HFONT Controller<T>::hFont = CreateFont(20, 0, 0, 0,
	FW_DONTCARE,
	FALSE, FALSE, FALSE, // курсив подчеркивание зачеркивание (прост поставить true)
	DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
	CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
	VARIABLE_PITCH, TEXT("Areal")); // в ковычках можно указать какой-нибудь шрифт
