//============================================================================
// Name        : CCompiler.cpp
// Author      :
// Version     :
// Copyright   :
// Description : Hello World in C, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string.h>

#include "Program.h"
#include "ASM.h"
#include "IR_CFG.h"

// getProgram defined in the bison generated code
extern bool getProgram(Model::Program **);

using namespace std;

void displayUsage ();

int main( int argc, char * argv[] )
{
	int returnValue = 0;
	//Detection of arguments
	bool versionArgument = false;
	bool compileArgument = false;
	bool staticAnalysisArgument = false;
	bool optimisationArgument = false;
	bool fileOutputGiven = false;

	char * fileOutputName;

	int argNumber = 1;
	while ( argNumber < argc ) {
		if ( strcmp ( argv[argNumber] , "-v" ) == 0 )
		{
			versionArgument = true;
#ifdef DETAIL
			cout << "Option -v detected" << endl;
#endif
		} else if ( strcmp ( argv[argNumber] , "-c" ) == 0 )
		{
			compileArgument = true;
#ifdef DETAIL
			cout << "Option -c detected" << endl;
#endif
		} else if ( strcmp ( argv[argNumber] , "-a" ) == 0 )
		{
			staticAnalysisArgument = true;
#ifdef DETAIL
			cout << "Option -a detected" << endl;
#endif
		} else if ( strcmp ( argv[argNumber] , "-o" ) == 0 )
		{
			optimisationArgument = true;
#ifdef DETAIL
			cout << "Option -o detected" << endl;
#endif
		} else
		{
#ifdef DETAIL
			cout << "File output name detected" << endl;
#endif
			fileOutputGiven = true;
			fileOutputName = argv[argNumber];
		}

		argNumber ++;
	}


	if ( versionArgument )
	{
		displayUsage();
	}

	if ( compileArgument && !fileOutputGiven )
	{
		cout << "No file output specified for assembly code generation" << endl;
		displayUsage();
	}

	//Building the Program representation
	Model::Program * prog;
	bool noSyntaxError = getProgram(&prog);

	if ( noSyntaxError )
	{
		bool symbolsOk = prog->verifyProgram();
		if ( symbolsOk && compileArgument )
		{
			ofstream fileOutput(fileOutputName);
			std::vector<IntermediateRepresentation::CFG*>* IR = prog->buildIR();
			IntermediateRepresentation::CFG::gen_asm_opening(fileOutput, Assembler::X86);
			for (IntermediateRepresentation::CFG* cfg : *IR) {
				cfg->gen_asm(fileOutput, Assembler::X86);
			}
			for (IntermediateRepresentation::CFG* cfg : *IR)
			{
				delete cfg;
			}
			delete IR;
		}
	}
	else
	{
		cout << "Compilation failed due to syntax errors : exiting with return value 1" << endl;
		returnValue = 1;
	}

	delete prog;

	return returnValue;
}

void displayUsage ()
{
	cout << "CCompiler program : almost a C compiler" << endl << endl;
	cout << "Usage:" << endl << endl;
	cout << "\t CCompiler -v\t\t\tShows this help page" << endl;
	cout << "\t CCompiler [OPTIONS] \tCompiles what is written to the stdin input file" << endl;

	cout << endl;
	cout << "OPTIONS:" << endl << endl;
	cout << "\t -v\t\t Shows this help page" << endl << endl;
	cout << "\t -c <file>\t Compiles the file to assembly language" << endl << endl;
	cout << "\t -a\t\t Performs a static analysis" << endl << endl;
	cout << "\t -o\t\t Performs various optimizations to the program" << endl << endl;

	cout << "This program was written by A.BENTO, R.EL-IDIRISSI MOKDAD, T.FERNANDEZ, P.FINNERTY, A.FOSSART, F.MACE--ROUSSSEL and B.RENAULT" << endl;
	cout << "They wish you a happy compiling !" << endl;
}
