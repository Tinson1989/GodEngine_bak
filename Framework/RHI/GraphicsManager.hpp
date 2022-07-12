#pragma once
#include <complex.h>

#include "Interface/Imodule.hpp"
#include <unordered_map>
#include <memory>

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Mesh.hpp"
#include "SamplerState.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "assimp/scene.h"

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
		virtual std::shared_ptr<IMesh> CreateRenderMeshDebug(void* data, int count, VertexFormat vf) noexcept = 0;
		virtual std::shared_ptr<IMesh> CreateRenderMeshUI() noexcept = 0;

		virtual std::shared_ptr<ITexture> CreateTexture2D(const std::string& path) noexcept = 0;
		virtual std::shared_ptr<ITexture> CreateTexture2D(int width, int height, unsigned char* data) noexcept = 0;
		virtual std::shared_ptr<ITexture> CreateTextureCubemap(const std::string& path) noexcept = 0;
		virtual std::shared_ptr<ISamplerState> CreateSamplerState() noexcept = 0;

		virtual void LoadShaders() noexcept = 0;
		virtual void UseShaders(std::shared_ptr<IShader>) noexcept = 0;
		virtual std::shared_ptr<IShader> GetShader(const std::string& shaderName) noexcept = 0;

		virtual void Draw(unsigned int vcount, unsigned int star) noexcept = 0;
		virtual void DrawIndexed(unsigned int icount, unsigned int start, int baseLoc) noexcept = 0;

	protected:
		std::unordered_map<std::string, std::shared_ptr<IShader>> mShaders;
		std::unordered_map<std::string, std::shared_ptr<ITexture>> mTextures;

	};
}
