#include<windows.h>
#include<commdlg.h>
#include<shlobj.h>
#include<bits/stdc++.h>
using namespace std;


// 全局变量
HINSTANCE hInst;
HWND hEdit;

// 声明回调函数
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// WinMain入口函数
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow){
    WNDCLASSEXW wcex;
    HWND hWnd;
    MSG msg;

    hInst = hInstance;

    wcex.cbSize = sizeof(WNDCLASSEXW);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"SampleWindowClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    RegisterClassExW(&wcex);
    hWnd = CreateWindowExW(0, L"SampleWindowClass", L"Updata", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

// 回调函数定义
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CREATE:
            hEdit = CreateWindowW(L"EDIT", L"\u9009\u62e9\u0020\u0043\u006c\u0061\u0073\u0073\u0020\u0057\u0069\u0064\u0067\u0065\u0074\u0073\u0020\u6587\u4ef6\u5939\u4f4d\u7f6e",
                                 WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                                 10, 10, 300, 25, hWnd, NULL, hInst, NULL);
            CreateWindowW(L"BUTTON", L"\u9009\u62e9\u6587\u4ef6\u5939",
                         WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                         320, 10, 100, 25, hWnd, (HMENU)1, hInst, NULL);
            break;
        case WM_COMMAND:
            if (LOWORD(wParam) == 1) {
			    BROWSEINFOW bi = { 0 };
			    bi.lpszTitle = L"\u9009\u62e9\u4e00\u4e2a\u6587\u4ef6\u5939";
			    LPITEMIDLIST pidl = SHBrowseForFolderW(&bi);
			
			    if (pidl != 0) {
			        WCHAR path[MAX_PATH];
			        if (SHGetPathFromIDListW(pidl, path)) {
			            SetWindowTextW(hEdit, path);
			        }
			        CoTaskMemFree(pidl);
			    }
			}
			break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

