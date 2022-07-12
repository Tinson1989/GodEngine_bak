#pragma once
#include "Interface/IResource.hpp"

namespace GodEngine {
	//混合状态，可以改变像素混合的行为。
	class IBlenState : public IRenderResource {
	public:
		virtual  void SetEnable(bool enable) = 0;
	};
}
