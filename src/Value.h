#pragma once

#include <cstdint>
#include "Expression.h"

namespace Model {
	class Value : public Expression {

	public:
		virtual IntermediateRepresentation::Address buildIR(IntermediateRepresentation::BasicBlock *firstBB, std::string label = "") = 0;
		bool computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>*);
		virtual size_t getValue() = 0;
		Value(int line);
		virtual ~Value();
	};
}
