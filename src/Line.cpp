#include "Line.h"

using namespace Model;

int Line::getLine()
{
    return lineNumber;
}

// ----------------------------- Constructors ----------------------------------

Line::Line(int l):lineNumber(l){}

Line::Line(const Line& other):lineNumber(other.lineNumber){}

// ------------------------------ Destructor -----------------------------------

Line::~Line(){}
