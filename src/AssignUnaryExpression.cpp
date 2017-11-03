#include <iostream>

#include "AssignUnaryExpression.h"

using namespace Model;
using namespace std;


IntermediateRepresentation::Address AssignUnaryExpression::buildIR(IntermediateRepresentation::BasicBlock* firstBB, std::string label)
{
	IntermediateRepresentation::Address varAdd = variable->buildIR(firstBB);

	IntermediateRepresentation::InstructionType op;
	switch(unaryOperator)
	{
		case PRE_INCREMENT_OPERATOR:
				op = IntermediateRepresentation::PRE_INC;
			break;
		case PRE_DECREMENT_OPERATOR:
				op = IntermediateRepresentation::PRE_DEC;
			break;
		case POST_INCREMENT_OPERATOR:
				op = IntermediateRepresentation::POST_INC;
			break;
		case POST_DECREMENT_OPERATOR:
				op = IntermediateRepresentation::POST_DEC;
			break;
		default:
				op = IntermediateRepresentation::NO_OP;
			break;
	}

	firstBB->add_IRInstr(op, varAdd, IntermediateRepresentation::NULL_ADDRESS, varAdd);
	return varAdd;
}

bool AssignUnaryExpression::computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>* symbolTable) {
#ifdef DETAIL
	cout << "-- computeAndVerifySymbols AssignUnaryExpression --" << endl;
#endif
    bool correct = variable->computeAndVerifySymbols(symbolTable);

    return correct;
}

bool AssignUnaryExpression::verifyAndUpdateType()
{
#ifdef DETAIL
	cout << "-- verifyAndUpdateType AssignUnaryExpression --" << endl;
#endif
	bool correct = variable->verifyAndUpdateType();

	if (correct)
	{
		t = variable->getType();
	}

	return correct;
}

// ----------------------------- Constructors ----------------------------------

AssignUnaryExpression::AssignUnaryExpression(UNARYOPERATOR op, LValue * var, int line)
    :variable(var),UnaryExpression(op, line)
{
#ifdef DEBUG
    cout << "-- Constructor AssignUnaryExpression --" << endl;
#endif
}

// ------------------------------ Destructor -----------------------------------

AssignUnaryExpression::~AssignUnaryExpression()
{
#ifdef DEBUG
    cout << "-- Destructor AssignBinaryExpression --" << endl;
#endif

    delete variable;
}
