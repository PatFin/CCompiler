#include <iostream>
#include "ForInstruction.h"

using namespace Model;
using namespace std;

bool ForInstruction::computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>* symbolTable) {
#ifdef DETAIL
	cout << "-- computeAndVerifySymbols ForInstruction --" << endl;
#endif
	bool correct = true;

	if (initialization != nullptr && !initialization->computeAndVerifySymbols(symbolTable))
	{
		correct = false;
	}

	if (guardClause != nullptr && !guardClause->computeAndVerifySymbols(symbolTable))
	{
		correct = false;
	}

	if (increment != nullptr && !increment->computeAndVerifySymbols(symbolTable))
	{
		correct = false;
	}

	if (!ControlInstruction::computeAndVerifySymbols(symbolTable))
	{
		correct = false;
	}

	return correct;
}

void ForInstruction::buildIR(IntermediateRepresentation::BasicBlock *firstBB)
{
	// TODO
	// add init and entry guardClause of the for loop
	IntermediateRepresentation::CFG *cfg = firstBB->getCfg();
	initialization->buildIR(firstBB);

	std::string numInstr = cfg->new_BB_name();

	IntermediateRepresentation::BasicBlock *testForBB = new IntermediateRepresentation::BasicBlock(cfg, "f_" + cfg->astName() + "_testFor_" + numInstr);
	cfg->add_bb(testForBB);
	IntermediateRepresentation::Address gcAddr = guardClause->buildIR(testForBB, testForBB->getLabel());
	IntermediateRepresentation::Address tmp;
	tmp.type = IntermediateRepresentation::CONSTANT;
	tmp.addr = 1;

	firstBB->add_IRInstr(IntermediateRepresentation::SIMPLE_CMP, tmp, gcAddr, IntermediateRepresentation::NULL_ADDRESS);

	// create the finally block for the for loop
	IntermediateRepresentation::BasicBlock *finallyBB = new IntermediateRepresentation::BasicBlock(cfg, "f_" + cfg->astName() + "_lFinally_" + numInstr);

	// create the for Block
	IntermediateRepresentation::BasicBlock *forBB = new IntermediateRepresentation::BasicBlock(cfg, "f_" + cfg->astName() + "_loop_" + numInstr);
	cfg->add_bb(forBB);
	instruction->buildIR(forBB);
	increment->buildIR(forBB);
	forBB->setExitT(testForBB);

	firstBB->setExitT(testForBB);

	testForBB->setExitT(forBB);
	testForBB->setExitF(finallyBB);

	cfg->add_bb(finallyBB);
}

bool ForInstruction::verifyExpressionsTypes(){
#ifdef DETAIL
	cout << "-- verifyExpressionsTypes ForInstruction --" << endl;
#endif

	bool correct = true;

	if (initialization != nullptr && !initialization->verifyAndUpdateType())
	{
		correct = false;
	}

	if (guardClause != nullptr && !guardClause->verifyAndUpdateType())
	{
		correct = false;
	}

	if (increment != nullptr && !increment->verifyAndUpdateType())
	{
		correct = false;
	}

	if (!ControlInstruction::verifyExpressionsTypes())
	{
		correct = false;
	}

	return correct;
}

// ----------------------------- Constructors ----------------------------------

ForInstruction::ForInstruction(Expression* init, Expression* cond,
							   Expression* aIncrement, Instruction* instr, int line)
	:initialization(init), guardClause(cond), increment(aIncrement),
		ControlInstruction(instr, line)
{
#ifdef DEBUG
    cout << "-- Constructor ForInstruction --" << endl;
#endif
}

// ------------------------------ Destructor -----------------------------------

ForInstruction::~ForInstruction()
{
#ifdef DEBUG
    cout << "-- Destructor ForInstruction --" << endl;
#endif
	delete initialization;
	delete guardClause;
	delete increment;
}
