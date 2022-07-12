#pragma once
#include "Interface/IResource.hpp"

namespace GodEngine {
	//渲染用到对应的采样器
	class ISamplerState : public IRenderResource {
	public:
		virtual void SetState() = 0;
	};
}
