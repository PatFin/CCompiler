#pragma once

/**
 * @file
 *
 * @brief Class definition for Expression
 *
 * This file contains the class and friend functions definition for Expression.
 *
 */

#include <string>
#include <list>
#include <map>

#include "Symbole.h"

#include "IR_BasicBlock.h"
#include "Types.h"
#include "Line.h"

using namespace std;

namespace Model {
	class Variable;
	class Value;

	class Expression : public Line {
		protected:
			Types t;
		public:
			virtual bool verifyAndUpdateType();
			virtual bool computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>*);
			virtual Types getType();
			virtual IntermediateRepresentation::Address buildIR(IntermediateRepresentation::BasicBlock *firstBB, std::string label = "");
			Expression();
			Expression(int line);
			Expression(Types type, int line);

			virtual ~Expression();
	};
}
