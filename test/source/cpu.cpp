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
		WHEN("Calling ORA (n, x)") {
			cpu.a() = 0b10100000;
			cpu.op() = 0x01;
			cpu.x() = 0x20;
			cpu.n() = 0x5;
			data[0x25] = 0x34;
			data[0x26] = 0x12;
			data[0x1234] = 0b01010101;
			cpu.exec();

			THEN(
			    "a == 0b11110101, zeroFlag == false, signFlag == "
			    "true") {
				REQUIRE(cpu.a() == 0b11110101);
				REQUIRE(cpu.zeroFlag() == false);
				REQUIRE(cpu.signFlag() == true);
			}
		}
		WHEN("Calling ORA n (1)") {
			cpu.a() = 0b11000000;
			cpu.n() = 0x13;
			data[0x13] = 0b00110000;
			cpu.op() = 0x5;
			cpu.exec();

			THEN(
			    "a == 0b11110000, zeroFlag == false, signFlag == "
			    "true") {
				REQUIRE(cpu.a() == 0b11110000);
				REQUIRE(cpu.zeroFlag() == false);
				REQUIRE(cpu.signFlag() == true);
			}
		}
		WHEN("Calling ORA #n (1)") {
			cpu.a() = 0b11001100;
			cpu.n() = 0b11111100;
			cpu.op() = 0x09;
			cpu.exec();

			THEN(
			    "a == 0b11111100, zeroFlag == false, signFlag == "
			    "true") {
				REQUIRE(cpu.a() == 0b11111100);
				REQUIRE(cpu.zeroFlag() == false);
				REQUIRE(cpu.signFlag() == true);
			}
		}
		WHEN("Calling ORA #n (2)") {
			cpu.a() = 0b00001100;
			cpu.n() = 0b00000011;
			cpu.op() = 0x09;
			cpu.exec();

			THEN(
			    "a == 0b00001111, zeroFlag == false, signFlag == "
			    "false") {
				REQUIRE(cpu.a() == 0b00001111);
				REQUIRE(cpu.zeroFlag() == false);
				REQUIRE(cpu.signFlag() == false);
			}
		}
		WHEN("Calling ORA #n (3)") {
			cpu.a() = 0;
			cpu.n() = 0;
			cpu.op() = 0x09;
			cpu.exec();

			THEN("a == 0, zeroFlag == true, signFlag == false") {
				REQUIRE(cpu.a() == 0);
				REQUIRE(cpu.zeroFlag() == true);
				REQUIRE(cpu.signFlag() == false);
			}
		}
		WHEN("Calling ORA nn") {
			cpu.a() = 0b00000011;
			cpu.nn() = 0x1234;
			data[0x1234] = 0b00001100;
			cpu.op() = 0xd;
			cpu.exec();

			THEN(
			    "a == 0b00001111, zeroFlag == false, signFlag == "
			    "false") {
				REQUIRE(cpu.a() == 0b00001111);
				REQUIRE(cpu.zeroFlag() == false);
				REQUIRE(cpu.signFlag() == false);
			}
		}
		WHEN("Calling ORA (n), Y (1)") {
			cpu.a() = 0x0f;
			cpu.y() = 0x34;
			cpu.n() = 0x40;
			data[0x40] = 0x00;
			data[0x41] = 0x12;
			data[0x1234] = 0x10;
			cpu.op() = 0x11;
			cpu.exec();

			THEN(
			    "a == 0x1f, zeroFlag == false, signFlag == false, "
			    "cycles == 0") {
				REQUIRE(cpu.a() == 0x1f);
				REQUIRE(cpu.zeroFlag() == false);
				REQUIRE(cpu.signFlag() == false);
				REQUIRE(cpu.cycles() == 0);
			}
		}
		WHEN("Calling ORA (n), Y (2)") {
			cpu.a() = 0xf0;
			cpu.y() = 0x1;
			cpu.n() = 0x60;
			data[0x60] = 0xff;
			data[0x61] = 0x40;
			data[0x4100] = 0x08;
			cpu.op() = 0x11;
			cpu.exec();

			THEN(
			    "a == 0xf8, zeroFlag == false, signFlag == true, "
			    "cycles == 1") {
				REQUIRE(cpu.a() == 0xf8);
				REQUIRE(cpu.zeroFlag() == false);
				REQUIRE(cpu.signFlag() == true);
				REQUIRE(cpu.cycles() == 1);
			}
		}
		WHEN("Calling ORA n, X") {
			cpu.a() = 0xf0;
			cpu.x() = 0x0f;
			cpu.n() = 0xf0;
			data[0xff] = 0x0f;
			cpu.op() = 0x15;
			cpu.exec();

			THEN("a == 0xff, zeroFlag == false, signFlag == true") {
				REQUIRE(cpu.a() == 0xff);
				REQUIRE(cpu.zeroFlag() == false);
				REQUIRE(cpu.signFlag() == true);
			}
		}
		WHEN("Calling ORA nn, Y") {
			cpu.a() = 0x0f;
			cpu.y() = 1;
			cpu.nn() = 0x30ff;
			data[0x3100] = 0xf0;
			cpu.op() = 0x19;
			cpu.exec();

			THEN(
			    "a == 0xff, zeroFlag == false, signFlag == true, "
			    "cycles == 1") {
				REQUIRE(cpu.a() == 0xff);
				REQUIRE(cpu.zeroFlag() == false);
				REQUIRE(cpu.signFlag() == true);
				REQUIRE(cpu.cycles() == 1);
			}
		}
		WHEN("Calling ORA nn, X") {
			cpu.a() = 0xf0;
			cpu.x() = 0x10;
			cpu.nn() = 0x4000;
			data[0x4010] = 0x0f;
			cpu.op() = 0x1d;
			cpu.exec();

			THEN(
			    "a == 0xff, zeroFlag == false, signFlag == true, "
			    "cycles == 0") {
				REQUIRE(cpu.a() == 0xff);
				REQUIRE(cpu.zeroFlag() == false);
				REQUIRE(cpu.signFlag() == true);
				REQUIRE(cpu.cycles() == 0);
			}
		}
		WHEN("Calling AND (n, x)") {
			cpu.a() = 0b10100000;
			cpu.x() = 0xf0;
			cpu.n() = 0x0f;
			data[0xff] = 0x34;
			data[0x00] = 0x12;
			data[0x1234] = 0xff;
			cpu.op() = 0x21;
			cpu.exec();

			THEN(
			    "a == 0b10100000, zeroFlag == false, signFlag == "
			    "true") {
				REQUIRE(cpu.a() == 0b10100000);
				REQUIRE(cpu.zeroFlag() == false);
				REQUIRE(cpu.signFlag() == true);
			}
		}
		WHEN("Calling AND n") {
			cpu.a() = 0b00111100;
			cpu.n() = 0x50;
			data[0x50] = 0x0f;
			cpu.op() = 0x25;
			cpu.exec();

			THEN(
			    "a == 0b00001100, zeroFlag == fasel, signFlag == "
			    "false") {
				REQUIRE(cpu.a() == 0b00001100);
				REQUIRE(cpu.zeroFlag() == false);
				REQUIRE(cpu.signFlag() == false);
			}
		}
		WHEN("Calling AND #n") {
			cpu.a() = 0xff;
			cpu.n() = 0;
			cpu.op() = 0x29;
			cpu.exec();

			THEN("a == 0, zeroFlag == true, signFlag == false") {
				REQUIRE(cpu.a() == 0);
				REQUIRE(cpu.zeroFlag() == true);
				REQUIRE(cpu.signFlag() == false);
			}
		}
		WHEN("Calling AND nn") {
			cpu.a() = 0x0f;
			cpu.nn() = 0x1234;
			data[0x1234] = 0xff;
			cpu.op() = 0x2d;
			cpu.exec();

			THEN(
			    "a == 0x0f, zeroFlag == false, signFlag == false") {
				REQUIRE(cpu.a() == 0x0f);
				REQUIRE(cpu.zeroFlag() == false);
				REQUIRE(cpu.signFlag() == false);
			}
		}
		WHEN("Calling AND (n), Y (1)") {
			cpu.a() = 0xb0;
			cpu.n() = 0x20;
			cpu.y() = 0x20;
			data[0x20] = 0x00;
			data[0x21] = 0x20;
			data[0x2020] = 0xff;
			cpu.op() = 0x31;
			cpu.exec();

			THEN(
			    "a == 0xb0, zeroFlag == false, signFlag == true, "
			    "cycles == 0") {
				REQUIRE(cpu.a() == 0xb0);
				REQUIRE(cpu.zeroFlag() == false);
				REQUIRE(cpu.signFlag() == true);
				REQUIRE(cpu.cycles() == 0);
			}
		}
		WHEN("Calling AND (n), Y (2)") {
			cpu.a() = 0xff;
			cpu.n() = 0xff;
			cpu.y() = 1;
			data[0xff] = 0xff;
			data[0x00] = 0x20;
			data[0x2100] = 0x89;
			cpu.op() = 0x31;
			cpu.exec();

			THEN(
			    "a == 0x89, zeroFlag == false, signFlag == true, "
			    "cycles == 0") {
				REQUIRE(cpu.a() == 0x89);
				REQUIRE(cpu.zeroFlag() == false);
				REQUIRE(cpu.signFlag() == true);
				REQUIRE(cpu.cycles() == 1);
			}
		}
		WHEN("Calling AND n, X") {
			cpu.a() = 0xff;
			cpu.n() = 0xff;
			cpu.x() = 0x1;
			data[0] = 0x0b;
			cpu.op() = 0x35;
			cpu.exec();

			THEN(
			    "a == 0x0b, zeroFlag == false, signFlag == false") {
				REQUIRE(cpu.a() == 0x0b);
				REQUIRE(cpu.zeroFlag() == false);
				REQUIRE(cpu.signFlag() == false);
			}
		}
		WHEN("Calling AND nn, Y") {
			cpu.a() = 0xff;
			cpu.nn() = 0x40ff;
			cpu.y() = 1;
			data[0x4100] = 0x19;
			cpu.op() = 0x39;
			cpu.exec();

			THEN(
			    "a == 0x19, zeroFlag == false, signFlag == false, "
			    "cycles == 1") {
				REQUIRE(cpu.a() == 0x19);
				REQUIRE(cpu.zeroFlag() == false);
				REQUIRE(cpu.signFlag() == false);
				REQUIRE(cpu.cycles() == 1);
			}
		}
		WHEN("Calling AND nn, X") {
			cpu.a() = 0xff;
			cpu.nn() = 0x40ef;
			cpu.x() = 1;
			data[0x40f0] = 0x19;
			cpu.op() = 0x3d;
			cpu.exec();

			THEN(
			    "a == 0x19, zeroFlag == false, signFlag == false, "
			    "cycles == 0") {
				REQUIRE(cpu.a() == 0x19);
				REQUIRE(cpu.zeroFlag() == false);
				REQUIRE(cpu.signFlag() == false);
				REQUIRE(cpu.cycles() == 0);
			}
		}
	}
}

