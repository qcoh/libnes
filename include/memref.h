#pragma once

#include "mmu.h"
#include "types.h"

class MemRef {
public:
	MemRef(u16, MMU*);
	~MemRef() = default;

	operator u8() const;
	operator u16() const;

	MemRef& operator=(const u8&);
	MemRef& operator=(const u16&);

private:
	u16 m_addr;
	MMU* m_mmu;
};
