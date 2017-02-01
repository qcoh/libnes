#include "testmmu.h"

TestMMU::TestMMU(MemArray& data) : m_data{data} {}

u8 TestMMU::read8(u16 addr) { return m_data[addr]; }

void TestMMU::write8(u16 addr, u8 v) {
	m_data[addr] = v;
	return;
}
