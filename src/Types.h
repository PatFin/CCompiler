#pragma once

#include <stdlib.h>

/**
 * @file
 *
 * @brief Enumeration definition for variable types
 *
 * This file contains the enumaretion for variable types.
 *
 * Currently our compiler only supports 3 variable types: @c char, @c int32_t and @c int64_t.
 * These and the @c void type are the only ones included in this enum.
 *
 */

#include <iostream>
#include <string>

using namespace std;

namespace Model {
	/**
	 * @brief The types supported by our compiler
	 *
	 * This enum lists the C types that our program will understand.
	 *
	 * Currently our compiler only supports 3 variable types: @c char, @c int32_t and @c int64_t.
	 * These and the @c void type are the only ones included in this enum.
	 */
	typedef enum {
		///@brief The @c void type, for functions and pointers only
		VOID,

		///@brief The @c char type, an 8-bit unsigned integer
		CHAR,

		///@brief The @c int32_t type, a 32-bit signed integer
		INT32,

		///@brief The @c int64_t type, a 64-bit signed integer
		INT64,
		WILDCARD
	} TYPES;

	class Types {
	private:
		TYPES t;
		size_t arraySize;
	public:
		size_t getSize() const;
		size_t getUnitSize() const;
		void setArraySize(size_t);
		TYPES getTypeValue() const;
		bool isVoid();
		bool operator!=(Types const&);
		bool operator==(Types const&);
		Types& operator=(Types const&);

		friend ostream& operator<< (ostream& os, const Types& t)
		{
			string text;

			switch(t.t)
			{
				case VOID:
					text = "void";
					break;

				case CHAR:
					text = "char";
					break;

				case INT32:
					text = "int32_t";
					break;
					
				case INT64:
					text = "int64_t";
					break;
					
				case WILDCARD:
					text = "wildcard";
			}

			os << text;
			return os;
		}

		Types();
		Types(TYPES, size_t aSize = 1);
		Types(Types const&);
		~Types();
	};
}
