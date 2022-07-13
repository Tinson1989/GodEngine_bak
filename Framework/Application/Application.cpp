#include "Application.hpp"

namespace GodEngine {
	int Application::Initialize() noexcept {
		mQuit = false;
		return 0;
	}

	void Application::Tick() noexcept {
		
	}

	void Application::Render() noexcept {
		
	}

	void Application::Run() noexcept {
		while(!IsQuit()) {
			Tick();
		}
	}

	void Application::Finalize() noexcept {
		
	}

	bool Application::IsQuit() noexcept {
		return mQuit;
	}

	void Application::Quit() noexcept {
		mQuit = true;
	}







}
