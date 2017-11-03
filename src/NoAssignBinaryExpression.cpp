#include <iostream>

#include "NoAssignBinaryExpression.h"

#include "Expression.h"

using namespace Model;
using namespace std;

IntermediateRepresentation::Address NoAssignBinaryExpression::buildIR(IntermediateRepresentation::BasicBlock *firstBB, std::string label)
{
	IntermediateRepresentation::Address lhs = leftHandSide->buildIR(firstBB);
	IntermediateRepresentation::Address rhs = rightHandSide->buildIR(firstBB);

	//TODO
	std::string nameResultVar = firstBB->getCfg()->create_new_tempvar(leftHandSide->getType());
	IntermediateRepresentation::Address Dest = firstBB->getCfg()->get_var_address(nameResultVar);

	IntermediateRepresentation::InstructionType op;
	switch(binaryOperator)
	{
		case BIT_LEFT_SHIFT_OPERATOR:
				op = IntermediateRepresentation::LEFT_SHIFT;
			break;
		case BIT_RIGHT_SHIFT_OPERATOR:
				op = IntermediateRepresentation::RIGHT_SHIFT;
			break;
		case BIT_AND_OPERATOR:
				op = IntermediateRepresentation::BAND;
			break;
		case BIT_OR_OPERATOR:
				op = IntermediateRepresentation::BOR;
			break;
		case XOR_OPERATOR:
				op = IntermediateRepresentation::BXOR;
			break;
		case PLUS_OPERATOR:
				op = IntermediateRepresentation::PLUS;
			break;
		case MINUS_OPERATOR:
				op = IntermediateRepresentation::MINUS;
			break;
		case MUL_OPERATOR:
				op = IntermediateRepresentation::MUL;
			break;
		case DIV_OPERATOR:
				op = IntermediateRepresentation::DIV;
			break;
		case MODULUS_OPERATOR:
				op = IntermediateRepresentation::MODULUS;
			break;
		case TEST_SUP_OPERATOR :
				op = IntermediateRepresentation::COMP_SUP ;
			break;
		case TEST_INF_OPERATOR :
				op = IntermediateRepresentation::COMP_INF ;
			break;
		case TEST_EQUAL_OPERATOR :
				op = IntermediateRepresentation::COMP_EQ ;
			break;
		case TEST_INFEQUAL_OPERATOR :
				op = IntermediateRepresentation::COMP_INFEQ ;
			break;
		case TEST_SUPEQUAL_OPERATOR :
				op = IntermediateRepresentation::COMP_SUPEQ ;
			break;
		case TEST_DIFFERENT_OPERATOR :
				op = IntermediateRepresentation::COMP_DIFF ;
			break;
		case OR_OPERATOR :
				op = IntermediateRepresentation::OR ;
			break;
		case AND_OPERATOR :
				op = IntermediateRepresentation::AND ;
			break;
		case COMA_OPERATOR :
			// 	op = IntermediateRepresentation::AND
			// break;
		default:
				op = IntermediateRepresentation::MOVE;
			break;
	}
	firstBB->add_IRInstr(op, rhs, lhs, Dest);

	return Dest;
}

bool NoAssignBinaryExpression::computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>* symbolTable) {
#ifdef DETAIL
	cout << "-- computeAndVerifySymbols NoAssignBinaryExpression --" << endl;
#endif
    bool correct = leftHandSide->computeAndVerifySymbols(symbolTable) && rightHandSide->computeAndVerifySymbols(symbolTable);

    return correct;
}

bool NoAssignBinaryExpression::verifyAndUpdateType(){
#ifdef DETAIL
	cout << "-- verifyAndUpdateType NoAssignBinaryExpression --" << endl;
#endif

	bool correct = true;
		if(!leftHandSide->verifyAndUpdateType()){
			correct = false;
		}
		if(!rightHandSide->verifyAndUpdateType()){
			correct = false;
		}
		if(correct && leftHandSide->getType()==rightHandSide->getType()){
			t = leftHandSide->getType();
		}
		else{
			correct = false;
		}
	return true;
}

// ----------------------------- Constructors ----------------------------------

NoAssignBinaryExpression::NoAssignBinaryExpression(Expression* left, BINARYOPERATOR op, Expression* right, int line)
    :leftHandSide(left), BinaryExpression(op, right, line)
{
#ifdef DEBUG
    cout << "-- Constructor NoAssignBinaryExpression --" << endl;
#endif
}

// ------------------------------ Destructor -----------------------------------

NoAssignBinaryExpression::~NoAssignBinaryExpression()
{
#ifdef DEBUG
    cout << "-- Destructor NoAssignBinaryExpression --" << endl;
#endif
    delete leftHandSide;
}
