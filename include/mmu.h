#pragma once

#include <array>

#include "types.h"

class MMU {
public:
	MMU() = default;
	virtual ~MMU() = default;

	virtual u8 read8(u16);
	virtual void write8(u16, u8);

	u16 read16(u16);
	void write16(u16, u16);

private:
	// 0x0000 - 0x00ff: Zero Page
	std::array<u8, 0x100> m_zpg = {{0}};
	// 0x0100 - 0x01ff: Stack memory
	std::array<u8, 0x100> m_stack = {{0}};
	// 0x0200 - 0x07ff: RAM
	std::array<u8, 0x600> m_ram = {{0}};
	// 0x0800 - 0x1fff: 3xMirror
	// 0x2000 - 0x2007: IO registers
	// 0x2008 - 0x3fff: ?xMirror
	// 0x4000 - 0x401f: IO registers
	// 0x4020 - 0x5fff: Expansion ROM
	// 0x6000 - 0x7fff: SRAM
	// 0x8000 - 0xffff: ROM
};
