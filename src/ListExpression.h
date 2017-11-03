#pragma once

#include "Expression.h"
#include <list>

namespace Model {
	class ListExpression : public Expression {
	private:
		std::list<Expression*>* expressions;
	public:
		virtual IntermediateRepresentation::Address buildIR(IntermediateRepresentation::BasicBlock *firstBB, std::string label = "");
		bool computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>*);

		std::list<Expression*> * getExpressions();

		ListExpression(std::list<Expression*>*);
		virtual ~ListExpression();
		bool verifyAndUpdateType();
		std::list<Types>* getListTypes();
	};
}
