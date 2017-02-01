#include "memref.h"

MemRef::MemRef(u16 addr, MMU* mmu) : m_addr{addr}, m_mmu{mmu} {}

MemRef::operator u8() const { return m_mmu->read8(m_addr); }

MemRef::operator u16() const { return m_mmu->read16(m_addr); }

MemRef& MemRef::operator=(const u8& rhs) {
	m_mmu->write8(m_addr, rhs);
	return *this;
}

MemRef& MemRef::operator=(const u16& rhs) {
	m_mmu->write16(m_addr, rhs);
	return *this;
}
