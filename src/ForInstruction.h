#pragma once

/**
 * @file
 *
 * @brief Class definition for ForInstruction
 *
 * This file contains the class and friend functions definition for ForInstruction.
 *
 */

#include "ControlInstruction.h"
#include "Expression.h"

namespace Model {
	class ForInstruction : public ControlInstruction {
	protected:
		Expression* initialization;
		Expression* guardClause;
		Expression* increment;
	public:
		bool verifyExpressionsTypes();
		bool computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>*);
		virtual void buildIR(IntermediateRepresentation::BasicBlock *firstBB);

		ForInstruction(Expression*, Expression*, Expression*, Instruction*,int line);
		virtual ~ForInstruction();
	};
}
