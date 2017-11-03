#include <iostream>

#include "ControlInstruction.h"

using namespace Model;
using namespace std;


bool ControlInstruction::verifyExpressionsTypes(){
#ifdef DETAIL
	cout << "-- verifyExpressionsTypes ControlInstruction --" << endl;
#endif
	bool correct = instruction->verifyExpressionsTypes();

    return correct;
}

bool ControlInstruction::computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>* symbolTable)
{
#ifdef DETAIL
	cout << "-- computeAndVerifySymbols ControlInstruction --" << endl;
#endif
    bool correct = instruction->computeAndVerifySymbols(symbolTable);

    return correct;
}

// ----------------------------- Constructors ----------------------------------

ControlInstruction::ControlInstruction(Instruction * instr, int line)
 	:instruction(instr),Instruction(line)
{
#ifdef DEBUG
    cout << "-- Constructor ControlInstruction --" << endl;
#endif
}

// ------------------------------ Destructor -----------------------------------

ControlInstruction::~ControlInstruction()
{
#ifdef DEBUG
    cout << "-- Destructor ControlInstruction --" << endl;
#endif
	delete instruction;
}
