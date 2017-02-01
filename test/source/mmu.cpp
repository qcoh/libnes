#include "catch.hpp"

#include "testmmu.h"

SCENARIO("Verify correct endianess", "[MMU]") {
	GIVEN("TestMMU instance with dummy data") {
		TestMMU::MemArray data = {{0x34, 0x12}};
		TestMMU mmu{data};

		WHEN("Reading from TestMMU") {
			THEN("(0) has the expected value") {
				REQUIRE(mmu.read16(0) == 0x1234);
			}
		}
		WHEN("Writing to TestMMU") {
			mmu.write16(0x100, 0x789a);

			THEN("(0x100) == 0x9a, (0x101) == 0x78") {
				REQUIRE(data[0x100] == 0x9a);
				REQUIRE(data[0x101] == 0x78);
			}
		}
		WHEN("Reading result of a write") {
			mmu.write16(0x1234, 0xabcd);
			u16 result = mmu.read16(0x1234);

			THEN("result == 0xabcd") { REQUIRE(result == 0xabcd); }
		}
	}
}
