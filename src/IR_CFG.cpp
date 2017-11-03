#include "IR_CFG.h"
#include "Function.h"
using namespace IntermediateRepresentation;

size_t CFG::makeFrameSize() {
	size_t frameSize = fctAst->getTypes().getSize();
	for(const auto& symTypePair : this->SymbolType)
	{
		if (symTypePair.first.find("___tmp") != 0)
		{
			frameSize += symTypePair.second.getSize();
		}
	}
	return frameSize;
}

std::string CFG::astName() {
	return this->fctAst->getName();
}

//------------------------------ Symbol and Variable Managment Method --------------------------

void CFG::add_to_symbol_table(std::string name, Model::Types t)
{
	Address addr;
	addr.type = REGISTER_INDIRECT_OFFSET;
	addr.addr = IRregToIndex(BP, QWORD);

	addr.offset = this->nextFreeStackPlace;
	this->nextFreeStackPlace += static_cast<int>(t.getSize());
	this->SymbolType[name] = t;
	this->SymbolAddress[name] = addr;
}

std::string CFG::create_new_tempvar(Model::Types t)
{
	//we always put the temp result in the R9 register


	Address addr;
	RegAccessType at;
	addr.type = REGISTER_DIRECT;
	addr.offset = 0;
	switch (t.getTypeValue()) {
		default:
		case Model::VOID:
		case Model::CHAR:
			at = BYTE;
			break;
		case Model::INT32:
			at = DWORD;
			break;
		case Model::INT64:
			at = QWORD;
			break;
	}
	/*
	switch (this->nextTempVarPlace) {
		default:
		case 0:
			addr.addr = IRregToIndex(R8, at);
			this->nextTempVarPlace = 1;
			break;
		case 1:
			addr.addr = IRregToIndex(R9, at);
			this->nextTempVarPlace = 2;
			break;
		case 2:
			addr.addr = IRregToIndex(R10, at);
			this->nextTempVarPlace = 3;
			break;
		case 3:
			addr.addr = IRregToIndex(R11, at);
			this->nextTempVarPlace = 0;
			break;
	}*/
	addr.addr = IRregToIndex(R11, at);

	//Adding it to the symbol table
	std::string newVarName = "___tmp_" + std::to_string(++nextTempVarName);
	this->SymbolType[newVarName] = t;
	this->SymbolAddress[newVarName] = addr;
	return newVarName;
}

Address CFG::get_var_address(std::string name)
{
	if (this->SymbolAddress.find(name) == this->SymbolAddress.end()) {
		return BAD_ADDRESS;
	}
	return SymbolAddress[name];
}

Model::Types CFG::get_var_type(std::string name)
{
	return SymbolType[name];
}

//----------------------------- Basic Block Managment Method ------------------------------

BasicBlock* CFG::getCurrentBB()
{
	return current_bb;
}

BasicBlock* CFG::add_bb(BasicBlock* bb)
{
	bbs.push_back(bb);
	current_bb = bb;
	return current_bb;
}

std::string CFG::new_BB_name()
{
	return std::to_string(++nextBBnumber);
}

//------------------------------ Assembly code generation Method --------------------------

void CFG::gen_asm(std::ostream& o, Assembler::ASMDialect dialect) {
	switch (dialect) {
	case Assembler::X86:
		gen_x86asm(o);
		break;
	}
}

void CFG::gen_asm_epilogue(std::ostream& o, Assembler::ASMDialect dialect) {
	switch (dialect) {
	case Assembler::X86:
		gen_x86asm_epilogue(o);
		break;
	}
}

void CFG::gen_asm_prologue(std::ostream& o, Assembler::ASMDialect dialect) {
	switch (dialect) {
	case Assembler::X86:
		gen_x86asm_prologue(o);
		break;
	}
}

void CFG::gen_asm_opening(std::ostream& o, Assembler::ASMDialect dialect) {
	switch (dialect) {
	case Assembler::X86:
		gen_x86asm_opening(o);
		break;
	}
}

//------------------------------ x86 Assembly code generation Method --------------------------

void CFG::gen_x86asm_opening(std::ostream& o) {
	o << ".file \"<<stdin>>\"" << std::endl;
	o << ".text" << std::endl;
	o << ".globl main" << std::endl;
	o << std::endl;
}

void CFG::gen_x86asm_prologue(std::ostream& o) {
	o << ".type " << fctAst->getName() << ", @function" << std::endl;
	o << fctAst->getName() << ':' << std::endl;
	o << "\tpushq %rbp" << std::endl;
	o << "\tmovq %rsp, %rbp" << std::endl;
	o << "\tsubq $" << this->makeFrameSize() << ", %RSP" << std::endl;
}

void CFG::gen_x86asm_epilogue(std::ostream& o) {
	o << "\tleave" << std::endl ;
	o << "\tret" << std::endl;
}

void CFG::gen_x86asm(std::ostream& o)
{
	this->gen_x86asm_prologue(o);
	for (BasicBlock* bb : this->bbs) {
		bb->gen_x86asm(o);
	}
	this->gen_x86asm_epilogue(o);
}

//------------------------------ Constructor and Destructor ----------------------------

CFG::CFG(Model::Function* ast)
:fctAst(ast), nextFreeStackPlace(8), nextBBnumber(0), nextTempVarPlace(0), nextTempVarName(0)
{
	#ifdef DEBUG
	cout << "-- Constructor CFG --" << endl;
	#endif
	this->makeFrameSize();
}

CFG::~CFG()
{
	#ifdef DEBUG
	cout << "-- Destructor CFG --" << endl;
	#endif
	for(BasicBlock* bb: bbs)
	{
		delete bb;
	}
}
