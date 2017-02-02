#pragma once

#include "types.h"

// iNES file format header
struct NesHeader {
	// 0x1a53454e
	uint32_t magicNumber;
	// prg rom size in multiples of 16kb
	u8 prgRomSize;
	// chr rom size in multiples of 8kb
	u8 chrRomSize;
	u8 flags6;
	u8 flags7;
	// prg ram size in multiples of 8kb
	u8 prgRamSize;
	u8 flags9;
	u8 flags10;
	u8 zeros[5];

	u8 mapper();
};

static_assert(sizeof(NesHeader) == 16, "sizeof(NesHeader) must be 16");
