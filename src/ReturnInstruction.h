#pragma once

/**
 * @file
 *
 * @brief Class definition for ReturnInstruction
 *
 * This file contains the class and friend functions definition for ReturnInstruction.
 *
 */

#include "Instruction.h"
#include "Expression.h"

namespace Model {
	/**
	 * @brief Memory representation for the C @c return
	 *
	 * This class represents a return instruction, that ends a functions
	 * by returnning a value (or nothing) obtained by evaluating an expression.
	 */
	class ReturnInstruction : public Instruction {
	private:
		/**
		 * @brief The return value
		 *
		 * This expression will be evaluated in order to get the returned value.
		 *
		 * If the return type is void, this pointer should be @c nullptr.
		 */
		Expression* expression;
	public:
		/**
		 * @brief Default constructor for this class
		 *
		 * This constructor will created a basic instance of this class
		 * while initializing its attributes.
		 */
		bool computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>*);
		bool verifyExpressionsTypes();
		virtual void buildIR(IntermediateRepresentation::BasicBlock *firstBB);

		ReturnInstruction(Expression*);
		virtual ~ReturnInstruction();
	};
}
