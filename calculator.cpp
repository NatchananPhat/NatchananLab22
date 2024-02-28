#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include<iostream>
#include <windows.h>
#include <tchar.h>
#include <string>

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

HWND textfield, button1, button2, button3, button4, textbox1, textbox2;
double textsaved;

TCHAR szClassName[] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain(HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;

    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof (WNDCLASSEX);

    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = CreateSolidBrush(RGB(202, 108, 255));

    if (!RegisterClassEx(&wincl))
        return 0;

    hwnd = CreateWindowEx(
           0,
           szClassName,
           _T("My Calculator"),
           WS_MAXIMIZEBOX | WS_SYSMENU,
           CW_USEDEFAULT, CW_USEDEFAULT,
           250, 200,
           HWND_DESKTOP,
           NULL,
           hThisInstance,
           NULL);

    ShowWindow(hwnd, nCmdShow);

    while (GetMessage(&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    return messages.wParam;
}


LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_CREATE:
            textfield = CreateWindow(_T("STATIC"), _T("  Please input two numbers"),
                                    WS_VISIBLE | WS_CHILD | WS_BORDER,
                                    35, 20, 180, 20, hwnd, NULL, NULL, NULL);
            textbox1 = CreateWindow(_T("EDIT"), _T(""), WS_VISIBLE | WS_CHILD | WS_BORDER,
                                    35, 50, 180, 20, hwnd, NULL, NULL, NULL);
            textbox2 = CreateWindow(_T("EDIT"), _T(""), WS_VISIBLE | WS_CHILD | WS_BORDER,
                                    35, 80, 180, 20, hwnd, NULL, NULL, NULL);
            button1 = CreateWindow(_T("BUTTON"), _T("+"), WS_VISIBLE | WS_CHILD | WS_BORDER,
                                    65, 110, 20, 20, hwnd, (HMENU) 1, NULL, NULL);
            button2 = CreateWindow(_T("BUTTON"), _T("-"), WS_VISIBLE | WS_CHILD | WS_BORDER,
                                    95, 110, 20, 20, hwnd, (HMENU) 2, NULL, NULL);
            button3 = CreateWindow(_T("BUTTON"), _T("*"), WS_VISIBLE | WS_CHILD | WS_BORDER,
                                    125, 110, 20, 20, hwnd, (HMENU) 3, NULL, NULL);
            button4 = CreateWindow(_T("BUTTON"), _T("/"), WS_VISIBLE | WS_CHILD | WS_BORDER,
                                    155, 110, 20, 20, hwnd, (HMENU) 4, NULL, NULL);
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case 1:
                {
                    char buffer1[256], buffer2[256];
                    GetWindowText(textbox1, buffer1, 256);
                    GetWindowText(textbox2, buffer2, 256);
                    double num1 = atof(buffer1);
                    double num2 = atof(buffer2);
                    textsaved = num1 + num2;
                    MessageBox(hwnd, std::to_string(textsaved).c_str(), _T("Result"), MB_OK);
                    break;
                }
                case 2:
                {
                    char buffer1[256], buffer2[256];
                    GetWindowText(textbox1, buffer1, 256);
                    GetWindowText(textbox2, buffer2, 256);
                    double num1 = atof(buffer1);
                    double num2 = atof(buffer2);
                    textsaved = num1 - num2;
                    MessageBox(hwnd, std::to_string(textsaved).c_str(), _T("Result"), MB_OK);
                    break;
                }
                case 3:
                {
                    char buffer1[256], buffer2[256];
                    GetWindowText(textbox1, buffer1, 256);
                    GetWindowText(textbox2, buffer2, 256);
                    double num1 = atof(buffer1);
                    double num2 = atof(buffer2);
                    textsaved = num1 * num2;
                    MessageBox(hwnd, std::to_string(textsaved).c_str(), _T("Result"), MB_OK);
                    break;
                }
                case 4:
                {
                    char buffer1[256], buffer2[256];
                    GetWindowText(textbox1, buffer1, 256);
                    GetWindowText(textbox2, buffer2, 256);
                    double num1 = atof(buffer1);
                    double num2 = atof(buffer2);
                    textsaved = num1 / num2;
                    MessageBox(hwnd, std::to_string(textsaved).c_str(), _T("Result"), MB_OK);
                    break;
                }
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}
