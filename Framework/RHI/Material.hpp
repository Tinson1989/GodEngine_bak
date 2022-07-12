#pragma once
#include <unordered_map>

#include "BlendState.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "DepthStencilState.hpp"
#include "Interface/IResource.hpp"

namespace GodEngine {
	class IMaterial : public IRenderResource {
	public:
		virtual void Apply(ConstantBuffer cb) noexcept = 0;
		virtual void ApplyLight(ConstantBufferLighting cb) noexcept = 0;
		virtual void ApplyAnimation(ConstantBufferAnimation cb) noexcept = 0;

	protected:
		std::string mName;
		std::shared_ptr<IShader> mShader;
		std::shared_ptr <IDepthStencilState> mDepthStencilState;
		std::shared_ptr < IBlenState> mBlendState;
		std::unordered_map<std::string, Vector4f> mParamters;
		//Texture
		std::unordered_map<std::string, std::shared_ptr<ITexture>> mTExtures;
		//SampleState
		
	};
}
