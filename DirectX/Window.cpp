#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/*HWND CreateFullscreenWindow(HWND hwnd)
{
  HMONITOR hmon = MonitorFromWindow(hwnd,
    MONITOR_DEFAULTTONEAREST);
  MONITORINFO mi = { sizeof(mi) };
  if (!GetMonitorInfo(hmon, &mi)) return NULL;
  return CreateWindowW(TEXT("static"),
    TEXT("something interesting might go here"),
    WS_POPUP | WS_VISIBLE,
    mi.rcMonitor.left,
    mi.rcMonitor.top,
    mi.rcMonitor.right - mi.rcMonitor.left,
    mi.rcMonitor.bottom - mi.rcMonitor.top,
    hwnd, NULL, g_hinst, 0);
}*/

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ PWSTR pCmdLine, _In_ int nCmdShow)
{
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Window";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        1,                      // Optional window styles.
        CLASS_NAME,             // Window class
        L"",                    // Window text
        WS_OVERLAPPEDWINDOW,    // Window style

        // Size and position
        0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(_In_ HWND hwnd, _In_opt_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);



        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        EndPaint(hwnd, &ps);
    }
    return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}