#include <windows.h>
#include <cstdlib>
#include <cstdio>

HWND hEdit1, hEdit2;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch(Message) {

    case WM_CREATE:
    {
        CreateWindow("STATIC", "Please input two numbers",
            WS_VISIBLE | WS_CHILD,
            40, 20, 170, 20,
            hwnd, NULL, NULL, NULL);

        hEdit1 = CreateWindow("EDIT", "",
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            40, 50, 170, 25,
            hwnd, NULL, NULL, NULL);

        hEdit2 = CreateWindow("EDIT", "",
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            40, 80, 170, 25,
            hwnd, NULL, NULL, NULL);

        CreateWindow("BUTTON", "+",
            WS_VISIBLE | WS_CHILD,
            40, 120, 35, 30,
            hwnd, (HMENU)1, NULL, NULL);

        CreateWindow("BUTTON", "-",
            WS_VISIBLE | WS_CHILD,
            85, 120, 35, 30,
            hwnd, (HMENU)2, NULL, NULL);

        CreateWindow("BUTTON", "*",
            WS_VISIBLE | WS_CHILD,
            130, 120, 35, 30,
            hwnd, (HMENU)3, NULL, NULL);

        CreateWindow("BUTTON", "/",
            WS_VISIBLE | WS_CHILD,
            175, 120, 35, 30,
            hwnd, (HMENU)4, NULL, NULL);

        break;
    }

    case WM_COMMAND:
    {
        if (HIWORD(wParam) == BN_CLICKED)
        {
            char num1[50], num2[50];

            GetWindowText(hEdit1, num1, 50);
            GetWindowText(hEdit2, num2, 50);

            double a = atof(num1);
            double b = atof(num2);
            double result = 0;

            switch(LOWORD(wParam))
            {
                case 1: result = a + b; break;
                case 2: result = a - b; break;
                case 3: result = a * b; break;
                case 4:
                    if (b != 0)
                        result = a / b;
                    else {
                        MessageBox(hwnd, "Cannot divide by zero!", "Error", MB_OK);
                        return 0;
                    }
                    break;
            }

            char output[100];
            sprintf(output, "%.6f", result);  // แสดง 6 ตำแหน่ง

            MessageBox(hwnd, output, "Result", MB_OK);
        }
        break;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, Message, wParam, lParam);
    }

    return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {

    WNDCLASSEX wc;
    HWND hwnd;
    MSG msg;

    memset(&wc, 0, sizeof(wc));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(0,180,0));
    wc.lpszClassName = "WindowClass";
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
                   MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        0,
        "WindowClass",
        "My Calculator",
        WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        250,
        200,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
                   MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    while(GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}