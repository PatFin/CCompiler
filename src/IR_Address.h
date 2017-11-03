#pragma once

#include <iostream>


#include <cstdint>
#include <string>

#include "ASM.h"
#include "Register.h"

namespace IntermediateRepresentation {

	/**
	 * @brief How to interpret and Address struct
	 *
	 * @li @c REGISTER_DIRECT means that the address is a direct access to a register. @c offset is not used.
	 * @li @c MEMORY_DIRECT means that an access is performed to a constant address in memory. @c offset is not used.
	 * @li @c REGISTER_INDIRECT means that an access is performed to memroy at the address located in the register designated by @c addr. @c offset is not used.
	 * @li @c REGISTER_INDIRECT_OFFSET means that an access is performed to memroy at the address in the @c addr register plus @c offset.
	 * @li @c REGISTER_INDIRECT_SCALE_n means that an access is performed to memory according to the following scheme: @f$ %addr + %offset \times n @f$
	 *
	 * @note Each backend should have a representation between register address and actual assembler register name that allows it to create code identical to other backends.
	 */

	typedef enum {
		REGISTER_DIRECT,
		MEMORY_DIRECT,
		REGISTER_INDIRECT,
		REGISTER_INDIRECT_OFFSET,
		REGISTER_INDIRECT_SCALE_1,
		REGISTER_INDIRECT_SCALE_2,
		REGISTER_INDIRECT_SCALE_4,
		REGISTER_INDIRECT_SCALE_8,
		CONSTANT,
		NULL_ADDR
	} AddressType;

	/**
	 * @brief Definition of an address
	 *
	 * This struct contains information on an address that can easily be turned into asm.
	 *
	 */
	typedef struct Address {

		/**
		 * @brief How to interpret this struct
		 *
		 * @see AddressType
		 */
		AddressType type;

		/**
		 * @brief The principal address
		 *
		 * This is either a register index, a constant, or an address in memory.
		 *
		 * The register index works this way:
		 * @li The 2 least-significant bits are the access mode as defined in @c RegAccessType from <tt>Register.h</tt>
		 * @li The remaining bits are the register identifier as defined in @c Register from <tt>Register.h</tt>
		 *
		 * If it is a constant, or a memory address, all bits are used to store the value.
		 */
		int64_t addr;

		/**
		 * @brief The offset from the address
		 *
		 * This is an offset that is added to the principal address.
		 *
		 * This offset can be either a constant or a register index.
		 *
		 * If it is a register index, see @c addr for more information.
		 */
		int offset;

		Address& operator=(const Address& other){
			this->type = other.type;
			this->addr = other.addr;
			this->offset = other.offset;
			return *this;
		}

		bool operator!=(const Address& other){
			// std::cout << "( " << std::to_string(this->addr) << ", " << std::to_string(this->offset) << " ) || ( " << std::to_string(other.addr) << ", " << std::to_string(other.offset) << " )" << std::endl;
			if(this->type != other.type || this->addr != other.addr || this->offset != other.offset)
			{
				// std::cout << "Different" << std::endl;
				return true;
			}
			return false;
		}

	} Address;

	/**
	 * @brief Null address
	 *
	 * This address is to be used when an address is required, but will not be used.
	 *
	 * @note This constant should not be mistaken with @c BAD_ADDRESS
	 */
	const Address NULL_ADDRESS {NULL_ADDR, 0, 0};

	/**
	 * @brief Invalid address
	 *
	 * This address is to be returned to indicate an error has occured.
	 *
	 * @note This constant should not be mistaken with @c BAD_ADDRESS
	 */
	const Address BAD_ADDRESS {REGISTER_DIRECT, -1, 0};

	int IRregToIndex(Register reg, RegAccessType t);
	std::string regIndexToASM(int index, Assembler::ASMDialect dialect);
	std::string IRaddressToASM(Address a, Assembler::ASMDialect dialect);
	std::string regIndexTox86ASM(int index);
	std::string IRaddressTox86ASM(Address a);
}
