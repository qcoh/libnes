#pragma once

#include <array>

#include "types.h"

struct Instruction {
	u8 opcode;
	const char* mnemonic;
	u8 length;
	u8 cycles;
};

constexpr const std::array<Instruction, 256> instructions = {{
    {0x00, "BRK", 2, 7},
}};
