#include <stdexcept>

#include "cpu.h"
#include "instruction.h"

void CPU::fetch() {
	m_op = m_mmu->read8(m_pc);
	m_nn = m_mmu->read16(m_pc + 1);
}

void CPU::exec() {
	switch (m_op) {
	case 0x00:  // BRK
		BRK();
		break;
	case 0x01:  // ORA (n, x)
		ORA(indexedIndirect());
		break;
	case 0x05:  // ORA n
		ORA(zeroPage());
		break;
	case 0x09:  // ORA #n
		ORA(m_n);
		break;
	case 0x0d:  // ORA nn
		ORA(absolute());
		break;
	case 0x11:  // ORA (n), Y
		ORA(indirectIndexed());
		break;
	case 0x15:  // ORA n, X
		ORA(zeroPageIndexed());
		break;
	case 0x19:  // ORA nn, Y
		ORA(absoluteIndexed(m_y));
		break;
	case 0x1d:  // ORA nn, X
		ORA(absoluteIndexed(m_x));
		break;
	default:
		throw std::runtime_error{"Unknown instruction"};
	}
}

void CPU::step() {
	(void)m_a;
	(void)m_x;
	(void)m_y;
	(void)m_sp;
	(void)m_pc;
	(void)m_status;

	(void)m_carryFlag;
	(void)m_zeroFlag;
	(void)m_intEnableFlag;
	(void)m_decimalFlag;
	(void)m_intFlag;
	(void)m_overflowFlag;
	(void)m_signFlag;

	fetch();
	exec();
}

u8 CPU::indexedIndirect() {
	u8 addr = static_cast<u8>(m_n + m_x);
	return m_mmu->read8(m_mmu->zpgRead16(addr));
}

u8 CPU::indirectIndexed() {
	u16 addr = m_mmu->zpgRead16(m_n);
	if ((addr + m_y) >> 8 != (addr >> 8)) {
		m_cycles++;
	}
	return m_mmu->read8(static_cast<u16>(addr + m_y));
}

u8 CPU::zeroPage() { return m_mmu->zpgRead8(m_n); }

u8 CPU::absolute() { return m_mmu->read8(m_nn); }

u8 CPU::zeroPageIndexed() { return m_mmu->zpgRead8(m_n + m_x); }

u8 CPU::absoluteIndexed(u8 offset) {
	if ((m_nn + offset) >> 8 != m_nn >> 8) {
		m_cycles++;
	}
	return m_mmu->read8(static_cast<u16>(m_nn + offset));
}

// Force Interrupt
void CPU::BRK() {
	m_intFlag = true;
	m_sp -= 2;
	m_mmu->write16(0x100 + m_sp, m_pc);
	m_pc = m_mmu->read16(0xfffe);
}

// OR A
void CPU::ORA(u8 v) {
	m_a |= v;
	m_zeroFlag = (m_a == 0);
	m_signFlag = ((m_a >> 7) != 0);
}

// Transfer A to X
void CPU::TAX() { m_x = m_a; }

// Transfer A to Y
void CPU::TAY() { m_y = m_a; }

// Transfer SP to X
void CPU::TSX() { m_x = m_sp; }

// Transfer X to A
void CPU::TXA() { m_a = m_x; }

// Transfer X to SP
void CPU::TXS() { m_sp = m_x; }

// Transfer Y to A
void CPU::TYA() { m_a = m_y; }
