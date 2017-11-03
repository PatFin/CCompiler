#pragma once

#include "UnaryExpression.h"

namespace Model
{
    class NoAssignUnaryExpression : public UnaryExpression
    {
        private:
            Expression * expression;
        public:
			virtual IntermediateRepresentation::Address buildIR(IntermediateRepresentation::BasicBlock *firstBB, std::string label = "");
            bool computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>*);
            NoAssignUnaryExpression(UNARYOPERATOR  op, Expression * expr, int line);
            bool verifyAndUpdateType();
            virtual ~NoAssignUnaryExpression();
    };
}
