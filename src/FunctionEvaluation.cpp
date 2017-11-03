#include <iostream>
#include "FunctionEvaluation.h"

using namespace Model;
using namespace std;


IntermediateRepresentation::Address FunctionEvaluation::buildIR(IntermediateRepresentation::BasicBlock* firstBB, std::string label)
{
	//parameters->buildIR(firstBB);
	IntermediateRepresentation::Address addr;

	int counter = 0;
	for(list<Expression*>::iterator expr = parameters->begin() ; expr != parameters->end(); expr++){
		addr = (*expr)->buildIR(firstBB);
		if(addr != IntermediateRepresentation::NULL_ADDRESS)
		{
			// cout << "counter fun eval " << counter << " size " << parameters->size() << endl;
			switch(counter)
			{
				case 0:
					firstBB->add_IRInstr(IntermediateRepresentation::MOVE, addr,
						IntermediateRepresentation::NULL_ADDRESS,
						IntermediateRepresentation::Address{IntermediateRepresentation::REGISTER_DIRECT,IntermediateRepresentation::IRregToIndex(IntermediateRepresentation::R4, IntermediateRepresentation::QWORD),
						0});
					break;

				case 1:
					firstBB->add_IRInstr(IntermediateRepresentation::MOVE, addr,
						IntermediateRepresentation::NULL_ADDRESS,
						IntermediateRepresentation::Address{IntermediateRepresentation::REGISTER_DIRECT,IntermediateRepresentation::IRregToIndex(IntermediateRepresentation::R5, IntermediateRepresentation::QWORD),
						0});
					break;

				case 2:
					firstBB->add_IRInstr(IntermediateRepresentation::MOVE, addr,
						IntermediateRepresentation::NULL_ADDRESS,
						IntermediateRepresentation::Address{IntermediateRepresentation::REGISTER_DIRECT,IntermediateRepresentation::IRregToIndex(IntermediateRepresentation::R3, IntermediateRepresentation::QWORD),
						0});
					break;
				case 3:
					firstBB->add_IRInstr(IntermediateRepresentation::MOVE, addr,
						IntermediateRepresentation::NULL_ADDRESS,
						IntermediateRepresentation::Address{IntermediateRepresentation::REGISTER_DIRECT,IntermediateRepresentation::IRregToIndex(IntermediateRepresentation::R2, IntermediateRepresentation::QWORD),
						0});
					break;

				case 4:
					firstBB->add_IRInstr(IntermediateRepresentation::MOVE, addr,
						IntermediateRepresentation::NULL_ADDRESS,
						IntermediateRepresentation::Address{IntermediateRepresentation::REGISTER_DIRECT,IntermediateRepresentation::IRregToIndex(IntermediateRepresentation::R8, IntermediateRepresentation::QWORD),
						0});
					break;

				case 5:
					firstBB->add_IRInstr(IntermediateRepresentation::MOVE, addr,
						IntermediateRepresentation::NULL_ADDRESS,
						IntermediateRepresentation::Address{IntermediateRepresentation::REGISTER_DIRECT,IntermediateRepresentation::IRregToIndex(IntermediateRepresentation::R9, IntermediateRepresentation::QWORD),
						0});
					break;

				default:
					firstBB->add_IRInstr(IntermediateRepresentation::PUSH, IntermediateRepresentation::NULL_ADDRESS, IntermediateRepresentation::NULL_ADDRESS, addr);
					break;
			}

			counter++;
		}
	}
	firstBB->add_IRInstr(IntermediateRepresentation::CALL, IntermediateRepresentation::NULL_ADDRESS, IntermediateRepresentation::NULL_ADDRESS, IntermediateRepresentation::NULL_ADDRESS, *functionName);
	switch (this->getType().getTypeValue()) {
	default:
	case VOID:
		addr = IntermediateRepresentation::NULL_ADDRESS;
		break;
	case CHAR:
		addr.type = IntermediateRepresentation::REGISTER_DIRECT;
		addr.addr = IntermediateRepresentation::IRregToIndex(IntermediateRepresentation::R0, IntermediateRepresentation::BYTE);
		addr.offset = 0;
		break;
	case INT32:
		addr.type = IntermediateRepresentation::REGISTER_DIRECT;
		addr.addr = IntermediateRepresentation::IRregToIndex(IntermediateRepresentation::R0, IntermediateRepresentation::DWORD);
		addr.offset = 0;
		break;
	case INT64:
		addr.type = IntermediateRepresentation::REGISTER_DIRECT;
		addr.addr = IntermediateRepresentation::IRregToIndex(IntermediateRepresentation::R0, IntermediateRepresentation::QWORD);
		addr.offset = 0;
		break;
	}
    return addr;
}

