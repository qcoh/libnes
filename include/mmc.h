#pragma once

#include <memory>
#include <string>

#include "types.h"

class MMC {
public:
	MMC() = default;
	virtual ~MMC() = default;

	MMC(const MMC&) = delete;
	MMC& operator=(const MMC&) = delete;
	MMC(MMC&&) = delete;
	MMC& operator=(MMC&&) = delete;

	virtual u8 read8(u16) = 0;

	static std::unique_ptr<MMC> fromFile(const std::string&);
};
