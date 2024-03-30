#pragma once
#include <windows.h>
#include <bcrypt.h>
#include "skStr.h"

namespace offset {
	bool detectv2802 = false;
	bool detectv2944 = false;
	bool detectv3095 = false;

	namespace b2802 {
		DWORD ReplayInterface_ptr = 0x20304C8;
		DWORD world_ptr = 0x26684D8;
		DWORD viewport_ptr = 0x20D8C90;
	}

	namespace b2699 {
		DWORD ReplayInterface_ptr = 0x20304C8;
		DWORD world_ptr = 0x26684D8;
		DWORD viewport_ptr = 0x20D8C90;
	}

	namespace b2612 {
		DWORD ReplayInterface_ptr = 0x1F77EF0;
		DWORD world_ptr = 0x2567DB0;
		DWORD viewport_ptr = 0x1FD8570;
	}

	namespace b2545 {
		DWORD ReplayInterface_ptr = 0x1F2E7A8;
		DWORD world_ptr = 0x25667E8;
		DWORD viewport_ptr = 0x1FD6F70;
	}

	namespace b2372 {
		DWORD ReplayInterface_ptr = 0x1F05208;
		DWORD world_ptr = 0x252DCD8;
		DWORD viewport_ptr = 0x1F9E9F0;
	}

	namespace b2189 {
		DWORD ReplayInterface_ptr = 0x1EE18A8;
		DWORD world_ptr = 0x24E6D90;
		DWORD viewport_ptr = 0x1F888C0;
	}

	namespace b2060 {
		DWORD ReplayInterface_ptr = 0x1EC3828;
		DWORD world_ptr = 0x24C8858;
		DWORD viewport_ptr = 0x1F6A7E0;
	}

	namespace b1604 {
		DWORD ReplayInterface_ptr = 0x1EFD4C8;
		DWORD world_ptr = 0x247F840;
		DWORD viewport_ptr = 0x2087780;
	}

	namespace b2944 {
		DWORD ReplayInterface_ptr = 0x1F42068;
		DWORD world_ptr = 0x257BEA0;
		DWORD viewport_ptr = 0x1FEAAC0;
	}

	namespace b3095 {
		DWORD ReplayInterface_ptr = 0x1F42068;
		DWORD world_ptr = 0x257BEA0;
		DWORD viewport_ptr = 0x1FEAAC0;
	}

}
