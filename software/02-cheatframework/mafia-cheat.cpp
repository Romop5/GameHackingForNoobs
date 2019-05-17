#include <iostream>
#include <Windows.h>
#include "cheatlib.h"

int main()
{
	std::cout << "This is Mafia Cheat ver. 0.1 noob-alpha" << std::endl;

	// Unit tests
	
	CheatLib::CheatGame game;

	CheatLib::MemoryAccessor ammunition(game, 0x55555);
	ammunition.write((DWORD) 5000);
	ammunition.get<DWORD>();
}
