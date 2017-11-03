# C Compiler project

Authors
==
- Alexandre Bento
- Rim El-Idrissi Mokdad
- Thibaut Fernandez
- Patrick Finnerty
- Alexis Fossart
- Florentin Mace-Roussel
- Benoit Renault

All (at the time of the project) 4th students at INSA Lyon - Computer Science and Information Technology department.

Building the program
==
`make all` or just `make` will do.
The executable is located in the bin directory : __/bin/CCompiler.exe__

You will find a simple explanation of how to use the program by symply running it without any argument or by using -v option.

Run the unit tests
--
You car run the unit tests by simply running the following command :
`make runtest`

The unit tests include the detection of several kinds of error and checking the associated error messages.

Sample test programs
==
In the *pres* directory, you will find several sample programs. To compile all of them and produce their executable, you can run the script `compile.sh`.
Among these files you will find :
* A simple putchar call
* A loop that displays the alphabet
* A recursive call that displays the alphabet
* A three for loops winded together displaying rows of characters
* A simple addition (which fails with our implementation)
* A fibonnacci sequence computation (which fails with our implementation)

Progression
==

What works ...
--
* Declaration of global variables (though not supported in the assembly generation)
* All the C operators (but the pointers and address operators)
* Errors with line numbers
* Static check of the program (unused variables ...) although this is always done. The -a option is no use.
* x86 assembly generation
* *Putchar* call
* While loops
* For loops
* If else control blocks
* Variable affectation


... and what doesn't
--
* Use of 'special characters' that start with a '\\' such as \\n
* Arrays
* The Div '/' and Modulus '%' operators assembly generation
* Complex tree expressions computations due to us not storing intermediate results in the stack
* Call to functions with more than 6 parameters (due to us not handling expressions properly)
* Return values