bool FunctionEvaluation::verifyAndUpdateType(){
#ifdef DETAIL
	cout << "-- verifyAndUpdateType FunctionEvaluation --" << endl;
#endif

	bool correct = true;

	if(parameters!=nullptr){
		list<Types>* currentParametersTypes = new list<Types>();

        for (std::list<Expression*>::iterator expr = parameters->begin(); expr != parameters->end(); expr++)
        {
            if ((*expr)->verifyAndUpdateType())
            {
                currentParametersTypes->push_back((*expr)->getType());
            }
            else{
                currentParametersTypes->push_back(Types(VOID));
            }
        }

        list<Types>::iterator it2 = currentParametersTypes->begin();
        int needed = 0;
        int given = 0;
        bool cont = true;

        if(parametersTypes != nullptr){
            list<Types>::iterator it1 = parametersTypes->begin();

            while(cont){
                if(*it1 != *it2){
                    correct = false;
                }
                needed++;
                given++;
                it1++;
                it2++;
                if(it1 == parametersTypes->end()){
                    cont = false;
                    while(it2 != currentParametersTypes->end()){
                        it2++;
                        given++;
                    }
                }
                if(it2 == currentParametersTypes->end()){
                    cont = false;
                    while(it1 != parametersTypes->end()){
                        it1++;
                        needed++;
                    }
                }
            }
            if(needed != given){
                correct = false;
                cerr << "ERROR on line "<< this->getLine() <<" wrong parameters on function : " << *functionName << endl;
            }
        }

		delete currentParametersTypes;
    }
	return correct;
}

std::string FunctionEvaluation::getName()
{
    return *functionName;
}

bool FunctionEvaluation::computeAndVerifySymbols(list<map<string,Symbole>*>* symbolTable){
#ifdef DETAIL
    cout << "-- computeAndVerifySymbols FunctionEvaluation --" << endl;
#endif
    bool correct = true;

    bool found = false;

    for(list<map<string,Symbole>*>::reverse_iterator lastLevel = symbolTable->rbegin() ; lastLevel != symbolTable->rend(); lastLevel++){

        map<string,Symbole>::iterator it = (*lastLevel)->find(*functionName);
        if(it != (*lastLevel)->end()){
            if(it->second.getType() == FUNCTION)
            {
                found = true;
                t = it->second.getTypage();
                parametersTypes = new list<Types>(it->second.getFunctionParameters()->begin(),it->second.getFunctionParameters()->end());
            }
        }
    }

    if((*functionName) == "putchar"){
        parametersTypes = new std::list<Types>();
        parametersTypes->push_back(Types(WILDCARD));
    } else if ((*functionName) == "getchar"){
        t = Types(CHAR);
        parametersTypes = new std::list<Types>();
    }

    if(!found && *functionName != "putchar" && *functionName != "getchar"){
        correct = false;
        cerr << "ERROR on line "<< this->getLine() <<" use of undefined function : " << *functionName << endl;
    }

    for (std::list<Expression*>::iterator expr = parameters->begin(); expr != parameters->end(); expr++)
    {
        if (!(*expr)->computeAndVerifySymbols(symbolTable))
        {
            correct = false;
        }
    }
    return correct;
}

// ----------------------------- Constructors ----------------------------------

FunctionEvaluation::FunctionEvaluation(std::string * name, list<Expression*>* param, int line)
    :functionName(name),parameters(param),Expression(line)
{
#ifdef DEBUG
    cout << "-- Constructor FunctionEvaluation --" << endl;
#endif

	//parametersTypes = new std::list<Types>();
}

// ------------------------------ Destructor -----------------------------------

FunctionEvaluation::~FunctionEvaluation()
{
#ifdef DEBUG
    cout << "-- Destructor FunctionEvaluation --" << endl;
#endif
    delete functionName;
    while(!parameters->empty())
	{
		delete parameters->back();
        parameters->pop_back();
	}
    delete parameters;
    delete parametersTypes;
}
