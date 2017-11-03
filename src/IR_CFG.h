#pragma once

#include <map>
#include <iostream>

#include "IR_Address.h"
#include "IR_BasicBlock.h"
#include "Register.h"
#include "Types.h"
#include "ASM.h"

namespace Model
{
	class Function;
}

namespace IntermediateRepresentation {

	class CFG {
		private:
		  	std::map <std::string, Model::Types> SymbolType; /**< part of the symbol table  */
			std::map <std::string, Address> SymbolAddress; /**< part of the symbol table  */

			int nextFreeStackPlace;
			int nextBBnumber; /**< just for naming */
			int nextTempVarPlace;
			int nextTempVarName;

			std::vector <BasicBlock*> bbs; /**< all the basic blocks of this CFG*/

			Model::Function* fctAst; /**< The AST this CFG comes from */

			BasicBlock* current_bb;
			size_t makeFrameSize();
		public:
			static void gen_asm_opening(std::ostream& o, Assembler::ASMDialect dialect);
			static void gen_x86asm_opening(std::ostream& o);

			void gen_asm(std::ostream& o, Assembler::ASMDialect dialect);
			void gen_x86asm(std::ostream& o);

			void gen_asm_epilogue(std::ostream& o, Assembler::ASMDialect dialect);
			void gen_asm_prologue(std::ostream& o, Assembler::ASMDialect dialect);

			void gen_x86asm_epilogue(std::ostream& o);
			void gen_x86asm_prologue(std::ostream& o);

			std::string astName();
			
			// symbol table methods
			void add_to_symbol_table(std::string name, Model::Types t);
			std::string create_new_tempvar(Model::Types t);
			Address get_var_address(std::string name);
			Model::Types get_var_type(std::string name);

			// basic block management
			BasicBlock* add_bb(BasicBlock* bb);
			std::string new_BB_name();
			BasicBlock* getCurrentBB();

			CFG(Model::Function* ast);
			~CFG();
	};
}
