#pragma once

/**
 * @file
 *
 * @brief Class definition for InstructionBlock
 *
 * This file contains the class and friend functions definition for InstructionBlock.
 *
 */

#include "Instruction.h"

namespace Model {

	class InstructionBlock : public Instruction {
		private:
			std::list<Instruction*>* instructions;
		public:
			bool computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>*);
			bool verifyExpressionsTypes();
			virtual void buildIR(IntermediateRepresentation::BasicBlock* firstBB);

			InstructionBlock(std::list<Instruction*>*,int line);
			virtual ~InstructionBlock();
	};
}
