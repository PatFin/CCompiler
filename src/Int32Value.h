#pragma once

#include "Value.h"

namespace Model
{
    class Int32Value : public Value
    {
        private:
          int32_t value;
        public:
          virtual IntermediateRepresentation::Address buildIR(IntermediateRepresentation::BasicBlock *firstBB, std::string label = "");
          size_t getValue();
          Int32Value(int32_t val, int line);
          virtual ~Int32Value();
    };
}
