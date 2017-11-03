#include <iostream>

#include "AssignBinaryExpression.h"

using namespace Model;
using namespace std;

	
IntermediateRepresentation::Address AssignBinaryExpression::buildIR(IntermediateRepresentation::BasicBlock* firstBB, std::string label)
{
	IntermediateRepresentation::Address lhs = leftHandSide->buildIR(firstBB);
	IntermediateRepresentation::Address rhs = rightHandSide->buildIR(firstBB);
	IntermediateRepresentation::InstructionType op;

	switch(binaryOperator)
	{
		case BIT_LEFT_SHIFT_ASSIGN_OPERATOR:
				op = IntermediateRepresentation::LEFT_SHIFT;
			break;
		case BIT_RIGHT_SHIFT_ASSIGN_OPERATOR:
				op = IntermediateRepresentation::RIGHT_SHIFT;
			break;
		case BIT_AND_ASSIGN_OPERATOR:
				op = IntermediateRepresentation::BAND;
			break;
		case BIT_OR_ASSIGN_OPERATOR:
				op = IntermediateRepresentation::BOR;
			break;
		case BIT_XOR_ASSIGN_OPERATOR:
				op = IntermediateRepresentation::BXOR;
			break;
		case PLUS_ASSIGN_OPERATOR:
				op = IntermediateRepresentation::PLUS;
			break;
		case MINUS_ASSIGN_OPERATOR:
				op = IntermediateRepresentation::MINUS;
			break;
		case MUL_ASSIGN_OPERATOR:
				op = IntermediateRepresentation::MUL;
			break;
		case DIV_ASSIGN_OPERATOR:
				op = IntermediateRepresentation::DIV;
			break;
		case MOD_ASSIGN_OPERATOR:
				op = IntermediateRepresentation::MODULUS;
			break;
		case ASSIGN_OPERATOR:
		default:
				op = IntermediateRepresentation::MOVE;
			break;
	}
	firstBB->add_IRInstr(op, rhs, lhs, lhs);
	return lhs;
}

bool AssignBinaryExpression::computeAndVerifySymbols(list<map<string,Symbole>*>* symbolTable){
#ifdef DETAIL
	cout << "-- computeAndVerifySymbols AssignBinaryExpression --" << endl;
#endif
    bool correct = leftHandSide->computeAndVerifySymbols(symbolTable) && BinaryExpression::computeAndVerifySymbols(symbolTable);

    return correct;
}

bool AssignBinaryExpression::verifyAndUpdateType()
{
    bool correct = true;

#ifdef DETAIL
	cout << "-- verifyAndUpdateType AssignBinaryExpression --" << endl;
#endif

    if (!leftHandSide->verifyAndUpdateType())
    {
        correct = false;
    }

    if (!rightHandSide->verifyAndUpdateType())
    {
        correct = false;
    }

    if (correct)
    {
		if ((leftHandSide->getType() == rightHandSide->getType()))
		{
			t = leftHandSide->getType();
		}
		else
		{
			correct = false;
			cerr << "Error at line " << getLine() << " : conflict between types " << leftHandSide->getType() << " and " << rightHandSide->getType() << "." << endl;
		}
    }

    return correct;
}

// ----------------------------- Constructors ----------------------------------

AssignBinaryExpression::AssignBinaryExpression(LValue* left,
    BINARYOPERATOR op,          Expression* right, int line)
    :leftHandSide(left), BinaryExpression(op, right, line)
{
#ifdef DEBUG
    cout << "-- Constructor AssignBinaryExpression --" << endl;
#endif
}

// ------------------------------ Destructor -----------------------------------

AssignBinaryExpression::~AssignBinaryExpression()
{
#ifdef DEBUG
    cout << "-- Destructor AssignBinaryExpression --" << endl;
#endif

    delete leftHandSide;
}
