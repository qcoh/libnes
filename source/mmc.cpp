#include <bitset>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "mmc.h"
#include "nesheader.h"

std::unique_ptr<MMC> MMC::fromFile(const std::string& path) {
	std::ifstream f{};
	f.exceptions(std::ios::failbit);
	f.open(path, std::ios::binary);

	NesHeader h{};
	f.read(static_cast<char*>(static_cast<void*>(&h)), sizeof(h));

	throw std::runtime_error{"not implemented"};
}
