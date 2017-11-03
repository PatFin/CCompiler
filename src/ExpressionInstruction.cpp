#include <iostream>

#include "ExpressionInstruction.h"
#include "Expression.h"

using namespace Model;
using namespace std;


bool ExpressionInstruction::computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>* symbolTable) {
	#ifdef DETAIL
		cout << "-- computeAndVerifySymbols ExpressionInstruction --" << endl;
	#endif

	bool correct = expression->computeAndVerifySymbols(symbolTable);

	return correct;
}

void ExpressionInstruction::buildIR(IntermediateRepresentation::BasicBlock *firstBB)
{
	expression->buildIR(firstBB);
}

bool ExpressionInstruction::verifyExpressionsTypes(){
#ifdef DETAIL
	cout << "-- verifyExpressionsTypes ExpressionInstruction --" << endl;
#endif

	bool correct = expression->verifyAndUpdateType();

	return correct;
}

// ----------------------------- Constructors ----------------------------------

ExpressionInstruction::ExpressionInstruction(Expression* expr)
	:expression(expr),Instruction(expr->getLine())
{
#ifdef DEBUG
    cout << "-- Constructor ExpressionInstruction --" << endl;
#endif
}

// ------------------------------ Destructor -----------------------------------

ExpressionInstruction::~ExpressionInstruction()
{
#ifdef DEBUG
    cout << "-- Destructor ExpressionInstruction --" << endl;
#endif
	delete expression;
}
