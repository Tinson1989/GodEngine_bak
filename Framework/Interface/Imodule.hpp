#pragma once
namespace GodEngine {
	class IModule {
	public:
		virtual int Initialize() noexcept = 0;
		virtual void Finalize() noexcept = 0;
	};

	class ITickableModule : public IModule {
		virtual void tick() noexcept = 0;
	};
}