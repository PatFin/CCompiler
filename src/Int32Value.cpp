#include <iostream>

#include "Int32Value.h"

using namespace Model;
using namespace std;


size_t Int32Value::getValue()
{
    return static_cast<size_t>(value);
}

IntermediateRepresentation::Address Int32Value::buildIR(IntermediateRepresentation::BasicBlock *firstBB, std::string label)
{
  cout << "-- buildIR for Int32Value --" << endl;
	IntermediateRepresentation::Address cst;
	cst.type = IntermediateRepresentation::CONSTANT;
	cst.addr = static_cast<int>(this->value);
	cst.offset = 0;
	return cst;
}

// ----------------------------- Constructors ----------------------------------

Int32Value::Int32Value(int32_t val, int line)
    :value(val),Value(line)
{
	t = Types(INT32);
#ifdef DEBUG
    cout << "-- Constructor Int32Value --" << endl;
#endif
}

// ------------------------------ Destructor -----------------------------------

Int32Value::~Int32Value()
{
#ifdef DEBUG
    cout << "-- Destructor Int32Value --" << endl;
#endif
}
