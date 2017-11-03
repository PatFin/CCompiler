#include <iostream>

#include "Variable.h"

using namespace Model;
using namespace std;


IntermediateRepresentation::Address Variable::buildIR(IntermediateRepresentation::BasicBlock* firstBB, std::string label)
{
	IntermediateRepresentation::Address addr = firstBB->getCfg()->get_var_address(*(this->name));
	if (addr.addr < 0) {
		// PLACEHOLDER
		firstBB->getCfg()->add_to_symbol_table(*(this->name), this->getType());
		addr = firstBB->getCfg()->get_var_address(*(this->name));
	}
	return addr;
}

bool Variable::computeAndVerifySymbols(list<map<string,Symbole>*>* symbolTable){
#ifdef DETAIL
	cout << "-- computeAndVerifySymbols Variable --" << endl;
#endif
	bool correct = true;

	bool found = false;

	for(list<map<string,Symbole>*>::reverse_iterator lastLevel = symbolTable->rbegin() ; lastLevel != symbolTable->rend(); lastLevel++){

		map<string,Symbole>::iterator it = (*lastLevel)->find(*name);
		if(it != (*lastLevel)->end()){
			if(it->second.getType() == VARIABLE){
				found = true;
				t = it->second.getTypage();

				it->second.setUsed();
			}
		}
	}

	if(!found){
		correct = false;
		cerr << "ERROR on line "<< this->getLine() <<" use of undefined variable : " << *name << endl;
	}

	return correct;
}

// ----------------------------- Constructors ----------------------------------

Variable::Variable(std::string * identifier, int line)
	:name(identifier), LValue(line)
{
#ifdef DEBUG
    cout << "-- Constructor Variable --" << endl;
#endif
}

Variable::Variable(std::string * identifier, Types type, int line)
:name(identifier), LValue(type, line)
{
	#ifdef DEBUG
	cout << "-- Constructor Variable --" << endl;
	#endif
}

// ------------------------------ Destructor -----------------------------------

Variable::~Variable()
{
#ifdef DEBUG
	cout << "-- Destructor Variable --" << endl;
#endif
	delete name;
}
