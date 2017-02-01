#pragma once

#include "cpu.h"

class TestCPU : public CPU {
public:
	TestCPU(MMU*);
	virtual ~TestCPU() = default;

	u8& a();
	u8& x();
	u8& y();
	u8& sp();
	u16& pc();
	u8& status();
	u8& n();
	u16& nn();
	u8& op();

	BitRef<u8, u8, 0>& carryFlag();
	BitRef<u8, u8, 1>& zeroFlag();
	BitRef<u8, u8, 2>& intEnableFlag();
	BitRef<u8, u8, 3>& decimalFlag();
	BitRef<u8, u8, 4>& intFlag();
	BitRef<u8, u8, 6>& overflowFlag();
	BitRef<u8, u8, 7>& signFlag();

	void exec();
};
