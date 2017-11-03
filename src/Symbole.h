#pragma once

#include <string>
#include <list>
#include "Types.h"
#include "Line.h"

namespace Model {
	typedef enum {
		FUNCTION,
		VARIABLE
	} TYPESYMBOLE ;

	class Symbole : public Line{
		private:
			std::string name;
			TYPESYMBOLE type;
			Types t;
			std::list<Types> * functionParameters;
			bool used;

		public:
			std::list<Types> * getFunctionParameters();
			void addFunctionParameters(std::list<Types>*);
			TYPESYMBOLE getType();
			Types getTypage();
			void setUsed();
			bool isUsed();
			string getName();
			bool operator==(Symbole const&);
			Symbole(std::string,TYPESYMBOLE,Types, Line);
			virtual ~Symbole();
	};
}
