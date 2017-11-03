#pragma once

#include "BinaryExpression.h"
#include "Expression.h"

namespace Model {
    class NoAssignBinaryExpression : public BinaryExpression {
    private:
        Expression* leftHandSide;

    public:
		virtual IntermediateRepresentation::Address buildIR(IntermediateRepresentation::BasicBlock* firstBB, std::string label = "");
        NoAssignBinaryExpression(Expression* left, BINARYOPERATOR op, Expression* right, int line);
		bool verifyAndUpdateType();
        bool computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>*);
        virtual ~NoAssignBinaryExpression();
    };
}
