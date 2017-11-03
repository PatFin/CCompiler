#include <iostream>

#include "Expression.h"

using namespace Model;
using namespace std;

IntermediateRepresentation::Address Expression::buildIR(IntermediateRepresentation::BasicBlock *firstBB, std::string label)
{
	return IntermediateRepresentation::NULL_ADDRESS;
}

bool Expression::computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>* symbolTable)
{
	#ifdef DEBUG
	cout << "-- computeAndVerifySymbols Expression --" << endl;
	#endif
	// Nothing to check, hence returns true.
	bool correct = true;

	return correct;
}

Types Expression::getType(){
	return t;
}

bool Expression::verifyAndUpdateType(){
#ifdef DETAIL
	cout << "-- verifyAndUpdateType Expression --" << endl;
#endif
	bool correct = true;

	return correct;
}

// ----------------------------- Constructors ----------------------------------

Expression::Expression(int line):Line(line)
{
#ifdef DETAIL
    cout << "-- Constructor Expression --" << endl;
#endif
}

Expression::Expression(Types type, int line)
	:t(type), Line(line)
{
#ifdef DETAIL
    cout << "-- Constructor Expression --" << endl;
#endif
}

// ------------------------------ Destructor -----------------------------------

Expression::~Expression()
{
#ifdef DEBUG
    cout << "-- Destructor Expression --" << endl;
#endif
}
