#pragma once
#include "Interface/IResource.hpp"

namespace GodEngine {
	//���״̬�����Ըı����ػ�ϵ���Ϊ��
	class IBlenState : public IRenderResource {
	public:
		virtual  void SetEnable(bool enable) = 0;
	};
}
