#pragma once

/**
 * @file
 *
 * @brief Class definition for DeclarationInstruction
 *
 * This file contains the class and friend functions definition for DeclarationInstruction.
 *
 */

#include <string>
#include <list>

#include "Instruction.h"
#include "Declaration.h"
#include "Types.h"
#include "IR_Address.h"
#include "IR_BasicBlock.h"

namespace Model {
	class DeclarationInstruction : public Instruction {
	private:
		Types * type;
		std::list<Declaration*> * declarations;
	public:
		virtual void buildIR(IntermediateRepresentation::BasicBlock *firstBB);
		bool computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>*);
		DeclarationInstruction(Types*, std::list<Declaration*>*);
		virtual ~DeclarationInstruction();
		bool verifyExpressionsTypes();
	};
}
