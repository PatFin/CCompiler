#include "InstructionBlock.h"

using namespace Model;
using namespace std;


void InstructionBlock::buildIR(IntermediateRepresentation::BasicBlock* firstBB) {
	for (list<Instruction*>::iterator instruction = instructions->begin(); instruction != instructions->end() ; instruction++) {
		(*instruction)->buildIR(firstBB);
		firstBB = firstBB->getCfg()->getCurrentBB();
	}
}

bool InstructionBlock::verifyExpressionsTypes(){
#ifdef DETAIL
	cout << "-- verifyExpressionsTypes InstructionBlock --" << endl;
#endif

	bool correct = true;

	for(list<Instruction*>::iterator instruction = instructions->begin(); instruction != instructions->end() ; instruction++){
			if(!(*instruction)->verifyExpressionsTypes())
				correct = false;
	}

	return correct;
}

bool InstructionBlock::computeAndVerifySymbols(list<map<string,Symbole>*>* symbolTable)
{
#ifdef DETAIL
	cout << "-- computeAndVerifySymbols InstructionBlock --" << endl;
#endif
	bool correct = true;
	map<string,Symbole>* localTable = new map<string,Symbole>();

	symbolTable->push_back(localTable);

	#ifdef DETAIL
	cerr << "Start computing block " << endl;
	#endif
	for(list<Instruction*>::iterator instruction = instructions->begin(); instruction != instructions->end() ; instruction++){
			if(!(*instruction)->computeAndVerifySymbols(symbolTable))
				correct = false;
	}

	for (map<string, Symbole>::iterator it = localTable->begin(); it != localTable->end(); it++)
	{
		if (!it->second.isUsed())
		{
			cerr << "WARNING at line " << it->second.getLine() << " : unused variable " << it->second.getName() << endl;
		}
	}

	#ifdef DETAIL
	cerr << "End computing block " << endl;
	#endif
	symbolTable->pop_back();

	delete localTable;

	return correct;
}

// ----------------------------- Constructors ----------------------------------

InstructionBlock::InstructionBlock(list<Instruction*>* instr, int line)
	:instructions(instr),Instruction(line)
{
#ifdef DEBUG
    cout << "-- Constructor InstructionBlock --" << endl;
#endif
}

// ------------------------------ Destructor -----------------------------------

InstructionBlock::~InstructionBlock()
{
#ifdef DEBUG
cout << "-- Destructor InstructionBlock --" << endl;
#endif
	while (!instructions->empty())
	{
		delete instructions->back();
		instructions->pop_back();
	}
	delete instructions;
}
