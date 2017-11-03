#pragma once

namespace IntermediateRepresentation {

	typedef enum {
		R0 = 0,
		R1 = 1,
		R2 = 2,
		R3 = 3,
		R4 = 4,
		R5 = 5,
		R6 = 6,
		R7 = 7,
		R8 = 8,
		R9 = 9,
		R10 = 10,
		R11 = 11,
		R12 = 12,
		R13 = 13,
		R14 = 14,
		R15 = 15,

		BP = 32,
		SP = 33,
		PC = 34
	} Register;

	typedef enum {
		BYTE = 0,
		WORD = 1,
		DWORD = 2,
		QWORD = 3
	} RegAccessType;

}
