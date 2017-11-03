#include <iostream>

#include "BinaryExpression.h"

using namespace Model;
using namespace std;


bool BinaryExpression::computeAndVerifySymbols(list<map<string,Symbole>*>* symbolTable){
#ifdef DETAIL
	cout << "-- computeAndVerifySymbols BinaryExpression --" << endl;
#endif
    bool correct = rightHandSide->computeAndVerifySymbols(symbolTable);

    return correct;
}

bool BinaryExpression::verifyAndUpdateType()
{
#ifdef DETAIL
	cout << "-- verifyAndUpdateType BinaryExpression --" << endl;
#endif
	bool correct = true;

	return correct;
}

// ----------------------------- Constructors ----------------------------------

BinaryExpression::BinaryExpression(BINARYOPERATOR op, Expression * right, int line)
    :binaryOperator(op),rightHandSide(right),Expression(line)
{
#ifdef DEBUG
    cout << "-- Constructor BinaryExpression --" << endl;
#endif
}

// ------------------------------ Destructor -----------------------------------

BinaryExpression::~BinaryExpression()
{
    #ifdef DEBUG
    cout << "-- Destructor BinaryExpression --" << endl;
    #endif

    delete rightHandSide;
}
