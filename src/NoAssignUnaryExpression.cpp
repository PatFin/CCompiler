#include <iostream>

#include "NoAssignUnaryExpression.h"

using namespace Model;
using namespace std;

IntermediateRepresentation::Address NoAssignUnaryExpression::buildIR(IntermediateRepresentation::BasicBlock *firstBB, std::string label)
{
	IntermediateRepresentation::Address varAdd = this->expression->buildIR(firstBB);

	IntermediateRepresentation::InstructionType op;
	switch(unaryOperator)
	{
		case BIT_NOT_OPERATOR:
				op = IntermediateRepresentation::BNOT;
			break;
		case NOT_OPERATOR:
				op = IntermediateRepresentation::NOT;
			break;
		case UNARY_MINUS_OPERATOR:
				op = IntermediateRepresentation::MINUS;
			break;
		default:
				op = IntermediateRepresentation::NO_OP;
			break;
	}

	firstBB->add_IRInstr(op, varAdd, IntermediateRepresentation::NULL_ADDRESS, varAdd);
	return varAdd;
}

bool NoAssignUnaryExpression::computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>* symbolTable) {
#ifdef DETAIL
	cout << "-- computeAndVerifySymbols NoAssignUnaryExpression --" << endl;
#endif
    bool correct = expression->computeAndVerifySymbols(symbolTable);
    return correct;
}

bool NoAssignUnaryExpression::verifyAndUpdateType(){
#ifdef DETAIL
	cout << "-- verifyAndUpdateType NoAssignUnaryExpression --" << endl;
#endif

	bool correct = true;
		if(expression->verifyAndUpdateType()){
			t = expression->getType();
		}
		else{
			correct = false;
		}
	return true;
}

// ----------------------------- Constructors ----------------------------------

NoAssignUnaryExpression::NoAssignUnaryExpression(UNARYOPERATOR op,
    Expression * expr, int line)
    :expression(expr),UnaryExpression(op,line)
{
#ifdef DEBUG
    cout << "-- Constructor NoAssignUnaryExpression --" << endl;
#endif
}

// ------------------------------ Destructor -----------------------------------

NoAssignUnaryExpression::~NoAssignUnaryExpression()
{
#ifdef DEBUG
    cout << "-- Constructor NoAssignUnnaryExpression --" << endl;
#endif
    delete expression;
}
