#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "IR_Address.h"
#include "IR_Instruction.h"
#include "IR_InstructionType.h"


namespace IntermediateRepresentation {
	class CFG;

	class BasicBlock {
		private:
			BasicBlock* exitTrue;  /**< pointer to the next basic block, true branch. If nullptr, return from procedure */
			BasicBlock* exitFalse; /**< pointer to the next basic block, false branch. If null_ptr, the basic block ends with an unconditional jump */
			std::string label; /**< label of the BB, also will be the label in the generated code */
			CFG* cfg; /** < the CFG where this block belongs */
			std::vector<IRInstruction*> instrs; /** < the instructions themselves. */

		public:
			void gen_x86asm(std::ostream &o); /**< x86 assembly code generation for this basic block (very simple) */
			void add_IRInstr(InstructionType op, Address op1, Address op2, Address Dest, std::string jmpLabel = "");

			CFG* getCfg();
			std::string getLabel();

			void setExitT(BasicBlock*);
			void setExitF(BasicBlock*);
			BasicBlock* getThen();
			BasicBlock* getElse();

			BasicBlock(CFG* cfg, std::string entry_label);
			~BasicBlock();
		};
}

#include "IR_CFG.h"
