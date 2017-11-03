#pragma once

#include "UnaryExpression.h"
#include "Operators.h"

namespace Model {
    class AssignUnaryExpression : public UnaryExpression {
        private:
          LValue * variable;
        public:
	      virtual IntermediateRepresentation::Address buildIR(IntermediateRepresentation::BasicBlock *firstBB, std::string label = "");
            bool computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>*);
            bool verifyAndUpdateType();

            AssignUnaryExpression(UNARYOPERATOR op, LValue * var, int line);
            virtual ~AssignUnaryExpression();
    };
}
