// clang -l user32.lib helloengine_win.c
// include the basic windows header file
#include <windows.h>
#include <windowsx.h>
#include <tchar.h>

// 因为用到了gdi32.lib clang会找不着依赖。建议在vscode里使用
// cl user32.lib gdi32.lib heeloengine_win.c 来编译
// 毕竟windown平台不是我们的重点，目标只是了解，使用OPENGL跨平台方案才是我们最终的目标
// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    // the handle for the window, filled by a function
    HWND hWind;
    // this struct holds information for the window class
    WNDCLASSEX wc;

    // clear out the window class for use
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    // fill in the struct with the needed information
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = _T("WindowClass1");

    // register the window class
    RegisterClassEx(&wc);

    // create the window and use the result as the handle
    hWind = CreateWindowEx(0, _T("WindowClass1"), _T("Hello, Engine!"), WS_OVERLAPPEDWINDOW, 300, 300, 500, 400, NULL, NULL, hInstance, NULL);

    // display the window on the screen
    ShowWindow(hWind, nCmdShow);

    // this struct holds Windows event messages
    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0))
    {
        // translate keystroke messages into the right format
        TranslateMessage(&msg);

        // send the message to the WindowProc function
        DispatchMessage(&msg);
    }

    // return this part of the WM_QUIT messages to windows
    return msg.wParam;
}

// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // sort through and find what code to run for the message given
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        RECT rec = {20, 20, 60, 80};
        HBRUSH brush = (HBRUSH)GetStockObject(BLACK_BRUSH);

        FillRect(hdc, &rec, brush);
        EndPaint(hWnd, &ps);
    }
    break;
    // this message is read when the window is closed
    case WM_DESTROY:
    {
        // close the application entirely
        PostQuitMessage(0);
        return 0;
    }
    break;

    default:
        break;
    }

    // Handle any message the switch statement didn't
    return DefWindowProc(hWnd, message, wParam, lParam);
}