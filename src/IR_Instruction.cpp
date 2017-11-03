#include "IR_Instruction.h"

#include "Register.h"

using namespace IntermediateRepresentation;

InstructionType IRInstruction::getType() {
	return this->type;
}

/// @todo Implement method
void IRInstruction::gen_x86asm(std::ostream &o)
{
	bool resultAlreadyInDest = false;
	//We create the register towards destination
	IntermediateRepresentation::Address R10;
	R10.addr = IntermediateRepresentation::IRregToIndex(IntermediateRepresentation::R10, IntermediateRepresentation::QWORD);
	R10.type = IntermediateRepresentation::REGISTER_DIRECT;
	R10.offset = 0;
	IntermediateRepresentation::Address R11;
	R11.addr = IntermediateRepresentation::IRregToIndex(IntermediateRepresentation::R11, IntermediateRepresentation::QWORD);
	R11.type = IntermediateRepresentation::REGISTER_DIRECT;
	R11.offset = 0;

	//If the content of the operands are located in the memory, we load them to the registers R10
	//R10 happens all the time :
	if ( op1 != NULL_ADDRESS && type != LEA)
	{
		o << "\tmov " << IRaddressToASM(op1, Assembler::X86) << ", " << IRaddressToASM(R10, Assembler::X86) << std::endl;
	}

	if ( op2 != NULL_ADDRESS && op2 != R11 ) //If the second operand is already in R11, no need to move it
	{
		o << "\tmov " << IRaddressToASM(op2, Assembler::X86) << ", " << IRaddressToASM(R11, Assembler::X86) << std::endl;
	}
	std::string tmpstr;
	switch (type)
	{	//TODO check the COMP_% !!!
		case COMP_EQ :
			tmpstr = ".f_" + bb->getCfg()->astName() + "_calc_" + bb->getCfg()->new_BB_name();
			o << "\tcmp " << IRaddressToASM(R10, Assembler::X86) << ", " << IRaddressToASM(R11, Assembler::X86) << std::endl;
			o << "\tje " << tmpstr << "_t" << std::endl;
			o << "\tmov $0, " << IRaddressToASM(dest, Assembler::X86) << std::endl;
			o << "\tjmp " << tmpstr << "_e" << std::endl;
			o << tmpstr << "_t:" << std::endl;
			o << "\tmov $1, " << IRaddressToASM(dest, Assembler::X86) << std::endl;
			o << tmpstr << "_e:" << std::endl;
			resultAlreadyInDest = true;
			break;
		case COMP_INFEQ :
			tmpstr = ".f_" + bb->getCfg()->astName() + "_calc_" + bb->getCfg()->new_BB_name();
			o << "\tcmp " << IRaddressToASM(R10, Assembler::X86) << ", " << IRaddressToASM(R11, Assembler::X86) << std::endl;
			o << "\tjbe " << tmpstr << "_t" << std::endl;
			o << "\tmov $0, " << IRaddressToASM(dest, Assembler::X86) << std::endl;
			o << "\tjmp " << tmpstr << "_e" << std::endl;
			o << tmpstr << "_t:" << std::endl;
			o << "\tmov $1, " << IRaddressToASM(dest, Assembler::X86) << std::endl;
			o << tmpstr << "_e:" << std::endl;
			resultAlreadyInDest = true;
			break;
		case COMP_SUPEQ :
			tmpstr = ".f_" + bb->getCfg()->astName() + "_calc_" + bb->getCfg()->new_BB_name();
			o << "\tcmp " << IRaddressToASM(R10, Assembler::X86) << ", " << IRaddressToASM(R11, Assembler::X86) << std::endl;
			o << "\tjge " << tmpstr << "_t" << std::endl;
			o << "\tmov $0, " << IRaddressToASM(dest, Assembler::X86) << std::endl;
			o << "\tjmp " << tmpstr << "_e" << std::endl;
			o << tmpstr << "_t:" << std::endl;
			o << "\tmov $1, " << IRaddressToASM(dest, Assembler::X86) << std::endl;
			o << tmpstr << "_e:" << std::endl;
			resultAlreadyInDest = true;
			break;
		case COMP_DIFF :
			tmpstr = ".f_" + bb->getCfg()->astName() + "_calc_" + bb->getCfg()->new_BB_name();
			o << "\tcmp " << IRaddressToASM(R10, Assembler::X86) << ", " << IRaddressToASM(R11, Assembler::X86) << std::endl;
			o << "\tjne " << tmpstr << "_t" << std::endl;
			o << "\tmov $0, " << IRaddressToASM(dest, Assembler::X86) << std::endl;
			o << "\tjmp " << tmpstr << "_e" << std::endl;
			o << tmpstr << "_t:" << std::endl;
			o << "\tmov $1, " << IRaddressToASM(dest, Assembler::X86) << std::endl;
			o << tmpstr << "_e:" << std::endl;
			resultAlreadyInDest = true;
			break;
		case COMP_SUP :
			tmpstr = ".f_" + bb->getCfg()->astName() + "_calc_" + bb->getCfg()->new_BB_name();
			o << "\tcmp " << IRaddressToASM(R10, Assembler::X86) << ", " << IRaddressToASM(R11, Assembler::X86) << std::endl;
			o << "\tjg " << tmpstr << "_t" << std::endl;
			o << "\tmov $0, " << IRaddressToASM(dest, Assembler::X86) << std::endl;
			o << "\tjmp " << tmpstr << "_e" << std::endl;
			o << tmpstr << "_t:" << std::endl;
			o << "\tmov $1, " << IRaddressToASM(dest, Assembler::X86) << std::endl;
			o << tmpstr << "_e:" << std::endl;
			resultAlreadyInDest = true;
			break;
		case COMP_INF :
			tmpstr = ".f_" + bb->getCfg()->astName() + "_calc_" + bb->getCfg()->new_BB_name();
			o << "\tcmp " << IRaddressToASM(R10, Assembler::X86) << ", " << IRaddressToASM(R11, Assembler::X86) << std::endl;
			o << "\tjb " << tmpstr << "_t" << std::endl;
			o << "\tmov $0, " << IRaddressToASM(dest, Assembler::X86) << std::endl;
			o << "\tjmp " << tmpstr << "_e" << std::endl;
			o << tmpstr << "_t:" << std::endl;
			o << "\tmov $1, " << IRaddressToASM(dest, Assembler::X86) << std::endl;
			o << tmpstr << "_e:" << std::endl;
			resultAlreadyInDest = true;
			break;
		case AND :
			tmpstr = ".f_" + bb->getCfg()->astName() + "_andOp_" + bb->getCfg()->new_BB_name();
			o << "\tcmp $0, " << IRaddressToASM(R10, Assembler::X86) << std::endl;
			o << "\tje " << tmpstr << "_false" << std::endl;
			o << "\tcmp $0, " << IRaddressToASM(R11, Assembler::X86) << std::endl;
			o << "\tje " << tmpstr << "_false" << std::endl;
			o << "\tmov $1, " << IRaddressToASM(dest, Assembler::X86) << std::endl;
			o << "\tjmp " << tmpstr << "_fin" << std::endl;
			o << tmpstr << "_false:" << std::endl;
			o << "\tmov $0, " << IRaddressToASM(dest, Assembler::X86) << std::endl;
			o << tmpstr << "_fin:" << std::endl;
			resultAlreadyInDest = true;
			break;
		case OR :
			tmpstr = ".f_" + bb->getCfg()->astName() + "_orOp_" + bb->getCfg()->new_BB_name();
			o << "\tcmp $0, " << IRaddressToASM(R10, Assembler::X86) << std::endl;
			o << "\tjne " << tmpstr << "_true" << std::endl;
			o << "\tcmp $0, " << IRaddressToASM(R11, Assembler::X86) << std::endl;
			o << "\tje " << tmpstr << "_true" << std::endl;
			o << "\tmov $0, " << IRaddressToASM(dest, Assembler::X86) << std::endl;
			o << "\tjmp " << tmpstr << "_fin" << std::endl;
			o << tmpstr << "_true:" << std::endl;
			o << "\tmov $1, " << IRaddressToASM(dest, Assembler::X86) << std::endl;
			o << tmpstr << "_fin:" << std::endl;
			resultAlreadyInDest = true;
			break;
		case NOT :
			tmpstr = ".f_" + bb->getCfg()->astName() + "_calc_" + bb->getCfg()->new_BB_name();
			o << "\tcmp " << IRaddressToASM(R10, Assembler::X86) << ", $0" << std::endl;
			o << "\tjne " << tmpstr << "_t" << std::endl;
			o << "\tmov $0, " << IRaddressToASM(dest, Assembler::X86) << std::endl;
			o << "\tjmp " << tmpstr << "_e" << std::endl;
			o << tmpstr << "_t:" << std::endl;
			o << "\tmov $1, " << IRaddressToASM(dest, Assembler::X86) << std::endl;
			o << tmpstr << "_e:" << std::endl;
			resultAlreadyInDest = true;
			break;
		case LEFT_SHIFT :
			//o << "\tmov " << IRaddressToASM(R10, Assembler::X86) << ", " << IRaddressToASM(dest, Assembler::X86) << std::endl;
			//o << "\tmov " << IRaddressToASM(R10, Assembler::X86) << ", %rcx" << std::endl;
			o << "\tshl " << IRaddressToASM(R10, Assembler::X86) << ", " << IRaddressToASM(R11, Assembler::X86) << std::endl;
			o << "\tmov " << IRaddressToASM(R10, Assembler::X86) << ", " << IRaddressToASM(dest, Assembler::X86)<< std::endl;
			resultAlreadyInDest = true;
			break;
		case RIGHT_SHIFT :
			o << "\tshr " << IRaddressToASM(R10, Assembler::X86) << ", " << IRaddressToASM(R11, Assembler::X86) << std::endl;
			o << "\tmov " << IRaddressToASM(R10, Assembler::X86) << ", " << IRaddressToASM(dest, Assembler::X86)<< std::endl;
			resultAlreadyInDest = true;
			break;
		case BAND :
			o << "\tand " + IRaddressToASM(R10, Assembler::X86) << ", " << IRaddressToASM(R11, Assembler::X86) << std::endl;
			o << "\tmov " + IRaddressToASM(R10, Assembler::X86) << ", " << IRaddressToASM(dest, Assembler::X86) << std::endl;
			resultAlreadyInDest = true;
			break;
		case BOR :
			o << "\tor " + IRaddressToASM(R10, Assembler::X86) << ", " << IRaddressToASM(R11, Assembler::X86) << std::endl;
			o << "\tmov " + IRaddressToASM(R10, Assembler::X86) << ", " << IRaddressToASM(dest, Assembler::X86) << std::endl;
			resultAlreadyInDest = true;
			break;
		case BXOR :
			o << "\txor " + IRaddressToASM(R10, Assembler::X86) << ", " << IRaddressToASM(R11, Assembler::X86) << std::endl;
			o << "\tmov " + IRaddressToASM(R10, Assembler::X86) << ", " << IRaddressToASM(dest, Assembler::X86) << std::endl;
			resultAlreadyInDest = true;
			break;
		case BNOT :
			o << "\tnot " + IRaddressToASM(R10, Assembler::X86) << std::endl;
			o << "\tmov " + IRaddressToASM(R10, Assembler::X86) << ", " << IRaddressToASM(dest, Assembler::X86) << std::endl;
			resultAlreadyInDest = true;
			break;
		case PLUS :
			o << "\tadd " + IRaddressToASM(R10, Assembler::X86) << ", " << IRaddressToASM(R11, Assembler::X86) << std::endl;
			break;
		case MINUS :
			o << "\tsub " + IRaddressToASM(R10, Assembler::X86) << ", " << IRaddressToASM(R11, Assembler::X86) << std::endl;
			break;
		case MUL :
			o << "\timul " << IRaddressToASM(R10, Assembler::X86) << ", " << IRaddressToASM(R11, Assembler::X86) << std::endl;
			break;
		case DIV :
			o << "\tmov $0, %rdx" << std::endl;
			o << "\tmov " << IRaddressToASM(R10, Assembler::X86) << ", %rax" << std::endl;
			o << "\tcqto" << std::endl;
			o << "\tidiv " << IRaddressToASM(R11, Assembler::X86) << std::endl;
			o << "\tmov %rax, " << IRaddressToASM(dest, Assembler::X86) << std::endl;
			resultAlreadyInDest = true;
			break;
		case MODULUS :
			o << "\tmov $0, %rdx" << std::endl;
			o << "\tmov " << IRaddressToASM(R10, Assembler::X86) << ", %rax" << std::endl;
			o << "\tcqto" << std::endl;
			o << "\tidiv " << IRaddressToASM(R11, Assembler::X86) << std::endl;
			o << "\tmov %rdx, " << IRaddressToASM(dest, Assembler::X86) << std::endl;
			resultAlreadyInDest = true;
			break;
		case IDENT :
			// DO NOTHING
			break;
		case NEG :
			o << "\tneg " << IRaddressToASM(R10, Assembler::X86) << std::endl;
			break;
		case PUTCHAR :
			o << "\t\t//putchar" << std::endl;
			break;
		case GETCHAR :
			o << "\t\t//getchar" << std::endl;
			break;
		case LEA :
			o << "\tlea " + IRaddressToASM(op1, Assembler::X86) + ", " + IRaddressToASM(dest, Assembler::X86) << std::endl;
			resultAlreadyInDest = true;
			break;
		case MOVE :
			o << "\tmov " << IRaddressToASM(R10, Assembler::X86) << ", " << IRaddressToASM(dest, Assembler::X86) << std::endl;
			resultAlreadyInDest = true;
			break;
		case NO_OP :
			o << "\tnop" << std::endl;
			resultAlreadyInDest = true;
			break;
		case POST_INC :
			o << "\tinc " << IRaddressToASM(R10, Assembler::X86) << std::endl;
			o << "\tmov " << IRaddressToASM(R10, Assembler::X86) << ", " << IRaddressToASM(dest, Assembler::X86) << std::endl;
			resultAlreadyInDest = true;
			break;
		case POST_DEC :
			o << "\tdec " << IRaddressToASM(R10, Assembler::X86) << std::endl;
			o << "\tmov " << IRaddressToASM(R10, Assembler::X86) << ", " << IRaddressToASM(dest, Assembler::X86) << std::endl;
			resultAlreadyInDest = true;
			break;
		case PRE_INC : //TODO a bit more complex, let's shunt it for now
			//o << "\tadd " << IRaddressToASM(R10, Assembler::X86) << ", " << IRaddressToASM(dest, Assembler::X86) << std::endl;
			break;
		case PRE_DEC : //TODO a bit more complex, let's shunt it for now
			//o << "\tsub " << IRaddressToASM(R10, Assembler::X86) << ", " << IRaddressToASM(dest, Assembler::X86) << std::endl;
			break;
		case SIMPLE_CMP :
			o << "\tcmp " << IRaddressToASM(R10, Assembler::X86) << ", " << IRaddressToASM(R11, Assembler::X86) << std::endl;
			resultAlreadyInDest = true;
			break;
		case JUMP_EQ :
			o << "\tje " << oJmpLabel << std::endl;
			resultAlreadyInDest = true;
			break;
		case JUMP_DIFF :
			o << "\tjne " << oJmpLabel << std::endl;
			resultAlreadyInDest = true;
			break;
		case JUMP_SUP :
			o << "\tjg " << oJmpLabel << std::endl;
			resultAlreadyInDest = true;
			break;
		case JUMP_INF :
			o << "\tjb " << oJmpLabel << std::endl;
			resultAlreadyInDest = true;
			break;
		case JUMP_SUPEQ :
			o << "\tjge " << oJmpLabel << std::endl;
			resultAlreadyInDest = true;
			break;
		case JUMP_INFEQ :
			o << "\tjbe " << oJmpLabel << std::endl;
			resultAlreadyInDest = true;
			break;
		case JUMP :
			o << "\tjmp " << oJmpLabel << std::endl;
			resultAlreadyInDest = true;
			break;
		case CALL :
			o << "\tcall " << oJmpLabel << std::endl;
			resultAlreadyInDest = true;
			break;
		case RETURN :
			o << "\tmov " << IRaddressToASM(R10, Assembler::X86) << ", %rax" << std::endl;
			this->bb->getCfg()->gen_x86asm_epilogue(o);
			resultAlreadyInDest = true;
			break;
		case PUSH :
			o << "\tpush " << IRaddressToASM(dest, Assembler::X86) << std::endl;
			resultAlreadyInDest = true;
			break;
		case POP :
			o << "\tpop " << IRaddressToASM(dest, Assembler::X86) << std::endl;
			resultAlreadyInDest = true;
			break;
		default :
			o << "\t\t//default" << std::endl;
			resultAlreadyInDest = true;
			break;
		}

		if ( !resultAlreadyInDest && dest != R11 )
		{
			o << "\tmov " << IRaddressToASM(R11, Assembler::X86) << ", " << IRaddressToASM(dest, Assembler::X86) << std::endl;
		}
}

void IRInstruction::setBB(BasicBlock* bb_)
{
	if (this->bb == nullptr)
	{
		this->bb = bb_;
	}
}

BasicBlock* IRInstruction::getBB() const
{
	return this->bb;
}

IRInstruction::IRInstruction(InstructionType type_, Address op1_, Address op2_, Address dest_, std::string label)
		: bb(nullptr), type(type_), op1(op1_), op2(op2_), dest(dest_), oJmpLabel(label)
{
	#ifdef DEBUG
			std::cout << "-- Constructor IRInstruction --" << std::endl;
	#endif
}

IRInstruction::~IRInstruction()
{
	#ifdef DEBUG
			std::cout << "-- Destructor IRInstruction --" << std::endl;
	#endif
}
