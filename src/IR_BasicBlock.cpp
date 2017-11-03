#include "IR_BasicBlock.h"
#include "IR_CFG.h"

using namespace IntermediateRepresentation;

//------------------------------ IR construction Method --------------------------

void BasicBlock::add_IRInstr(
		InstructionType op,
		Address op1,
		Address op2,
		Address dest, std::string jmpLabel)
{
	IRInstruction* instr = new IRInstruction(op, op1, op2, dest, jmpLabel);
	instr->setBB(this);
	this->instrs.push_back(instr);
}

std::string BasicBlock::getLabel()
{
	return label;
}

//------------------------------ x86 Assembly code generation Method --------------------------
void BasicBlock::gen_x86asm(std::ostream &o) {
	o << this->label << ":" << std::endl;
	for (unsigned int i = 0; i < this->instrs.size(); i++) {
		this->instrs.at(i)->gen_x86asm(o);
	}
	std::string jpop;
	if (this->exitTrue != nullptr)
	{
		if(this->exitFalse != nullptr)
		{
			switch (this->instrs.at(this->instrs.size() - 1)->getType()) {
			default:
			case COMP_EQ:
				jpop = "JE";
				break;
			case COMP_INFEQ:
				jpop = "JBE";
				break;
			case COMP_SUPEQ:
				jpop = "JGE";
				break;
			case COMP_DIFF:
				jpop = "JNE";
				break;
			case COMP_SUP:
				jpop = "JG";
				break;
			case COMP_INF:
				jpop = "JB";
				break;
			}
			o << '\t' << jpop << ' ' << this->exitTrue->label << std::endl;
			o << "\tJMP " << this->exitFalse->label << std::endl;
		}
		else
		{
			o << "\tJMP " << this->exitTrue->label << std::endl;
		}

	}
}

//------------------------------ Setter and Getter --------------------------

CFG* BasicBlock::getCfg()
{
	return cfg;
}

void BasicBlock::setExitT(BasicBlock* exitT)
{
	exitTrue = exitT;
}

void BasicBlock::setExitF(BasicBlock* exitF)
{
	exitFalse = exitF;
}

BasicBlock* BasicBlock::getThen()
{
	return exitTrue;
}

BasicBlock* BasicBlock::getElse()
{
	return exitFalse;
}

//------------------------------ Constructor and Destructor --------------------------

BasicBlock::BasicBlock(CFG* parent_cfg, std::string entry_label) :
		exitTrue(nullptr), exitFalse(nullptr),
		cfg(parent_cfg), label(entry_label)
{
	#ifdef DEBUG
			std::cout << "-- Constructor BasicBlock--" << std::endl;
	#endif
}

BasicBlock::~BasicBlock()
{
	#ifdef DEBUG
			std::cout << "-- Destructor BasicBlock --" << std::endl;
	#endif
	for(IRInstruction* instr: instrs)
	{
		delete instr;
	}
}
