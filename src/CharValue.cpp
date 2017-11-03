#include <iostream>

#include "CharValue.h"
#include "Types.h"
#include "IR_Instruction.h"
#include "IR_InstructionType.h"

using namespace Model;
using namespace std;


size_t CharValue::getValue()
{
    return static_cast<size_t>(value);
}

IntermediateRepresentation::Address CharValue::buildIR(IntermediateRepresentation::BasicBlock *firstBB, std::string label)
{
	IntermediateRepresentation::Address cst;
	cst.type = IntermediateRepresentation::CONSTANT;
	cst.addr = static_cast<int>(this->value);
	cst.offset = 0;

	return cst;
}

// ----------------------------- Constructors ----------------------------------

CharValue::CharValue(char val, int line)
    :value(val),Value(line)
{
	t = Types(CHAR);
#ifdef DEBUG
    cout << "-- Constructor CharValue --" << endl;
#endif
}

// ------------------------------ Destructor -----------------------------------

CharValue::~CharValue()
{
#ifdef DEBUG
    cout << "-- Destructor CharValue --" << endl;
#endif
}
