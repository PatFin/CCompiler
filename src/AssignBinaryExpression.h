#pragma once

#include "BinaryExpression.h"
#include "LValue.h"

namespace Model {
    class AssignBinaryExpression : public BinaryExpression {
    private:
        LValue * leftHandSide;

    public:
		    virtual IntermediateRepresentation::Address buildIR(IntermediateRepresentation::BasicBlock *firstBB, std::string label = "");
        AssignBinaryExpression(LValue* left, BINARYOPERATOR op, Expression* right, int line);

        bool computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>*);
        bool verifyAndUpdateType();

        virtual ~AssignBinaryExpression();
    };
}
