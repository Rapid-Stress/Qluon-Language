#include "Interpreter.h"
#include "Timer/Timer.h"

const char* PROGRAM_FILE = "Bytecodes/Program.qlubyte";

int main()
{
	Timer::RecordStartTime();
	
	Interpreter interpreter(PROGRAM_FILE);
	interpreter.Run();
	
	Timer::RecordEndTime();
	std::cin.get();
}