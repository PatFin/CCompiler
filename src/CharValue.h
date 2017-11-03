#pragma once

#include "Value.h"

namespace Model
{
    class CharValue : public Value
    {
        private:
            char value;
        public:
			virtual IntermediateRepresentation::Address buildIR(IntermediateRepresentation::BasicBlock *firstBB, std::string label = "");
            size_t getValue();
            CharValue(char val, int line);
            CharValue(char val);
            virtual ~CharValue();
    };
}
