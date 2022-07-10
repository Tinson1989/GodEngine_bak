#pragma once
#include "Interface/IResource.hpp"

namespace GodEngine {
	//todo 这里需要了解一下这几个的意思是啥
	enum VertexFormat {
		VF_None = 0,
		VF_P3F,
		vF_T2F,
		VF_N3F,
		VF_C4B,
		VF_BONE_IDX_4I,
		VF_BONE_WEIGHT_4F,
	};

	class IVertexBuffer : public IRenderResource {
	public:
		virtual void Initailize(void* data, unsigned int count, VertexFormat vf) noexcept = 0;

		IVertexBuffer() : mVertexCount(0), mVertexFormat(VF_None){}

		unsigned int GetVertexSize(VertexFormat vf) {
			if(vf == VF_P3F || vf == VF_N3F) {
				return sizeof(float) * 3;
			}else if(vf == VertexFormat::VF_C4B) {
				return 4;
			}else if(vf == vF_T2F) {
				return sizeof(float) * 2;
			}else if(vf == VF_BONE_IDX_4I) {
				return sizeof(int) * 4;
			}else if(vf == VF_BONE_WEIGHT_4F) {
				return sizeof(float) * 4;
			}else {
				return 0;
			}
		}

		unsigned int GetVertexCount() {
			return mVertexCount;
		}

	public:
		unsigned int mVertexCount; //顶点数量
		VertexFormat mVertexFormat;//顶点格式
	};
}
