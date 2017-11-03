#include <iostream>

#include "WhileInstruction.h"

using namespace Model;
using namespace std;

bool WhileInstruction::verifyExpressionsTypes(){
#ifdef DETAIL
	cout << "-- verifyExpressionsTypes WhileInstruction --" << endl;
#endif

	bool correct = true;
	if(!(guardClause==nullptr) && !guardClause->verifyAndUpdateType())
		correct = false;
	if(!ControlInstruction::verifyExpressionsTypes())
		correct = false;
	return correct;
}

bool WhileInstruction::computeAndVerifySymbols(list<map<string,Symbole>*>* symbolTable){
#ifdef DETAIL
	cout << "-- computeAndVerifySymbols WhileInstruction --" << endl;
#endif
	bool correct = true;
	if(!(guardClause==nullptr) && !guardClause->computeAndVerifySymbols(symbolTable))
		correct = false;
	if(!ControlInstruction::computeAndVerifySymbols(symbolTable))
		correct = false;
	return correct;
}

void WhileInstruction::buildIR(IntermediateRepresentation::BasicBlock *firstBB)
{
	// add init and entry condition of the for loop
	IntermediateRepresentation::CFG* cfg = firstBB->getCfg();

	std::string numInstr = cfg->new_BB_name();

	IntermediateRepresentation::BasicBlock *ifTestBB = new IntermediateRepresentation::BasicBlock(cfg, "f_" + cfg->astName() + "_testWhile_" + numInstr);
	firstBB->setExitT(ifTestBB);
	cfg->add_bb(ifTestBB);
	IntermediateRepresentation::Address gcAddr = guardClause->buildIR(ifTestBB, ifTestBB->getLabel());
	IntermediateRepresentation::Address tmp;
	tmp.type = IntermediateRepresentation::CONSTANT;
	tmp.addr = 1;

	firstBB->add_IRInstr(IntermediateRepresentation::SIMPLE_CMP, tmp, gcAddr, IntermediateRepresentation::NULL_ADDRESS);

	IntermediateRepresentation::BasicBlock *finallyBB = new IntermediateRepresentation::BasicBlock(cfg, "f_" + cfg->astName() + "_wFinally_" + numInstr);

	IntermediateRepresentation::BasicBlock *whileBB = new IntermediateRepresentation::BasicBlock(cfg, "f_" + cfg->astName() + "_while_" + numInstr);
	cfg->add_bb(whileBB);

	ifTestBB->setExitT(whileBB);
	ifTestBB->setExitF(finallyBB);

	instruction->buildIR(whileBB);
	whileBB = cfg->getCurrentBB();

	whileBB->setExitT(ifTestBB);

	cfg->add_bb(finallyBB);
}

// ----------------------------- Constructors ----------------------------------

WhileInstruction::WhileInstruction(Expression* expr, Instruction* inst)
	:guardClause(expr), ControlInstruction(inst,expr->getLine())
{
#ifdef DEBUG
    cout << "-- Constructor WhileInstruction --" << endl;
#endif
}

// ------------------------------ Destructor -----------------------------------

WhileInstruction::~WhileInstruction()
{
#ifdef DEBUG
	cout << "-- Destructor WhileInstruction --" << endl;
#endif
	delete guardClause;
}
