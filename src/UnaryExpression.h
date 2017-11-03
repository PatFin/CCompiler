#pragma once

/**
 * @file
 *
 * @brief Class definition for UnaryExpression
 *
 * This file contains the class and friend functions definition for UnaryExpression.
 *
 */

#include <string>

#include "Expression.h"
#include "Operators.h"
#include "Variable.h"

#include "IR_InstructionType.h"
#include "IR_BasicBlock.h"

namespace Model {
	/**
	 * @brief Representation for a Unary Expression in C
	 *
	 * A C unary expression is represented by this class, by combining:
	 * @li A C unary operator
	 * @li another expression
	 */
	class UnaryExpression : public Expression {
	protected:
		UNARYOPERATOR unaryOperator;

	public:
		/**
		 * @brief Base constructor for this class
		 *
		 * This constructor will created a basic instance of this class
		 * while initializing its attributes.
		 *
		 * @param op The operator for this expression
		 * @param exp A pointer to the base expression
		 */
		virtual IntermediateRepresentation::Address buildIR(IntermediateRepresentation::BasicBlock *firstBB, std::string label = "") = 0;

		UnaryExpression(UNARYOPERATOR op, int line);

		virtual ~UnaryExpression();
	};
}
