#pragma once
#include "Interface/IResource.hpp"

namespace GodEngine {
	class IShader : public IRenderResource {
	public:
		virtual bool InitializeFromFile(const std::string& vsPath, const std::string& psPath) noexcept = 0;
		virtual void Use() noexcept = 0;
		virtual void SetConstantBuffer(const ConstantBuffer& cb) noexcept = 0;
		virtual void SetConstantBufferLight(const ConstantBufferLighting& cb) noexcept = 0;
		virtual void SetConstantBufferAnimation(const ConstantBufferAnimation& cb) noexcept = 0;
	};
}
