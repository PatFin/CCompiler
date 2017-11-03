#include "IR_Address.h"

namespace IntermediateRepresentation {

	/// @todo Implement function
	int IRregToIndex(Register reg, RegAccessType t) {
		int at = static_cast<int>(t);
		int index = static_cast<int>(reg);
		return (index << 2) | (at & 3);
	}

	std::string regIndexToASM(int index, Assembler::ASMDialect dialect) {
		std::string rslt;
		switch (dialect) {
		case Assembler::X86:
			rslt = regIndexTox86ASM(index);
			break;
		}
		return rslt;
	}

	std::string IRaddressToASM(Address a, Assembler::ASMDialect dialect)
	{
		std::string rslt;
		switch (dialect) {
		case Assembler::X86:
			rslt = IRaddressTox86ASM(a);
			break;
		}
		return rslt;
	}

	std::string IRaddressTox86ASM(Address addr) {
		std::string asm_addr;
		if (addr.type == REGISTER_DIRECT && addr.addr < 0) {
			return "ERR";
		}
		switch (addr.type) {
		case REGISTER_DIRECT:
			asm_addr = regIndexTox86ASM(addr.addr);
			break;
		case MEMORY_DIRECT:
			asm_addr = std::to_string(addr.addr);
			break;
		case REGISTER_INDIRECT:
			asm_addr = "(" + regIndexTox86ASM(addr.addr) + ")";
			break;
		case REGISTER_INDIRECT_OFFSET:
			asm_addr = "-" + std::to_string(addr.offset) + "(" + regIndexTox86ASM(addr.addr) + ")";
			break;
		case REGISTER_INDIRECT_SCALE_1:
			asm_addr = "(" + regIndexTox86ASM(addr.addr) + "," + regIndexTox86ASM(addr.offset) + ",1)";
			break;
		case REGISTER_INDIRECT_SCALE_2:
			asm_addr = "(" + regIndexTox86ASM(addr.addr) + "," + regIndexTox86ASM(addr.offset) + ",2)";
			break;
		case REGISTER_INDIRECT_SCALE_4:
			asm_addr = "(" + regIndexTox86ASM(addr.addr) + "," + regIndexTox86ASM(addr.offset) + ",4)";
			break;
		case REGISTER_INDIRECT_SCALE_8:
			asm_addr = "(" + regIndexTox86ASM(addr.addr) + "," + regIndexTox86ASM(addr.offset) + ",8)";
			break;
		case CONSTANT:
		default:
			asm_addr = "$" + std::to_string(addr.addr);
			break;
		case NULL_ADDR:
			asm_addr = "$0";
			break;
		}
		return asm_addr;
	}

	/// @todo Implement function
	std::string regIndexTox86ASM(int index) {
		std::string rslt;
		switch(index >> 2) {
		case 0:
			switch (index & 3) {
			case 0:
				rslt = "%al";
				break;
			case 1:
				rslt = "%ax";
				break;
			case 2:
				rslt = "%eax";
				break;
			case 3:
				rslt = "%rax";
				break;
			}
			break;
		case 1:
			switch (index & 3) {
			case 0:
				rslt = "%bl";
				break;
			case 1:
				rslt = "%bx";
				break;
			case 2:
				rslt = "%ebx";
				break;
			case 3:
				rslt = "%rbx";
				break;
			}
			break;
		case 2:
			switch (index & 3) {
			case 0:
				rslt = "%cl";
				break;
			case 1:
				rslt = "%cx";
				break;
			case 2:
				rslt = "%ecx";
				break;
			case 3:
				rslt = "%rcx";
				break;
			}
			break;
		case 3:
			switch (index & 3) {
			case 0:
				rslt = "%dl";
				break;
			case 1:
				rslt = "%dx";
				break;
			case 2:
				rslt = "%edx";
				break;
			case 3:
				rslt = "%rdx";
				break;
			}
			break;
		case 4:
			switch (index & 3) {
			case 0:
				rslt = "%dil";
				break;
			case 1:
				rslt = "%di";
				break;
			case 2:
				rslt = "%edi";
				break;
			case 3:
				rslt = "%rdi";
				break;
			}
			break;
		case 5:
			switch (index & 3) {
			case 0:
				rslt = "%sil";
				break;
			case 1:
				rslt = "%si";
				break;
			case 2:
				rslt = "%esi";
				break;
			case 3:
				rslt = "%rsi";
				break;
			}
			break;
		case 6:
			rslt = "ERR";
			break;
		case 7:
			rslt = "ERR";
			break;
		case 8:
			switch (index & 3) {
			case 0:
				rslt = "%r8b";
				break;
			case 1:
				rslt = "%r8w";
				break;
			case 2:
				rslt = "%r8d";
				break;
			case 3:
				rslt = "%r8";
				break;
			}
			break;
		case 9:
			switch (index & 3) {
			case 0:
				rslt = "%r9b";
				break;
			case 1:
				rslt = "%r9w";
				break;
			case 2:
				rslt = "%r9d";
				break;
			case 3:
				rslt = "%r9";
				break;
			}
			break;
		case 10:
			switch (index & 3) {
			case 0:
				rslt = "%r10b";
				break;
			case 1:
				rslt = "%r10w";
				break;
			case 2:
				rslt = "%r10d";
				break;
			case 3:
				rslt = "%r10";
				break;
			}
			break;
		case 11:
			switch (index & 3) {
			case 0:
				rslt = "%r11b";
				break;
			case 1:
				rslt = "%r11w";
				break;
			case 2:
				rslt = "%r11d";
				break;
			case 3:
				rslt = "%r11";
				break;
			}
			break;
		case 12:
			switch (index & 3) {
			case 0:
				rslt = "%r12b";
				break;
			case 1:
				rslt = "%r12w";
				break;
			case 2:
				rslt = "%r12d";
				break;
			case 3:
				rslt = "%r12";
				break;
			}
			break;
		case 13:
			switch (index & 3) {
			case 0:
				rslt = "%r13b";
				break;
			case 1:
				rslt = "%r13w";
				break;
			case 2:
				rslt = "%r13d";
				break;
			case 3:
				rslt = "%r13";
				break;
			}
			break;
		case 14:
			switch (index & 3) {
			case 0:
				rslt = "%r14b";
				break;
			case 1:
				rslt = "%r14w";
				break;
			case 2:
				rslt = "%r14d";
				break;
			case 3:
				rslt = "%r14";
				break;
			}
			break;
		case 15:
			switch (index & 3) {
			case 0:
				rslt = "%r15b";
				break;
			case 1:
				rslt = "%r15w";
				break;
			case 2:
				rslt = "%r15d";
				break;
			case 3:
				rslt = "%r15";
				break;
			}
			break;
		case 32:
			switch (index & 3) {
			case 0:
				rslt = "%bpl";
				break;
			case 1:
				rslt = "%bp";
				break;
			case 2:
				rslt = "%ebp";
				break;
			case 3:
				rslt = "%rbp";
				break;
			}
			break;
		case 33:
			switch (index & 3) {
			case 0:
				rslt = "%spl";
				break;
			case 1:
				rslt = "%sp";
				break;
			case 2:
				rslt = "%esp";
				break;
			case 3:
				rslt = "%rsp";
				break;
			}
			break;
		case 34:
			switch (index & 3) {
			case 0:
				rslt = "%ipl";
				break;
			case 1:
				rslt = "%ip";
				break;
			case 2:
				rslt = "%eip";
				break;
			case 3:
				rslt = "%rip";
				break;
			}
			break;
		}
		return rslt;
	}
}
