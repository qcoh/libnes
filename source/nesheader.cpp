#include "nesheader.h"

u8 NesHeader::mapper() {
	return static_cast<u8>((flags6 >> 4) | (flags7 & 0xf0));
}