SCENARIO("Test addressing modes", "[CPU]") {
	GIVEN("TestCPU and TestMMU") {
		TestMMU::MemArray data{};
		TestMMU mmu{data};
		TestCPU cpu{&mmu};

		WHEN("Addressing indexed indirectly (1)") {
			cpu.n() = 0xff;
			cpu.x() = 0;
			data[0xff] = 0x34;
			data[0x00] = 0x12;
			data[0x1234] = 0x99;

			THEN("Addressing produces correct value") {
				REQUIRE(cpu.indexedIndirect() == 0x99);
			}
		}
		WHEN("Addressing indexed indirectly (2)") {
			cpu.n() = 0x50;
			cpu.x() = 0x5;
			data[0x55] = 0x34;
			data[0x56] = 0x12;
			data[0x1234] = 0x99;

			THEN("Addressing produces correct value") {
				REQUIRE(cpu.indexedIndirect() == 0x99);
			}
		}
		WHEN("Addressing indirectly indexed (1)") {
			cpu.n() = 0x50;
			data[0x50] = 0x33;
			data[0x51] = 0x12;
			cpu.y() = 0x1;
			data[0x1234] = 0xaa;

			THEN(
			    "Addressing produces correct value, does not cross "
			    "page boundary") {
				REQUIRE(cpu.indirectIndexed() == 0xaa);
				REQUIRE(cpu.cycles() == 0);
			}
		}
		WHEN("Addressing indirectly indexed (2)") {
			cpu.n() = 0xff;
			data[0xff] = 0xff;
			data[0x00] = 0x40;
			cpu.y() = 0x1;
			data[0x4100] = 0xcc;

			THEN(
			    "Addressing produces correct value, crosses page "
			    "boundary") {
				REQUIRE(cpu.indirectIndexed() == 0xcc);
				REQUIRE(cpu.cycles() == 1);
			}
		}
		WHEN("Addressing zero page") {
			cpu.n() = 0x12;
			data[0x12] = 0x25;

			THEN("Addressing produces correct value") {
				REQUIRE(cpu.zeroPage() == 0x25);
			}
		}
		WHEN("Addressing absolute") {
			cpu.nn() = 0x1234;
			data[0x1234] = 0x67;

			THEN("Addressing produces correct value") {
				REQUIRE(cpu.absolute() == 0x67);
			}
		}
		WHEN("Addressing zero page indexed") {
			cpu.n() = 0xff;
			cpu.x() = 0x1;
			data[0] = 0x78;

			THEN("Addressing produces correct value") {
				REQUIRE(cpu.zeroPageIndexed() == 0x78);
			}
		}
		WHEN("Addressing absolute indexed (1)") {
			cpu.nn() = 0x1000;
			cpu.x() = 0x25;
			data[0x1025] = 0x78;

			THEN(
			    "Addressing produces correct value, does not cross "
			    "page boundary") {
				REQUIRE(cpu.absoluteIndexed(cpu.x()) == 0x78);
				REQUIRE(cpu.cycles() == 0);
			}
		}
		WHEN("Addressing absolute indexed (2)") {
			cpu.nn() = 0x10ff;
			cpu.y() = 1;
			data[0x1100] = 0x56;

			THEN(
			    "Addressing produces correct value, does cross "
			    "page boundary") {
				REQUIRE(cpu.absoluteIndexed(cpu.y()) == 0x56);
				REQUIRE(cpu.cycles() == 1);
			}
		}
	}
}
