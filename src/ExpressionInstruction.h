#pragma once

/**
 * @file
 *
 * @brief Class definition for ExpressionInstruction
 *
 * This file contains the class and friend functions definition for ExpressionInstruction.
 *
 */

#include "Instruction.h"
#include "Expression.h"

namespace Model {
	class ExpressionInstruction : public Instruction {
	private:
		Expression* expression;
	public:
		bool computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>*);
		virtual void buildIR(IntermediateRepresentation::BasicBlock *firstBB);

		ExpressionInstruction(Expression*);
		virtual ~ExpressionInstruction();
		bool verifyExpressionsTypes();
	};
}
