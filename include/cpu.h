#pragma once

#include "bitref.h"
#include "mmu.h"
#include "types.h"

class CPU {
public:
	CPU() = default;
	virtual ~CPU() = default;

	CPU(const CPU&) = delete;
	CPU& operator=(const CPU&) = delete;
	CPU(CPU&&) = delete;
	CPU& operator=(CPU&&) = delete;

	virtual void step();

protected:
	void fetch();
	void exec();

	u8 m_a = 0;
	u8 m_x = 0;
	u8 m_y = 0;
	u8 m_sp = 0;
	u16 m_pc = 0;

	u8 m_status = 0;
	BitRef<u8, u8, 0> m_carryFlag{m_status};
	BitRef<u8, u8, 1> m_zeroFlag{m_status};
	BitRef<u8, u8, 2> m_intEnableFlag{m_status};
	BitRef<u8, u8, 3> m_decimalFlag{m_status};
	BitRef<u8, u8, 4> m_intFlag{m_status};
	BitRef<u8, u8, 6> m_overflowFlag{m_status};
	BitRef<u8, u8, 7> m_signFlag{m_status};

	MMU* m_mmu = nullptr;
	u8 m_cycles = 0;

	u8 m_op = 0;

	u16 m_nn = 0;
	u8& m_n = static_cast<u8*>(static_cast<void*>(&m_nn))[0];

	// addressing modes
	u8 indexedIndirect();
	u8 indirectIndexed();
	u8 zeroPage();
	u8 absolute();
	u8 zeroPageIndexed();
	u8 absoluteIndexed(u8);

private:
	// Instructions

	// Control flow
	void BRK();

	void TAX();
	void TAY();
	void TSX();
	void TXA();
	void TXS();
	void TYA();

	void ORA(u8);
	void AND(u8);

	template <typename T>
	void EOR(const T& source) {
		m_a ^= static_cast<u8>(source);
		m_zeroFlag = (m_a == 0);
		m_signFlag = ((m_a >> 7) != 0);
	}

	template <typename T>
	void ADC(const T& source) {
		u16 temp = static_cast<u16>(m_a + m_carryFlag +
					    static_cast<u8>(source));
		m_carryFlag = (temp > 0xff);
		// http://stackoverflow.com/a/29224684
		// TODO: think about this
		m_overflowFlag = ((~(m_a ^ source) & (m_a ^ temp) & 0x80) != 0);
		m_a = static_cast<u8>(temp);
		m_zeroFlag = (m_a == 0);
		m_signFlag = ((m_a >> 7) != 0);
	}

	template <typename T>
	void SBC(const T& source) {
		ADC(~static_cast<u8>(source));
	}

	template <typename T>
	void CMP(const T& source) {
		u8 temp = m_a;
		SBC(static_cast<u8>(source));
		m_a = temp;
	}

	template <typename T>
	void CPX(const T& source) {
		u8 temp = m_a;
		m_a = m_x;
		SBC(static_cast<u8>(source));
		m_a = temp;
	}

	template <typename T>
	void CPY(const T& source) {
		u8 temp = m_a;
		m_a = m_y;
		SBC(static_cast<u8>(source));
		m_a = temp;
	}

	template <typename T>
	void INC(const T& target) {
		u8 temp = static_cast<u8>(target);
		temp++;
		m_zeroFlag = (temp == 0);
		m_signFlag = ((temp >> 7) != 0);
		target = temp;
	}

	template <typename T>
	void DEC(const T& target) {
		u8 temp = static_cast<u8>(target);
		temp--;
		m_zeroFlag = (temp == 0);
		m_signFlag = ((temp >> 7) != 0);
		target = temp;
	}

	void DEX();
	void DEY();
	void CLC();
	void SEC();
	void CLV();
	void INY();
	void INX();
};
