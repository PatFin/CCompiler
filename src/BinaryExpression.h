#pragma once

/**
 * @file
 *
 * @brief Class definition for BinaryExpression
 *
 * This file contains the class and friend functions definition for BinaryExpression.
 *
 */

#include <string>

#include "Expression.h"
#include "Operators.h"
#include "Variable.h"

#include "IR_InstructionType.h"
#include "IR_BasicBlock.h"
#include "IR_Address.h"

namespace Model {
	/**
	 * @brief Representation for a binary expression in C
	 *
	 * A C binary expression can be represented by this class, by combining:
	 * @li A left-side expression
	 * @li A binary operator
	 * @li A right-side expression
	 */
	class BinaryExpression : public Expression {
	protected:
		BINARYOPERATOR binaryOperator;
		Expression * rightHandSide;

	public:
		/**
		 * @brief Base constructor for this class
		 *
		 * This constructor will created a basic instance of this class
		 * while initializing its attributes.
		 *
		 * @param left A pointer to the left-side expression
		 * @param op The operator for this expression
		 * @param right A pointer to the right-side expression
		 */
		virtual IntermediateRepresentation::Address buildIR(IntermediateRepresentation::BasicBlock *firstBB, std::string label = "") = 0;
		virtual bool computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>*);

		BinaryExpression(BINARYOPERATOR op, Expression * right, int line);
		virtual bool verifyAndUpdateType();

		virtual ~BinaryExpression();
	};
}
