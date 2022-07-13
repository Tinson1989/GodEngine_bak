#pragma once
#include <d3d10.h>

#include "Application/Application.hpp"

namespace GodEngine {
	class WindowsApplication : public Application {
	public:
		WindowsApplication(){}
		virtual int Initialize() noexcept override;
		virtual void Finalize() noexcept override;
		virtual void Tick() noexcept override;
		virtual void Render() noexcept override;

		HWND GetWindowsHandler() noexcept;

	protected:
		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	private:
		void CreateMainWindow();

		void LoadWGL();
		void CreateGLContext();
	private:
		HWND mHWND;
		HGLRC mRenderContext;

		bool mUseOpenGL;
	};
}
