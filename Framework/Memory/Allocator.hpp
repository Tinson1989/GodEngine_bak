#pragma once
#include <cstdint>

//todo �����������ʲô��
#ifndef ALIGN
#define ALIGN(x, a) (((x) + (a - 1)) & ~((a) - 1))
#endif

namespace GodEngine {
	struct BlockHeader {
		BlockHeader* next;
	};

	struct PageHeader {
		PageHeader* next;
		BlockHeader* getBlocks() {
			return reinterpret_cast<BlockHeader*>(this + 1);
		}
	};

	class Allocator {
	public:
		static const uint8_t PATTERN_ALIGN = 0xFC; //252
		static const uint8_t PATTERN_ALLOC = 0xFD; //253
		static const uint8_t PATTERN_FREE  = 0xFE; //254

		Allocator();
		Allocator(size_t dataSize, size_t pageSize, size_t alignment);
		~Allocator();
		void Reset(size_t dataSize, size_t pageSize, size_t alignment);
		void* Allocate();
		void Free(void* p);
		void FreeAll();
	private:
#if defined(_DEBUG)
		void debugFillFreePage(PageHeader* pPage);
		void debugFillFreeBlock(BlockHeader* pBlock);
		void debugFillAllocatedBlock(BlockHeader* pBlock);
#endif
		BlockHeader* calcNextBlock(BlockHeader* pBlock);
		PageHeader*  m_pPageList;
		BlockHeader* m_pFreeList;
		size_t m_szDataSize;
		size_t m_szPageSize;
		size_t m_szAlignmentSize;
		size_t m_szBlockSize;
		size_t m_nBlockPerPage;

		size_t m_nPages;
		size_t m_nBlock;
		size_t m_nFreeBlocks;

		Allocator(const Allocator& clone) = delete;
		Allocator& operator=(const Allocator& rhs) = delete;

	};
}
