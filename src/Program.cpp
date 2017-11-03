#include <list>
#include <map>
#include <string>
#include <iostream>

#include "Program.h"
#include "Symbole.h"

using namespace Model;
using namespace std;

bool Program::verifyExpressionsTypes(){
#ifdef DETAIL
	cout << "-- verifyExpressionsTypes Program --" << endl;
#endif

	bool correct = true;

	for(list<Function*>::iterator function = functions.begin(); function != functions.end(); function++){
		if(!(*function)->verifyExpressionsTypes()){
			correct = false;
		}
	}

	for(list<DeclarationInstruction*>::iterator globalVarDef = globals.begin(); globalVarDef != globals.end(); globalVarDef++){
		if(!(*globalVarDef)->verifyExpressionsTypes()){
			correct = false;
		}
	}

	return correct;
}

bool Program::computeSymbolTable(){
#ifdef DETAIL
	cout << "-- computeSymbolTable Program --" << endl;
#endif

	bool correct = true;

	list<map<string,Symbole>*>* symbolTable = new list<map<string,Symbole>*>();
	map<string,Symbole>* globalLevel = new map<string,Symbole>();
	symbolTable->push_back(globalLevel);

	#ifdef DETAIL
	cerr << "Start computing function names" << endl;
	#endif

	// Checking unicity of functions and presence of main
	bool main_exists = false;

	for(list<Function*>::iterator function = functions.begin(); function != functions.end(); function++){
		string functionName((*function)->getName());
		Symbole functionSymbole(functionName,FUNCTION,(*function)->getTypes(), *(*function));

		// Unicity of functions
		if(globalLevel->find(functionName) == globalLevel->end()){
			globalLevel->emplace(functionName,functionSymbole);
		}
		else{
			correct = false;
			cerr << "ERROR on line "<< (*function)->getLine() <<" multiple definition of function : " << functionName << endl;
		}

		// Presence of main function
		if (functionName == "main")
		{
			main_exists = true;

			if ((*function)->getTypes() != Types(VOID))
			{
				cerr << "ERROR on line "<< (*function)->getLine() <<" : incorrect type for main function : " << (*function)->getTypes() << " instead of void." << endl;
			}
		}
	}

	if (!main_exists)
	{
		correct = false;
		cerr << "ERROR : There is no main function in this program." << endl;
	}


	#ifdef DETAIL
	cerr << "End computing function names" << endl;
	cerr << "Start globals declarations" << endl;
	#endif

	for(list<DeclarationInstruction*>::iterator globalVarDef = globals.begin(); globalVarDef != globals.end(); globalVarDef++){
		if(!(*globalVarDef)->computeAndVerifySymbols(symbolTable)){
			correct = false;
		}
	}

	#ifdef DETAIL
	cerr << "End globals declarations" << endl;
	cerr << "Start computing functions " << endl;
	#endif

	for(list<Function*>::iterator function = functions.begin(); function != functions.end(); function++){
		if(!(*function)->computeAndVerifySymbols(symbolTable)){
			correct = false;
		}
	}

	#ifdef DETAIL
	cerr << "End computing functions " << endl;
	cerr << "Start checking unused variables" << endl;
	#endif

	for (map<string, Symbole>::iterator it = globalLevel->begin(); it != globalLevel->end(); it++)
	{
		if (it->second.getType() == VARIABLE && !it->second.isUsed())
		{
			cerr << "WARNING at line " << it->second.getLine() << " : unused global variable " << it->second.getName() << endl;
		}
	}

	#ifdef DETAIL
		cerr << "End checking unused variables" << endl;
	#endif

	symbolTable->pop_back();

	delete globalLevel;
	delete symbolTable;

	return correct;
}

void Program::addFunction(Function * f)
{
	functions.push_back(f);
}

void Program::addGlobalDeclaration(DeclarationInstruction *d)
{
	globals.push_back(d);
}

std::vector<IntermediateRepresentation::CFG*>* Program::buildIR() {
	std::vector<IntermediateRepresentation::CFG*>* IR = new std::vector<IntermediateRepresentation::CFG*>;
	for (list<Function*>::iterator f = functions.begin(); f != functions.end(); f++) {
		IntermediateRepresentation::CFG* cfg = new IntermediateRepresentation::CFG(*f);
		(*f)->buildIR(cfg);
		IR->push_back(cfg);
	}
	return IR;
}

bool Program::verifyProgram()
{
	bool correct = computeSymbolTable();

	if (correct)
	{
		correct = verifyExpressionsTypes();
	}

	return correct;
}

// ----------------------------- Constructors ----------------------------------

Program::Program()
{
#ifdef DEBUG
    cout << "-- Constructor Program --" << endl;
#endif
}

// ------------------------------ Destructor -----------------------------------

Program::~Program()
{
	while (!functions.empty())
	{
		delete functions.back();
		functions.pop_back();
	}

	while (!globals.empty())
	{
		delete globals.back();
		globals.pop_back();
	}
#ifdef DEBUG
    cout << "-- Destructor Program --" << endl;
#endif
}
