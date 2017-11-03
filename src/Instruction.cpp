#include "Instruction.h"

using namespace Model;
using namespace std;

bool Instruction::verifyExpressionsTypes(){
#ifdef DETAIL
	cout << "-- verifyExpressionsTypes Instruction --" << endl;
#endif

	return true;
}

bool Instruction::computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>* symbolTable){
#ifdef DETAIL
	cout << "-- computeAndVerifySymbols Instruction --" << endl;
#endif
		return true;
}

// ----------------------------- Constructors ----------------------------------

Instruction::Instruction (int line)
	:Line(line)
{
#ifdef DEBUG
    cout << "-- Constructor Instruction --" << endl;
#endif
}

// ------------------------------ Destructor -----------------------------------

Instruction::~Instruction ()
{
#ifdef DEBUG
    cout << "-- Destructor Instruction --" << endl;
#endif
}
