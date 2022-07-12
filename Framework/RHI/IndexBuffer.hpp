#pragma once
#include "Interface/IResource.hpp"

namespace GodEngine {
	enum IndexFormat {
		IF_None = 0,
		IF_UINT16,
		IF_UINT32,
	};
	//渲染模型的顶点索引缓冲。主要的作用是复用顶点数据，减少带宽消耗。
	class IIndexBuffer : public IRenderResource {
	public:
		virtual void Initialize(void* data, unsigned int count, IndexFormat iformat) noexcept = 0;
		IIndexBuffer() : mIndexCount(0), mIndexFormat(IF_None){}
		unsigned int GetIndexCount() { return mIndexCount; }

	protected:
		unsigned int mIndexCount;//索引总数
		IndexFormat mIndexFormat;//索引的格式
	};
}