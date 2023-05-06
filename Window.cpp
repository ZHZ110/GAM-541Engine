#include "Window.h"
#include <Windows.h>
#include "GameEngine.h"
#include "Message.h"

// The main window handle; this is used to identify a
// created window.
HWND ghMainWnd = 0;
extern GameEngine* ENGINE;

// The window procedure handles events our window receives.
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int x, y;
	// Handle some specific messages. Note that if we handle a
	// message, we should return 0.
	switch (msg)
	{
	case WM_KEYDOWN:
	{
		// In the case the escape key was pressed, then destroy the main application window.
		if (wParam == VK_ESCAPE) {
			int msgboxID = MessageBox(0, "Do you wish to save your progress? ", "Quit", MB_YESNOCANCEL);
			switch (msgboxID) {
			case IDCANCEL:
				break;
			case IDYES:
				DestroyWindow(ghMainWnd);
				break;
			case IDNO:
				DestroyWindow(ghMainWnd);
				break;
			}
			return 0;
		}
		KeyboardPress keyboard_down = KeyboardPress();
		keyboard_down.key = static_cast<unsigned char>(wParam);
		ENGINE->BroadcastMessage(&keyboard_down);
		return 0;
	}
	case WM_KEYUP: 
	{
		KeyboardUp keyboard_up = KeyboardUp();
		keyboard_up.key = static_cast<unsigned char>(wParam);
		ENGINE->BroadcastMessage(&keyboard_up);
		return 0;
	}
	/*case WM_CHAR:
		ch = static_cast<unsigned char>(wParam);
		if (keyboard.IsCharAutoRepeat()) {
			keyboard.OnChar(ch);
		}
		else {
			const bool wasPressed = lParam & 0x4000000;
			if (!wasPressed) {
				keyboard.OnChar(ch);
			}
		}*/
	case WM_MOUSEMOVE:
	{
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		MouseMove mouse_move = MouseMove(x, y); // can I just have it on the stack
		//ENGINE->BroadcastMessage(&mouse_move);
		return 0;
	}
	case WM_LBUTTONDOWN:
	{
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		MouseLeftClick mouse_left_click = MouseLeftClick(x, y);
		ENGINE->BroadcastMessage(&mouse_left_click);
		return 0;
	}
	case WM_RBUTTONDOWN:
	{
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		MouseRightClick mouse_right_click = MouseRightClick(x, y);
		ENGINE->BroadcastMessage(&mouse_right_click);
		return 0;
	}
	case WM_LBUTTONUP:
	{
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		MouseLeftUp mouse_left_up = MouseLeftUp(x, y);
		ENGINE->BroadcastMessage(&mouse_left_up);
		return 0;
	}
	case WM_RBUTTONUP:
	{
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		MouseRightUp mouse_right_up = MouseRightUp(x, y);
		ENGINE->BroadcastMessage(&mouse_right_up);
		return 0;
	}
	case WM_MOUSEWHEEL:
	{
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		MouseWheel mouse_wheel = MouseWheel(x, y);
		if (GET_WHEEL_DELTA_WPARAM(wParam) > 0) {
			mouse_wheel.UpOrDown = 0; // up
		}
		else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0) {
			mouse_wheel.UpOrDown = 1; // down
		}
		ENGINE->BroadcastMessage(&mouse_wheel);
		return 0;
	}
	// In the case of a destroy message, then send a
	// quit message, which will terminate the message loop.
	case WM_DESTROY : case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

// Wraps the code necessary to initialize a Windows
// application. Function returns true if initialization
// was successful, otherwise it returns false.
Window::Window(HINSTANCE instanceHandle, int show, float width, float height) 
	: show(show), width(width), height(height) {
	// Define window style
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = instanceHandle;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = "DX11-engine";

	if (!RegisterClass(&wc))
	{
		MessageBox(0, "RegisterClass FAILED", 0, 0);
	}

	// Create the window
	ghMainWnd = CreateWindow("DX11-engine", "My Engine Interface", WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
		100, 100, width, height, NULL, NULL, NULL, NULL);
	if (ghMainWnd == 0)
	{
		MessageBox(0, "CreateWindow FAILED", 0, 0);
	}
	else {
		m_handle = ghMainWnd;
		ShowWindow(ghMainWnd, show);
		UpdateWindow(ghMainWnd);
	}
}

void Window::Initialize() {
}

void Window::Update(float dt) {
	MSG m_msg = { 0 };
	//WPARAM wParam;
	if (PeekMessage(&m_msg, 0, 0, 0, PM_REMOVE)) {
		TranslateMessage(&m_msg);
		DispatchMessage(&m_msg);
		switch (m_msg.message)
		{
		case WM_QUIT: {
			MessageQuit msg;
			ENGINE->BroadcastMessage(&msg);
			break;
		}	
		default:
			break;
		}	
	}
	else {
	}
}

void Window::ShutDown() {
}


void Window::getMessage(const Message* msg) {
	//printf("sendMessage in windows\n");
}

HWND Window::getHandle() {
	return m_handle;
}