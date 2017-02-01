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

// Force Interrupt
void CPU::BRK() {
	m_intFlag = true;
	m_sp -= 2;
	m_mmu->write16(0x100 + m_sp, m_pc);
	m_pc = m_mmu->read16(0xfffe);
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
