#pragma once

/**
 * @file
 *
 * @brief Class definition for WhileInstruction
 *
 * This file contains the class and friend functions definition for WhileInstruction.
 *
 */

#include "ControlInstruction.h"
#include "Expression.h"

namespace Model {
	/**
	 * @brief Memory representation for a @c while instruction
	 *
	 * This class represents a @c while loop.
	 *
	 * It is define by a guard clause (a boolean expression that stays true
	 * if the loop needs to keep going) and an instruction,
	 * which can be an instruction block.
	 *
	 */
	class WhileInstruction : public ControlInstruction {
	private:
		/**
		 * @brief Guard clause for the while
		 *
		 * This expression is evaluated as a boolean before each iteration.
		 * If the expression is evaluated as true (non-zero),
		 * the iteration is processed. If the expression is false (zero),
		 * the iteration is not processed and the while instruction stops.
		 */
		Expression* guardClause;
	public:
		bool verifyExpressionsTypes();
		bool computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>*);
		virtual void buildIR(IntermediateRepresentation::BasicBlock *firstBB);

		/**
		 * @brief Default constructor for this class
		 *
		 * This constructor will created a basic instance of this class
		 * with default parameters.
		 */
		WhileInstruction(Expression*, Instruction*);
		virtual ~WhileInstruction();
	};
}
