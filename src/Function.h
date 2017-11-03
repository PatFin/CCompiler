#pragma once

/**
 * @file
 *
 * @brief Class definition for Function
 *
 * This file contains the class and friend functions definition for Function.
 *
 */

#include <list>
#include <map>
#include <string>

#include "ParameterDeclaration.h"
#include "InstructionBlock.h"
#include "Symbole.h"
#include "Line.h"

#include "IR_CFG.h"

namespace Model {
	class Function : public Line
	{
	private:
		Types * type;
		std::string* identificator;
		std::list<ParameterDeclaration*>* parameters;
		InstructionBlock* instructions;
	public:
		virtual void buildIR(IntermediateRepresentation::CFG* cfg);
		size_t getFrameSize();
		Types getTypes();
		bool verifyExpressionsTypes();
		std::string getName();
		bool computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>*);

		Function(Types*, std::string *, std::list<ParameterDeclaration*>*, InstructionBlock*, int line);
		virtual ~Function();
	};
}

#include "Types.h"
