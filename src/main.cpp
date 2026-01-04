#include "Engine.h"

// important early goals
// use RAII
// kernighan and ritchie convention
// hungarian notation
// use public, protected, private conventions.

int main() {
	Engine engine;
	engine.Run();
	engine.Exit();
	return 0;
}