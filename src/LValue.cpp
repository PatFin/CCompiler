#include <iostream>

#include "LValue.h"

using namespace std;
using namespace Model;


// ----------------------------- Constructors ----------------------------------

LValue::LValue(int line)
    :Expression(line)
{
#ifdef DEBUG
    cout << "-- Constructor LValue --" << endl;
#endif
}

LValue::LValue(Types type, int line)
:Expression(type, line)
{
    #ifdef DEBUG
    cout << "-- Constructor LValue --" << endl;
    #endif
}

// ------------------------------ Destructor -----------------------------------

LValue::~LValue()
{
#ifdef DEBUG
    cout << "-- Destructor LValue --" << endl;
#endif
}
