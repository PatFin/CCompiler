#include <iostream>

#include "Types.h"

using namespace Model;
using namespace std;


size_t Types::getSize() const {
		return arraySize * 8;
}

bool Types::operator!=(Types const& other){
	if(this->t == WILDCARD || other.t == WILDCARD){
		return false;
	}
	bool ret =(this->t != other.t );
	if(ret){
		if(this->t == INT32 && other.t == INT64){
			ret = false;
		}
	}
	if(other.arraySize == 1){
		return ret;
	}
	return ret || arraySize != other.arraySize;
}

size_t Types::getUnitSize() const {
	return 8;
}

TYPES Types::getTypeValue() const
{
	return this->t;
}

bool Types::isVoid(){
	return t==VOID;
}

Types& Types::operator=(Types const& other){
	this->t = other.t;
	this->arraySize = other.arraySize;
	return *this;
}

bool Types::operator==(Types const& other){
	if(this->t == WILDCARD || other.t == WILDCARD){
		return true;
	}
	bool ret =(this->t == other.t );
	if(!ret){
		if(this->t == INT32 && other.t == INT64){
			ret = true;
		}
	}
	return ret && (arraySize == other.arraySize || other.arraySize == 1);
}


void Types::setArraySize(size_t aSize)
{
	arraySize = aSize;
}

// ----------------------------- Constructors ----------------------------------

Types::Types()
:t(VOID)
{
	#ifdef DEBUG
	cout << "-- Constructor Types --" << endl;
	#endif
}

Model::Types::Types(Model::Types const& type)
:t(type.t), arraySize(type.arraySize)
{
	#ifdef DEBUG
	cout << "-- Constructor Types --" << endl;
	#endif
}

Model::Types::Types(TYPES type, size_t aSize)
:t(type), arraySize(aSize)
{
	#ifdef DEBUG
	cout << "-- Constructor Types --" << endl;
	#endif
}

// ------------------------------ Destructor -----------------------------------

Model::Types::~Types()
{
	#ifdef DEBUG
	cout << "-- Destructor Types --" << endl;
	#endif
}
