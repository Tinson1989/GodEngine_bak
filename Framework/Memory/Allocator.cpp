#include"Allocator.hpp"
#include <Foundation/Asset.hpp>
#include<stdlib.h>
#include<string.h>

namespace GodEngine {
	Allocator::Allocator() :
		m_pPageList(nullptr), m_pFreeList(nullptr),
		m_szDataSize(0), m_szPageSize(0), m_szAlignmentSize(0),
		m_szBlockSize(0), m_nBlockPerPage(0)
	{
	}

	Allocator::Allocator(size_t dataSize, size_t pageSize, size_t alignment) :
		m_pFreeList(nullptr), m_pPageList(nullptr)
	{
		Reset(dataSize, pageSize, alignment);
	}

	Allocator::~Allocator() {
		FreeAll();
	}

	void Allocator::Reset(size_t dataSize, size_t pageSize, size_t alignment) {
		FreeAll();

		m_szDataSize = dataSize;
		m_szPageSize = pageSize;
		size_t minBlockSize = (sizeof(PageHeader) > m_szDataSize ) ? sizeof(PageHeader) : m_szDataSize;

		GOD_ASSERT(alignment > 0 && ((alignment & (alignment - 1))) == 0);
		m_szBlockSize = ALIGN(minBlockSize, alignment);
		m_szAlignmentSize = m_szBlockSize - minBlockSize;
		m_nBlockPerPage = (m_szPageSize - sizeof(PageHeader)) / m_szBlockSize;
	}

	void* Allocator::Allocate() {
		if (!m_pFreeList) {
			PageHeader* pNewPage = reinterpret_cast<PageHeader*>(new uint8_t[m_szPageSize]);
			pNewPage->next = nullptr;
			++m_nPages;
			m_nBlock += m_nBlockPerPage;
			m_nFreeBlocks += m_nBlockPerPage;
#if defined(_DEBUG)
			debugFillFreePage(pNewPage);
#endif
			if (m_pPageList) {
				pNewPage->next = m_pPageList;
			}
			m_pPageList = pNewPage;
			BlockHeader* pBlock = pNewPage->getBlocks();
			
			for (int i = 0; i < m_nBlockPerPage - 1; i++) {
				pBlock->next = calcNextBlock(pBlock);
				pBlock = pBlock->next;
			}
			pBlock->next = nullptr;
			m_pFreeList = pNewPage->getBlocks();
		}

		BlockHeader* pFreeBlock = m_pFreeList;
		m_pFreeList = m_pFreeList->next;
		--m_nFreeBlocks;

#if defined(_DEBUG)
		debugFillAllocatedBlock(pFreeBlock);
#endif
		return reinterpret_cast<void*>(pFreeBlock);
	}

	void Allocator::Free(void* p) {
		BlockHeader* block = reinterpret_cast<BlockHeader*>(p);
#if defined(_DEBUG)
		debugFillFreeBlock(block);
#endif

		block->next = m_pFreeList;
		m_pFreeList = block;
		++m_nFreeBlocks;
	}

	void Allocator::FreeAll() {
		PageHeader* pPage = m_pPageList;
		while (pPage) {
			PageHeader* p = pPage;
			pPage = pPage->next;
			delete[] reinterpret_cast<uint8_t*>(p);
		}

		m_pPageList = nullptr;
		m_pFreeList = nullptr;

		m_nPages = 0;
		m_nBlock = 0;
		m_nFreeBlocks = 0;
	}

#if defined(_DEBUG)
	void Allocator::debugFillFreePage(PageHeader* pPage){
		BlockHeader* pBlock = pPage->getBlocks();
		for (size_t i = 0; i < m_nBlockPerPage; i++) {
			debugFillFreeBlock(pBlock);
			pBlock = calcNextBlock(pBlock);
		}
	}

	void Allocator::debugFillFreeBlock(BlockHeader* pBlock){
		memset(pBlock, PATTERN_FREE, m_szBlockSize - m_szAlignmentSize);
		memset(reinterpret_cast<uint8_t*>(pBlock) + m_szBlockSize - m_szAlignmentSize, PATTERN_ALIGN, m_szAlignmentSize);
	}

	void Allocator::debugFillAllocatedBlock(BlockHeader* pBlock) {
		memset(pBlock, PATTERN_ALLOC, m_szBlockSize - m_szAlignmentSize);
		memset(reinterpret_cast<uint8_t*>(pBlock) + m_szBlockSize - m_szAlignmentSize, PATTERN_ALIGN, m_szAlignmentSize);
	}
#endif

	BlockHeader* Allocator::calcNextBlock(BlockHeader* pBlock) {
		uint8_t* address = reinterpret_cast<uint8_t*>(pBlock) + m_szBlockSize;
		return reinterpret_cast<BlockHeader*>(address);
	}
}