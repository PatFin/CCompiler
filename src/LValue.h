#pragma once

#include "Expression.h"

namespace Model
{
    class LValue : public Expression
    {
    public:
        virtual IntermediateRepresentation::Address buildIR(IntermediateRepresentation::BasicBlock *firstBB, std::string label = "") = 0;
        virtual bool computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>*) = 0;
        LValue (int line);
        LValue (Types, int line );
        ~LValue();
    };
}
