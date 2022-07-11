#pragma once
#include <complex.h>

#include "Interface/Imodule.hpp"
#include <unordered_map>
#include <memory>

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Mesh.hpp"

namespace GodEngine {
	class GraphicsManager : public ITickableModule {
	public:
		virtual int Initialize() noexcept = 0;
		virtual void Finalize() noexcept = 0;
		
		virtual void Present() noexcept = 0;
		virtual void ClearRenderTarget(float r, float g, float b, float a) noexcept = 0;

		virtual std::shared_ptr<IVertexBuffer> CreateVertexBuffer(void* data, int count, VertexFormat vf) noexcept = 0;
		virtual std::shared_ptr<IIndexBuffer> CreateIndexBuffer(void* data, int count, IndexFormat iformat) noexcept = 0;

		virtual std::shared_ptr<IMesh> CreateRenderMesh() noexcept = 0;
		virtual std::shared_ptr<IMesh> CreateRenderMesh(aiMesh* mesh, const aiScene* world) noexcept = 0;
	};
}
