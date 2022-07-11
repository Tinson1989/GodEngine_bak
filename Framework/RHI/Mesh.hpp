#pragma once
#include "VertexBuffer.hpp"
#include "assimp/mesh.h"
#include "Interface/IResource.hpp"

namespace GodEngine {
	//����lod
	enum TerrainLod {
		Low,
		Middle,
		High
	};

	//��������
	enum MeshType {
		MESH_TYPE_MODEL = 1,
		MESH_TYPE_SKYBOX,
		MESH_TYPE_UI,
		MESH_TYPE_TERRAIN,
	};

	//ͼԪ����
	enum PrimitiveType {
		PT_POINT = 1,
		PT_LINE,
		PT_TRIANGLE,
	};

	class IMesh : public IRenderResource {
	public:
		virtual void Initialize(aiMesh* mesh) noexcept = 0;
		virtual void Initialize(void* data, int count, VertexFormat vf) noexcept = 0;
		virtual void InitializeUI() noexcept = 0;
		virtual void InitializeTerrain() noexcept = 0;

		virtual void Render(Entity* self) noexcept = 0;
	};
}
