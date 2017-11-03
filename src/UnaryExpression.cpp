#include <iostream>

#include "UnaryExpression.h"

using namespace Model;
using namespace std;


// ----------------------------- Constructors ----------------------------------

UnaryExpression::UnaryExpression(UNARYOPERATOR op, int line)
    :unaryOperator(op),Expression(line)
{
#ifdef DEBUG
    cout << "-- Constructor UnaryExpression --" << endl;
#endif
}

// ------------------------------ Destructor -----------------------------------

UnaryExpression::~UnaryExpression()
{
#ifdef DEBUG
    cout << "-- Destructor UnaryExpression --" << endl;
#endif
}
