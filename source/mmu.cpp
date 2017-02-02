#include "mmu.h"

u8 MMU::read8(u16 addr) {
	(void)addr;
	(void)m_ram;
	(void)m_zpg;
	(void)m_stack;
	return 0;
}

void MMU::write8(u16 addr, u8 v) {
	(void)addr;
	(void)v;
}

u8 MMU::zpgRead8(u16 addr) { return read8(addr & 0xff); }

u16 MMU::zpgRead16(u16 addr) {
	return static_cast<u16>(zpgRead8(addr) | (zpgRead8(addr + 1) << 8));
}

u16 MMU::read16(u16 addr) {
	return static_cast<u16>(read8(addr) | (read8(addr + 1) << 8));
}

void MMU::write16(u16 addr, u16 v) {
	write8(addr, static_cast<u8>(v));
	write8(addr + 1, static_cast<u8>(v >> 8));
}
