#include "Int64Value.h"

using namespace Model;
using namespace std;


IntermediateRepresentation::Address Int64Value::buildIR(IntermediateRepresentation::BasicBlock *firstBB, std::string label)
{
	IntermediateRepresentation::Address cst;
	cst.type = IntermediateRepresentation::CONSTANT;
	cst.addr = static_cast<int>(this->value);
	cst.offset = 0;
	return cst;
}

size_t Int64Value::getValue()
{
	return static_cast<size_t>(value);
}

// ----------------------------- Constructors ----------------------------------

Int64Value::Int64Value(int64_t val, int line)
:value(val),Value(line)
{
  t = Types(INT64);
  #ifdef DEBUG
  cout << "-- Constructor Int64Value --" << endl;
  #endif
}

// ------------------------------ Destructor -----------------------------------

Int64Value::~Int64Value()
{
  #ifdef DEBUG
  cout << "-- Destructor Int64Value --" << endl;
  #endif
}
