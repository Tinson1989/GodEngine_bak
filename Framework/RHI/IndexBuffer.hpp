#pragma once
#include "Interface/IResource.hpp"

namespace GodEngine {
	enum IndexFormat {
		IF_None = 0,
		IF_UINT16,
		IF_UINT32,
	};

	class IIndexBuffer : public IRenderResource {
	public:
		virtual void Initialize(void* data, unsigned int count, IndexFormat iformat) noexcept = 0;
		IIndexBuffer() : mIndexCount(0), mIndexFormat(IF_None){}
		unsigned int GetIndexCount() { return mIndexCount; }

	protected:
		unsigned int mIndexCount;//��������
		IndexFormat mIndexFormat;//�����ĸ�ʽ
	};
}