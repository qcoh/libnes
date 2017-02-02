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

    {0x01, "ORA (n, x)", 2, 6},

    {0x05, "ORA n", 2, 3},

    {0x09, "ORA #n", 2, 2},

    {0x0d, "ORA nn", 3, 4},

    {0x11, "ORA (n), Y", 2, 5},

    {0x15, "ORA n, X", 2, 4},
}};
