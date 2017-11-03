#include <iostream>

#include "Value.h"

using namespace Model;
using namespace std;


bool Value::computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>* symbolTable)
{
    bool correct = true;

    return correct;
}

// ----------------------------- Constructors ----------------------------------

Value::Value(int line):
    Expression(line)
{
#ifdef DEBUG
    cout << "-- Constructor Value --" << endl;
#endif
}

// ------------------------------ Destructor -----------------------------------

Value::~Value()
{
#ifdef DEBUG
    cout << "-- Destructor Value --" << endl;
#endif
}
