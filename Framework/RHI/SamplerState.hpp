#pragma once
#include "Interface/IResource.hpp"

namespace GodEngine {
	//��Ⱦ�õ���Ӧ�Ĳ�����
	class ISamplerState : public IRenderResource {
	public:
		virtual void SetState() = 0;
	};
}
