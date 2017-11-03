#pragma once

#include "Value.h"
#include "IR_BasicBlock.h"

namespace Model
{
    class Int64Value : public Value
    {
        private:
            int64_t value;
        public:
			virtual IntermediateRepresentation::Address buildIR(IntermediateRepresentation::BasicBlock *firstBB, std::string label = "");
            size_t getValue();
            Int64Value(int64_t val);
            Int64Value(int64_t val, int line);
            virtual ~Int64Value();
    };
}
