#include "debugmmu.h"

DebugMMU::DebugMMU(std::unordered_set<u16>& watchPoints)
    : m_watchPoints{watchPoints} {}

void DebugMMU::write8(u16 addr, u8 v) {
	if (m_watchPoints.find(addr) != m_watchPoints.end()) {
		u8 old = read8(addr);
		throw WatchEvent{addr, old, v};
	}
	MMU::write8(addr, v);
}

std::ostream& operator<<(std::ostream& os, const DebugMMU::WatchEvent& we) {
	os << "WatchEvent: Address == 0x" << std::hex << +we.addr
	   << ", Old Value: 0x" << std::hex << +we.oldVal << ", New Value: 0x"
	   << std::hex << +we.newVal;
	return os;
}
