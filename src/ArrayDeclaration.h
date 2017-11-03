#pragma once

/**
 * @file
 *
 * @brief Class definition for Declaration
 *
 * This file contains the class and friend functions definition for Declaration.
 *
 */

#include <list>
#include <map>
#include <string>

#include "Declaration.h"
#include "Symbole.h"
#include "Expression.h"
#include "Value.h"

#include "IR_InstructionType.h"
#include "IR_BasicBlock.h"
#include "IR_Address.h"

namespace Model {
	class ArrayDeclaration : public Declaration
	{
	private:
		Value * index;
		std::list<Expression*> *initialisation;
	public:
		std::string getName();
		bool computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>*);
		virtual IntermediateRepresentation::Address buildIR(IntermediateRepresentation::BasicBlock *firstBB);
		bool verifyExpressionsTypes();
		void setType(Types);

		ArrayDeclaration(std::string *, Value*, std::list<Expression*>*, int line);
		virtual ~ArrayDeclaration();
	};
}
