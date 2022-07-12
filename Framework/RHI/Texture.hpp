#pragma once
#include "Interface/IResource.hpp"

namespace GodEngine {
	enum TextureType {
		Default = 1,
		Cubemap = 2,
	};
	//��Ⱦ�õ�����ͼ
	class ITexture : public IRenderResource {
	public:
		ITexture(TextureType type) : mType(type){}
		virtual void InitializeDefault(const std::string& filepath) noexcept = 0;
		virtual void InitializeCubemap(const std::string& filepath) noexcept = 0;
	protected:
		TextureType mType;
	};
}
