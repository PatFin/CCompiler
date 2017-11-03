#pragma once

#include <string>
#include "LValue.h"

namespace Model {
	class Array : public LValue {
	private:
		std::string* name;
		Expression* arrayIndex;
	public:
		IntermediateRepresentation::Address buildIR(IntermediateRepresentation::BasicBlock *firstBB, std::string label = "");
		bool computeAndVerifySymbols(list<map<string,Symbole>*>*);
		Array(std::string *, Expression*, int line);
		virtual ~Array();
	};
}
