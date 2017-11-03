#pragma once

#include <iostream>
#include <string>


#include "IR_Address.h"
#include "IR_InstructionType.h"

namespace IntermediateRepresentation {
	class BasicBlock;
	
	class IRInstruction {
		private:
			BasicBlock* bb;
			InstructionType type;
			Address op1;
			Address op2;
			Address dest;
			std::string oJmpLabel;
		public:
			void gen_x86asm(std::ostream &o);
			void setBB(BasicBlock* bb);
			BasicBlock* getBB() const;
			InstructionType getType();
			IRInstruction(InstructionType type, Address op1, Address op2, Address dest, std::string label);
			virtual ~IRInstruction();
	};
}
#include "IR_BasicBlock.h"