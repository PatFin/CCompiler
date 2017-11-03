#pragma once

/**
 * @file
 *
 * @brief Class definition for ControlInstruction
 *
 * This file contains the class and friend functions definition for ControlInstruction.
 *
 */

#include "Instruction.h"
#include "IR_Address.h"
#include "IR_BasicBlock.h"

namespace Model {
	class ControlInstruction : public Instruction {
	protected:
		Instruction* instruction;
	public:
		virtual bool verifyExpressionsTypes();
		ControlInstruction(Instruction * instr, int line);
		virtual void buildIR(IntermediateRepresentation::BasicBlock *firstBB) = 0;

		virtual bool computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>*);
		virtual ~ControlInstruction();
	};
}
