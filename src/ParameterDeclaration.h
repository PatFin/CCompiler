#pragma once

/**
 * @file
 *
 * @brief Class definition for ParameterDeclaration
 *
 * This file contains the class and friend functions definition for ParameterDeclaration.
 *
 */

#include <string>
#include <list>
#include <map>

#include "Symbole.h"
#include "Types.h"
#include "Line.h"
#include "IR_BasicBlock.h"

using namespace std;

namespace Model {
	/**
	 * @brief Declaration of a function parameter
	 *
	 * This class represents a function parameter.
	 * It is defined by an identifier and a type.
	 */
	class ParameterDeclaration : public Line
	{
	private:
		Types* type;
		std::string* name;
	public:
		bool computeAndVerifySymbols(std::list<std::map<std::string,Symbole>*>*);
		inline size_t getTypeSize() { return this->type->getSize(); }
		virtual void buildIR(IntermediateRepresentation::BasicBlock *firstBB);
		std::string getName();

		Types getType();

		/**
		 * @brief Default constructor for this class
		 *
		 * This constructor will created a basic instance of this class
		 * while initializing its attributes.
		 */
		ParameterDeclaration(Types*, std::string *, int line);


		/**
		 * @brief Default destructor for this class
		 *
		 * This destructor will perform the necessary cleanup operations
		 * upon destruction of an instance of this class.
		 */
		virtual ~ParameterDeclaration();
	};
}
