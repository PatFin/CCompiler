#pragma once

/**
 * @file
 *
 * @brief Class definition for IfInstruction
 *
 * This file contains the class and friend functions definition for IfInstruction.
 *
 */

#include "ControlInstruction.h"
#include "Expression.h"
#include "IR_BasicBlock.h"

namespace Model {
	class IfInstruction : public ControlInstruction {
	protected:
		Expression* guardClause;
		Instruction* elseInstruction;
	public:
		bool computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>*);
		virtual void buildIR(IntermediateRepresentation::BasicBlock *firstBB);

		IfInstruction(Expression*, Instruction*, Instruction*);
		virtual ~IfInstruction();
		bool verifyExpressionsTypes();
	};
}
