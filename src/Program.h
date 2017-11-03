#pragma once

/**
 * @file
 *
 * @brief Class definition for Program
 *
 * This file contains the class and friend functions definition for Program.
 *
 */

#include <list>
#include "Function.h"
#include "DeclarationInstruction.h"
#include "IR_CFG.h"

/**
 * @brief Memory representation of the compiled program
 *
 * This namespace contains the classes necessary to create the memory representation
 * of the compiled program.
 *
 * These classes mostly represent the instructions and expressions
 * that can be understood by the compiler.
 */
namespace Model {
	/**
	 * @brief Representation of the global program
	 *
	 * This class represents the entire program. The program is defined as a collection
	 * of functions and global variable decalrations.
	 */
	class Program {
	private:
		/**
		 * @brief The collection of functions that constitute the program
		 *
		 * This collection must contain at lest the @c main function
		 * in order for the compiled program to have an entry point.
		 */
		std::list<Function*> functions;

		/**
		 * @brief The global variables of the program
		 *
		 * This collection contains the globally-declared variables
		 * for the compiled program. It can be empty.
		 */
		std::list<DeclarationInstruction*> globals;

		bool verifyExpressionsTypes();
		bool computeSymbolTable();
	public:
		/**
		 *
		 */
		void addFunction(Function *);

		/**
		 *
		 */
		void addGlobalDeclaration(DeclarationInstruction *);


		std::vector<IntermediateRepresentation::CFG*>* buildIR();

		bool verifyProgram();

		/**
		 * @brief Default constructor for this class
		 *
		 * This constructor will created a basic instance of this class
		 * while initializing its attributes.
		 */
		Program();

		/**
		 * @brief Default destructor for this class
		 *
		 * This destructor will perform the necessary cleanup operations
		 * upon destruction of an instance of this class.
		 */
		virtual ~Program();
	};
}
