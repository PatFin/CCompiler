#include <iostream>
#include "IfInstruction.h"

using namespace Model;
using namespace std;


void IfInstruction::buildIR(IntermediateRepresentation::BasicBlock *firstBB)
{
	IntermediateRepresentation::CFG* cfg = firstBB->getCfg();

	// create block's name
	std::string numInstr = cfg->new_BB_name();
	std::string BBIfName = "f_" + cfg->astName() + "_if_" + numInstr;
	std::string BBElseName = "f_" + cfg->astName() + "_else_" + numInstr;
	std::string BBFinallyName = "f_" + cfg->astName() + "_ifinally_" + numInstr;

	IntermediateRepresentation::Address gcAddr = guardClause->buildIR(firstBB, BBIfName);
	IntermediateRepresentation::Address tmp;
	tmp.type = IntermediateRepresentation::CONSTANT;
	tmp.addr = 1;

	firstBB->add_IRInstr(IntermediateRepresentation::SIMPLE_CMP, tmp, gcAddr, IntermediateRepresentation::NULL_ADDRESS);

	// create ExitTrue block
	IntermediateRepresentation::BasicBlock *BBThen = new IntermediateRepresentation::BasicBlock(cfg, BBIfName);
	cfg->add_bb(BBThen);
	instruction->buildIR(BBThen);
	firstBB->setExitT(BBThen);

	// create ExitFalse block
	IntermediateRepresentation::BasicBlock	*BBElse = new IntermediateRepresentation::BasicBlock(cfg, BBElseName);
	cfg->add_bb(BBElse);
	elseInstruction->buildIR(BBElse);
	firstBB->setExitF(BBElse);

	// create "Finally" block
	IntermediateRepresentation::BasicBlock *BBFinally = new IntermediateRepresentation::BasicBlock(cfg, BBFinallyName);
	cfg->add_bb(BBFinally);
	BBElse->setExitT(BBFinally);
	BBThen->setExitT(BBFinally);

	// change firstBB pointer to the Finally block
	firstBB = cfg->getCurrentBB();
}

bool IfInstruction::computeAndVerifySymbols(list<map<string,Symbole>*>* symbolTable){
#ifdef DETAIL
	cout << "-- computeAndVerifySymbols IfInstruction --" << endl;
#endif
	bool correct = true;
	if(!(guardClause==nullptr) && !guardClause->computeAndVerifySymbols(symbolTable))
		correct = false;
	if(!ControlInstruction::computeAndVerifySymbols(symbolTable))
		correct = false;
	if(!(elseInstruction==nullptr) && !elseInstruction->computeAndVerifySymbols(symbolTable))
		correct = false;
	return correct;
}

bool IfInstruction::verifyExpressionsTypes(){
#ifdef DETAIL
	cout << "-- verifyExpressionsTypes IfInstruction --" << endl;
#endif

	bool correct = true;
	if(!(guardClause==nullptr) && !guardClause->verifyAndUpdateType())
		correct = false;
	if(!ControlInstruction::verifyExpressionsTypes())
		correct = false;
	if(!(elseInstruction==nullptr) && !elseInstruction->verifyExpressionsTypes())
		correct = false;
	return correct;
}

// ----------------------------- Constructors ----------------------------------

IfInstruction::IfInstruction(Expression* guard, Instruction* thenInst,
									Instruction* elseInst)
	:guardClause(guard), elseInstruction(elseInst), ControlInstruction(thenInst,guard->getLine())
{
#ifdef DEBUG
    cout << "-- Constructor IfInstruction --" << endl;
#endif
}

// ------------------------------ Destructor -----------------------------------

IfInstruction::~IfInstruction()
{
#ifdef DEBUG
    cout << "-- Destructor IfInstruction --" << endl;
#endif
	delete guardClause;
	delete elseInstruction;
}
