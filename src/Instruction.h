#pragma once

/**
 * @file
 *
 * @brief Class definition for Instruction
 *
 * This file contains the class and friend functions definition for Instruction.
 *
 */

#include <list>
#include <map>
#include <string>

#include "Symbole.h"
#include "Line.h"

#include "IR_InstructionType.h"
#include "IR_BasicBlock.h"
#include "IR_Address.h"

namespace Model {
	class Instruction : public Line
	{
		public:
			virtual bool verifyExpressionsTypes();
			virtual void buildIR(IntermediateRepresentation::BasicBlock* firstBB) = 0;
			virtual bool computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>*);
			Instruction(int line);
			virtual ~Instruction();
	};
}
