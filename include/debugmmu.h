#pragma once

#include <iostream>
#include <unordered_set>

#include "mmu.h"

class DebugMMU : public MMU {
public:
	DebugMMU(std::unordered_set<u16>&);
	virtual ~DebugMMU() = default;

	virtual void write8(u16, u8) override;

	struct WatchEvent {
		u16 addr;
		u8 oldVal;
		u8 newVal;

		friend std::ostream& operator<<(std::ostream&,
						const WatchEvent&);
	};

private:
	std::unordered_set<u16> m_watchPoints;
};
