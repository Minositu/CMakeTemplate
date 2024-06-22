#ifdef PLATFORM_WIN32
#include <windows.h>
#include <string>

HINSTANCE hInstance;
HWND hwnd;
bool shouldClose = false;

LRESULT windowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void createWindow(std::string windowName, int posX = 0, int posY = 0, int width = 100, int height = 100)
{
    hInstance = GetModuleHandle(NULL);
    STARTUPINFO si;
    GetStartupInfo(&si);

    // Must be unique
    const char* winClassName = "CMakeProjectWindow";

    // Win32 class structure
    WNDCLASSEX wc;

    wc.lpszClassName = winClassName;
    wc.lpfnWndProc = windowProcedure;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1); // (HBRUSH) CreateSolidBrush(RGB(10, 20, 30));
    wc.lpszMenuName = NULL;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window registration failed!!!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return;
    }

    hwnd = CreateWindowA(wc.lpszClassName, windowName.c_str(), WS_OVERLAPPEDWINDOW, posX, posY, width, height, nullptr, nullptr, hInstance, nullptr);
    ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
}

bool processMessages()
{
    while (!shouldClose)
    {
        MSG message;
        while (PeekMessageA(&message, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessageA(&message);
        }
    }
    return false;
}

void shutdownWindow()
{
    return;
}

LRESULT windowProcedure (
	 HWND   hwnd    // Window Handle (Window object)
	,UINT   msg     // Window Message  
	,WPARAM wParam  // Additional message information
	,LPARAM lParam  // Additional message information
	){

	// Process messages 
	switch(msg)
	{
	case WM_CREATE:
		break;
    case WM_CLOSE:		
		DestroyWindow(hwnd);
        shouldClose = true;
		break;
    case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_MOVE:
		break; 
	case WM_PAINT:
	{
		// GDI - Graphics Devices Interface Here
		//--------------------------------------------
		PAINTSTRUCT ps;
		HDC hdc;
		// std::cerr << " [INFO] Windown painting" << std::endl;
		hdc = BeginPaint(hwnd, &ps);
		std::string text = "Hello CMake!";		
		TextOutA(hdc, 0, 0, text.c_str(), text.size());
		EndPaint(hwnd, &ps);		
	}
	break;
    default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
    }

	return 0;
}

#endif