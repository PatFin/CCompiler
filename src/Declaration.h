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

#include "Symbole.h"
#include "Expression.h"
#include "Value.h"
#include "Line.h"

#include "IR_InstructionType.h"
#include "IR_BasicBlock.h"
#include "IR_Address.h"

namespace Model {
	class Declaration : public Line
	{
	protected:
		Types t;
		std::string * name;
	public:
		std::string getName();
		virtual bool computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>*);
		virtual IntermediateRepresentation::Address buildIR(IntermediateRepresentation::BasicBlock *firstBB) = 0;
		virtual void setType(Types);
		virtual bool verifyExpressionsTypes()=0;

		Declaration(std::string *, int line);
		virtual ~Declaration();
	};
}
