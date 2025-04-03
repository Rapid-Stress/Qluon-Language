#include "Interpreter.h"

const char* PROGRAM_FILE = "Bytecodes/Program.qlubyte";

int main()
{
	Interpreter interpreter(PROGRAM_FILE);
	interpreter.Run();
}