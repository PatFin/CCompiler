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
	class VariableDeclaration : public Declaration
	{
	private:
		Expression* initialisation;
	public:
		std::string getName();
		bool computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>*);
		virtual IntermediateRepresentation::Address buildIR(IntermediateRepresentation::BasicBlock *firstBB);
		void setType(Types);
		bool verifyExpressionsTypes();

		VariableDeclaration(std::string *,Expression*, int line);
		virtual ~VariableDeclaration();
	};
}
