#include "testcpu.h"

TestCPU::TestCPU(MMU* mmu) : CPU{} { m_mmu = mmu; }

void TestCPU::exec() { CPU::exec(); }

u8& TestCPU::a() { return m_a; }

u8& TestCPU::x() { return m_x; }

u8& TestCPU::y() { return m_y; }

u8& TestCPU::sp() { return m_sp; }

u16& TestCPU::pc() { return m_pc; }

u8& TestCPU::status() { return m_status; }

u8& TestCPU::n() { return m_n; }

u16& TestCPU::nn() { return m_nn; }

u8& TestCPU::op() { return m_op; }

u8& TestCPU::cycles() { return m_cycles; }

BitRef<u8, u8, 0>& TestCPU::carryFlag() { return m_carryFlag; }

BitRef<u8, u8, 1>& TestCPU::zeroFlag() { return m_zeroFlag; }

BitRef<u8, u8, 2>& TestCPU::intEnableFlag() { return m_intEnableFlag; }

BitRef<u8, u8, 3>& TestCPU::decimalFlag() { return m_decimalFlag; }

BitRef<u8, u8, 4>& TestCPU::intFlag() { return m_intFlag; }

BitRef<u8, u8, 6>& TestCPU::overflowFlag() { return m_overflowFlag; }

BitRef<u8, u8, 7>& TestCPU::signFlag() { return m_signFlag; }

u8 TestCPU::indexedIndirect() { return CPU::indexedIndirect(); }

u8 TestCPU::indirectIndexed() { return CPU::indirectIndexed(); }

u8 TestCPU::zeroPage() { return CPU::zeroPage(); }

u8 TestCPU::absolute() { return CPU::absolute(); }

u8 TestCPU::zeroPageIndexed() { return CPU::zeroPageIndexed(); }

u8 TestCPU::absoluteIndexed(u8 offset) { return CPU::absoluteIndexed(offset); }
