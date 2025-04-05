#include "Interpreter.h"
#include "Timer/Timer.h"

const char* PROGRAM_FILE = "Bytecodes/Program.qlubyte";

int main()
{
	Timer::Get().RecordStartTime();
	
	Interpreter interpreter(PROGRAM_FILE);
	interpreter.Run();
	
	Timer::Get().RecordEndTime();
	std::cin.get();
}