#include <iostream>
#include <list>

#include "ListExpression.h"
#include "Expression.h"

using namespace Model;
using namespace std;


IntermediateRepresentation::Address ListExpression::buildIR(IntermediateRepresentation::BasicBlock* firstBB, std::string label)
{
	IntermediateRepresentation::Address addr;
	for (std::list<Expression*>::iterator expr = expressions->begin(); expr != expressions->end(); expr++)
	{
		addr = (*expr)->buildIR(firstBB, label);
	}
	return addr;
}

bool ListExpression::computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>* symbolTable)
{
	#ifdef DETAIL
	cout << "-- computeAndVerifySymbols ListExpression --" << endl;
	#endif
	bool correct = true;

	for (std::list<Expression*>::iterator expr = expressions->begin(); expr != expressions->end(); expr++)
	{
		if (!(*expr)->computeAndVerifySymbols(symbolTable))
		{
			correct = false;
		}
	}

	return correct;
}

std::list<Expression*> * ListExpression::getExpressions()
{
	return expressions;
}

list<Types>* ListExpression::getListTypes(){
	list<Types>* listTypes = new list<Types>();

	for (std::list<Expression*>::iterator expr = expressions->begin(); expr != expressions->end(); expr++)
	{
		if ((*expr)->verifyAndUpdateType())
		{
			listTypes->push_back((*expr)->getType());
		}
		else{
			listTypes->push_back(Types(VOID));
		}
	}

	return listTypes;
}

bool ListExpression::verifyAndUpdateType()
{
#ifdef DETAIL
	cout << "-- verifyAndUpdateType ListExpression --" << endl;
#endif

	bool correct = true;

	t = (*(expressions->begin()))->getType();

	for (std::list<Expression*>::iterator expr = expressions->begin(); expr != expressions->end(); expr++)
	{
		if (!(*expr)->verifyAndUpdateType())
		{
			correct = false;
		}
		if(t != (*expr)->getType()){
			correct = false;
			t = Types(VOID);
		}
	}

	return correct;
}

// ----------------------------- Constructors ----------------------------------

ListExpression::ListExpression(std::list<Expression*>* expr)
	: expressions(expr),Expression(expr->back()->getLine())
{
#ifdef DEBUG
    cout << "-- Constructor ListExpression --" << endl;
#endif
}

// ------------------------------ Destructor -----------------------------------

ListExpression::~ListExpression()
{
#ifdef DEBUG
    cout << "-- Destructor ListExpression --" << endl;
#endif

	while (!expressions->empty()) {
		delete expressions->back();
		expressions->pop_back();
	}
	delete expressions;

}
