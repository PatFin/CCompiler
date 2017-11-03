#pragma once

#include <string>
#include "IR_Address.h"
#include "Expression.h"
#include "Types.h"
#include "LValue.h"

namespace Model {
	class Variable : public LValue {
	private:
		std::string* name;
	public:
		virtual IntermediateRepresentation::Address buildIR(IntermediateRepresentation::BasicBlock *firstBB, std::string label = "");

		Variable(std::string *, int line);
		Variable(std::string *, Types type, int line);
		bool computeAndVerifySymbols(list<map<string,Symbole>*>*);
		virtual ~Variable();
	};
}
