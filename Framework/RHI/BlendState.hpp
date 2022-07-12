#pragma once
#include "Interface/IResource.hpp"

namespace GodEngine {
	class IBlenState : public IRenderResource {
	public:
		virtual  void SetEnable(bool enable) = 0;
	};
}
