#pragma once

#include "mmu.h"

class TestMMU : public MMU {
public:
	using MemArray = std::array<u8, 0x10000>;
	TestMMU(MemArray&);
	virtual ~TestMMU() = default;

	virtual u8 read8(u16) override;
	virtual void write8(u16, u8) override;

private:
	MemArray& m_data;
};
