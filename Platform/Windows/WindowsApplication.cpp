#include "WindowsApplication.hpp"

namespace GodEngine {
	static LRESULT CALLBACK TmpWndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam) {
		switch (uiMsg) {
		case WM_CLOSE:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, uiMsg, wParam, lParam);
		}

		return 0;
	}

	LRESULT CALLBACK WindowsApplication::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
		WindowsApplication* pThis;
		pThis = reinterpret_cast<WindowsApplication*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		switch (message) {
		case WM_CREATE:
			LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
			return 0;
		case WM_LBUTTONDOWN:
			//todo 处理onkeyDown事件
			return 0;
		case WM_LBUTTONUP:
			return 0;
		case WM_RBUTTONDOWN:
			return 0;
		case WM_RBUTTONUP:
			return 0;
		case WM_KEYDOWN:
			return 0;
		case WM_KEYUP:
			return 0;
		case WM_MOUSEMOVE:
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			pThis->Quit();
			return 0;
		}

		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	//初始化
	int WindowsApplication::Initialize() noexcept {
		CHECK_APPLICATION_INIT(Application::Initialize());

		//todo 调试窗口

		CreateMainWindow();
		mUseOpenGL = false;
		if(mUseOpenGL) {
			LoadWGL();
			CreateGLContext();
		}

		return 0;
	}

	void WindowsApplication::Tick() noexcept {
		
	}

	void WindowsApplication::Render() noexcept {
		
	}

	HWND WindowsApplication::GetWindowsHandler() noexcept {
		return mHWND;
	}

	void WindowsApplication::CreateMainWindow() {
		HINSTANCE hInstance = GetModuleHandle(NULL);
		WNDCLASSEX windowClass = { 0 };
		windowClass.cbSize = sizeof(WNDCLASSEX);
		windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		windowClass.lpfnWndProc = WindowProc;
		windowClass.hInstance = hInstance;
		windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		windowClass.lpszClassName = "god";
		RegisterClassEx(&windowClass);

		RECT windowRect = { 0, 0, 960, 480 };
		AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);

		mHWND = CreateWindowEx(
			NULL,
			windowClass.lpszClassName,
			"GodEngine",
			WS_OVERLAPPEDWINDOW,
			100,
			100,
			windowRect.right - windowRect.left,
			windowRect.bottom - windowRect.top,
			nullptr,
			nullptr,
			hInstance,
			this
		);

		ShowWindow(mHWND, 5);
	}

	void WindowsApplication::Finalize() noexcept {
		
	}

	void WindowsApplication::LoadWGL() {
		int result = 0;
		DWORD Style = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
		WNDCLASSEX WndClassEx;
		memset(&WndClassEx, 0, sizeof(WNDCLASSEX));
		HINSTANCE hInstance = GetModuleHandle(NULL);
		WndClassEx.cbSize = sizeof(WNDCLASSEX);
		WndClassEx.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		WndClassEx.lpfnWndProc = TmpWndProc;
		WndClassEx.hInstance = hInstance;
		WndClassEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		WndClassEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		WndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
		WndClassEx.lpszClassName = "InitWindow";
		RegisterClassEx(&WndClassEx);
		HWND TemphWnd = CreateWindowEx(
			WS_EX_APPWINDOW,
			WndClassEx.lpszClassName,
			"InitWindow",
			Style,
			0,
			0,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			NULL,
			NULL,
			hInstance, 
			NULL
		);
		PIXELFORMATDESCRIPTOR pfd;
		memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 24;
		pfd.cRedBits = 8;
		pfd.cGreenBits = 8;
		pfd.cBlueBits = 8;
		pfd.cAlphaBits = 8;
		pfd.cDepthBits = 24;
		pfd.cStencilBits = 8;
		pfd.iLayerType = PFD_MAIN_PLANE;

		HDC TemphDC = GetDC(TemphWnd);
		int nPixelFormat = ChoosePixelFormat(TemphDC, &pfd);
		_ASSERT(nPixelFormat != 0);

		result = SetPixelFormat(TemphDC, nPixelFormat, &pfd);
		_ASSERT(result == 1);

		mRenderContext = wglCreateContext(TemphDC);
		_ASSERT(result == 1);

		result = wglMakeCurrent(TemphDC, mRenderContext);
		_ASSERT(result == 1);

		auto r = gladLoadWGL(TemphDC);
		_ASSERT(r != 0);

		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(mRenderContext);
		ReleaseDC(TemphWnd, TemphDC);
		DestroyWindow(TemphWnd);
	}

	void WindowsApplication::CreateGLContext() {
		int nPixelFormat;
		UINT numFormats;
		PIXELFORMATDESCRIPTOR pfd;
		int result;

		auto mHDC = GetDC(mHWND);
		if(GLAD_WGL_ARB_pixel_format && GLAD_WGL_ARB_multisample && GLAD_WGL_ARB_create_context) {
			const int attributes[] = {
				WGL_DRAW_TO_BITMAP_ARB, GL_TRUE,
				WGL_SUPPORT_GDI_ARB, GL_TRUE,
				WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
				WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
				WGL_COLOR_BITS_ARB, (int)24,
				WGL_RED_BITS_ARB, (int)8,
				WGL_GREEN_BITS_ARB, (int)8,
				WGL_BLUE_BITS_ARB, (int)8,
				WGL_ALPHA_BITS_ARB, (int)8,
				WGL_DEPTH_BITS_ARB, (int)24,
				WGL_STENCIL_BITS_ARB, (int)8,
				WGL_SAMPLE_BUFFERS_ARB, 1,
				WGL_SAMPLES_ARB, 4,
				0
			};

			bool fail = wglChoosePixelFormatARB(mHDC, attributes, nullptr, 1, &nPixelFormat, &numFormats) < 0 || numFormats == 0;
			_ASSERT(!fail);

			result = SetPixelFormat(mHDC, nPixelFormat, &pfd);
			_ASSERT(result == 1);

			const int contextAttributes[] = {
				WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
				WGL_CONTEXT_MINOR_VERSION_ARB, 1,
				WGL_CONTEXT_FLAGS_ARB,
				WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
				WGL_CONTEXT_PROFILE_MASK_ARB,
				WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
				0
			};
			mRenderContext = wglCreateContextAttribsARB(mHDC, 0, contextAttributes);
			_ASSERT(mRenderContext);

			result = wglMakeCurrent(mHDC, mRenderContext);
			_ASSERT(result == 1);
		}else {
			int nPixelFormat = ChoosePixelFormat(mHDC, &pfd);
			_ASSERT(nPixelFormat != 0);

			result = SetPixelFormat(mHDC, nPixelFormat, &pfd);
			_ASSERT(result == 1);

			mRenderContext = wglCreateContext(mHDC);
			_ASSERT(mRenderContext);

			result = wglMakeCurrent(mHDC, mRenderContext);
			_ASSERT(result == 1);
		}
	}








}
