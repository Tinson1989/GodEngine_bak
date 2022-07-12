#pragma once
#include "Interface/IResource.hpp"

namespace GodEngine {
	class ISamplerState : public IRenderResource {
	public:
		virtual void SetState() = 0;
	};
}
