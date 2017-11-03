#pragma once

#include <string.h>
#include <iostream>

#include "Expression.h"
#include "ListExpression.h"
#include "Types.h"

namespace Model {
    class FunctionEvaluation : public Expression
    {
        private:
            std::string * functionName;
            std::list<Expression*> * parameters;
            std::list<Types> * parametersTypes;
        public:
			bool computeAndVerifySymbols(list<map<string,Symbole>*>*);
			bool verifyAndUpdateType();
            std::string getName();
            virtual IntermediateRepresentation::Address buildIR(IntermediateRepresentation::BasicBlock *, std::string label = "");

            FunctionEvaluation(std::string * name, std::list<Expression*> * param, int line);
            virtual ~FunctionEvaluation();
    };
}
