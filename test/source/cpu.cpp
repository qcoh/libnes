#include "catch.hpp"
#include "testcpu.h"
#include "testmmu.h"

SCENARIO("Test CPU instructions", "[CPU]") {
	GIVEN("TestCPU and TestMMU") {
		TestMMU::MemArray data{};
		TestMMU mmu{data};
		TestCPU cpu{&mmu};

		WHEN("Calling BRK") {
			data[0xfffe] = 0x34;
			data[0xffff] = 0x12;
			cpu.sp() = 0xff;
			cpu.pc() = 0x789a;
			cpu.op() = 0x00;
			cpu.exec();

			THEN("pc == 0x1234, intFlag == true, sp == 0xfd") {
				REQUIRE(cpu.pc() == 0x1234);
				REQUIRE(cpu.intFlag() == true);
				REQUIRE(cpu.sp() == 0xfd);
				REQUIRE(data[0x1fd] == 0x9a);
				REQUIRE(data[0x1fe] == 0x78);
			}
		}
	}
}
