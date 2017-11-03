#pragma once

namespace IntermediateRepresentation {

	/// @todo Add needed instruction types
	typedef enum {
		COMP_EQ,
		COMP_INFEQ,
		COMP_SUPEQ,
		COMP_DIFF,
		COMP_SUP,
		COMP_INF,

		OR,
		AND,
		NOT,

		LEFT_SHIFT,
		RIGHT_SHIFT,
		BAND,
		BOR,
		BXOR,
		BNOT,

		PLUS,
		MINUS,
		MUL,
		DIV,
		MODULUS,
		IDENT,
		NEG,

		PUTCHAR,
		GETCHAR,

		LEA,
		MOVE,
		NO_OP,

		POST_INC,
		POST_DEC,
		PRE_INC,
		PRE_DEC,

		PUSH,
		POP,

		SIMPLE_CMP,

		JUMP_EQ,
		JUMP_DIFF,
		JUMP_SUP,
		JUMP_INF,
		JUMP_SUPEQ,
		JUMP_INFEQ,
		JUMP,
		CALL,
		RETURN,
	} InstructionType;
}
