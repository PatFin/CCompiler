#include <iostream>

#include "Function.h"
#include <iostream>

#include "IR_CFG.h"
#include "IR_BasicBlock.h"

using namespace std;
using namespace Model;


bool Function::verifyExpressionsTypes(){
#ifdef DETAIL
	cout << "-- verifyExpressionsTypes Function --" << endl;
#endif

	bool correct = true;

	if(!instructions->verifyExpressionsTypes())
		correct = false;

	return correct;
}

Types Function::getTypes(){
	return *type;
}

bool Function::computeAndVerifySymbols(list<map<string,Symbole>*>* symbolTable){
	#ifdef DETAIL
	cout << "-- computeAndVerifySymbols Function --" << endl;
	#endif
	bool correct = true;
	map<string,Symbole>* parameterTable = new map<string,Symbole>();

	bool found = false;

	map<string,Symbole>::iterator symbole;

	for(list<map<string,Symbole>*>::reverse_iterator lastLevel = symbolTable->rbegin() ; lastLevel != symbolTable->rend(); lastLevel++){

		map<string,Symbole>::iterator it = (*lastLevel)->find(*identificator);
		if(it != (*lastLevel)->end()){
			if(it->second.getType() == FUNCTION)
            {
                found = true;
				symbole = it;
            }
		}
	}

	list<Types> * parameterTypes = new list<Types>();
	symbole->second.addFunctionParameters(parameterTypes);


	symbolTable->push_back(parameterTable);

	#ifdef DETAIL
	cerr << "Start computing function parameters " << endl;
	#endif

	if(parameters != nullptr)
	{
		for(list<ParameterDeclaration*>::iterator paramDecl = parameters->begin(); paramDecl != parameters->end(); paramDecl++){
			if(!(*paramDecl)->computeAndVerifySymbols(symbolTable)){
				correct = false;
			}
			parameterTypes->push_back((*paramDecl)->getType());
		}
	}

	#ifdef DETAIL
	cerr << "end computing function parameters" << endl;
	#endif

	if(!instructions->computeAndVerifySymbols(symbolTable))
		correct = false;

	for (map<string, Symbole>::iterator it = parameterTable->begin(); it != parameterTable->end(); it++)
	{
		if (!it->second.isUsed())
		{
			cerr << "WARNING at line " << it->second.getLine() << " : unused parameter " << it->second.getName() << endl;
		}
	}

	symbolTable->pop_back();

	delete parameterTable;

	return correct;
}


string Function::getName(){
	return *identificator;
}

size_t Function::getFrameSize() {
	size_t frameSize = this->type->getSize();
	for (list<ParameterDeclaration*>::iterator paramDecl = parameters->begin(); paramDecl != parameters->end(); paramDecl++) {
		frameSize += (*paramDecl)->getTypeSize();
	}
	return frameSize;
}

void Function::buildIR(IntermediateRepresentation::CFG* cfg) {
	IntermediateRepresentation::BasicBlock *entryBB = new IntermediateRepresentation::BasicBlock(cfg, "f_" + *(this->identificator) + "_" + cfg->new_BB_name());
	cfg->add_bb(entryBB);

	int counter = 0;
	for (list<ParameterDeclaration*>::iterator paramDecl = parameters->begin(); paramDecl != parameters->end(); paramDecl++) {
		(*paramDecl)->buildIR(entryBB);

		IntermediateRepresentation::Address addr = cfg->get_var_address((*paramDecl)->getName());

		switch(counter)
		{
			case 0:
				entryBB->add_IRInstr(IntermediateRepresentation::MOVE, IntermediateRepresentation::Address{IntermediateRepresentation::REGISTER_DIRECT,IntermediateRepresentation::IRregToIndex(IntermediateRepresentation::R4, IntermediateRepresentation::QWORD),
					0},
					IntermediateRepresentation::NULL_ADDRESS,
					addr);
				break;

			case 1:
				entryBB->add_IRInstr(IntermediateRepresentation::MOVE, IntermediateRepresentation::Address{IntermediateRepresentation::REGISTER_DIRECT,IntermediateRepresentation::IRregToIndex(IntermediateRepresentation::R5, IntermediateRepresentation::QWORD),
					0},
					IntermediateRepresentation::NULL_ADDRESS,
					addr);
				break;

			case 2:
				entryBB->add_IRInstr(IntermediateRepresentation::MOVE, IntermediateRepresentation::Address{IntermediateRepresentation::REGISTER_DIRECT,IntermediateRepresentation::IRregToIndex(IntermediateRepresentation::R3, IntermediateRepresentation::QWORD),
					0},
					IntermediateRepresentation::NULL_ADDRESS,
					addr);
				break;

			case 3:
				entryBB->add_IRInstr(IntermediateRepresentation::MOVE, IntermediateRepresentation::Address{IntermediateRepresentation::REGISTER_DIRECT,IntermediateRepresentation::IRregToIndex(IntermediateRepresentation::R2, IntermediateRepresentation::QWORD),
					0},
					IntermediateRepresentation::NULL_ADDRESS,
					addr);
				break;

			case 4:
				entryBB->add_IRInstr(IntermediateRepresentation::MOVE, IntermediateRepresentation::Address{IntermediateRepresentation::REGISTER_DIRECT,IntermediateRepresentation::IRregToIndex(IntermediateRepresentation::R8, IntermediateRepresentation::QWORD),
					0},
					IntermediateRepresentation::NULL_ADDRESS,
					addr);
				break;

			case 5:
				entryBB->add_IRInstr(IntermediateRepresentation::MOVE, IntermediateRepresentation::Address{IntermediateRepresentation::REGISTER_DIRECT,IntermediateRepresentation::IRregToIndex(IntermediateRepresentation::R9, IntermediateRepresentation::QWORD),
					0},
					IntermediateRepresentation::NULL_ADDRESS,
					addr);
				break;

			default:
				entryBB->add_IRInstr(IntermediateRepresentation::POP, IntermediateRepresentation::NULL_ADDRESS, IntermediateRepresentation::NULL_ADDRESS, addr);
				break;
		}

		counter++;
	}
	instructions->buildIR(entryBB);
}

// ----------------------------- Constructors ----------------------------------

Function::Function( Types* aType, std::string * name, list<ParameterDeclaration*>* param, InstructionBlock* instr, int line)
	:type(aType), identificator(name), parameters(param),
	instructions(instr),Line(line)
{
#ifdef DEBUG
    cout << "-- Constructor Function --" << endl;
#endif
}

// ------------------------------ Destructor -----------------------------------

Function::~Function()
{
#ifdef DEBUG
    cout << "-- Destructor Function --" << endl;
#endif
	delete type;
	delete identificator;
	while (!parameters->empty())
	{
		delete parameters->back();
		parameters->pop_back();
	}
	delete parameters;
	delete instructions;
}
