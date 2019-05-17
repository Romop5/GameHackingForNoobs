#include <iostream>
#include <Windows.h>
#include "cheatlib.h"

int main()
{
	std::cout << "This is Mafia Cheat ver. 0.1 noob-alpha" << std::endl;

	// Unit tests
	
	CheatLib::CheatGame game;
	game.bindToWindow("Mafia");
	std::cout << "ProcID " << game.getProcessID() << std::endl;
	std::cout << "Handle " << game.getHandle() << std::endl;

	if (game.isBinded() == false)
	{
		std::cout << "Failed to find window with game :(" << std::endl;
		return 1;
	}



	CheatLib::MemoryAccessor ammunition(game, 0x09E52C04);
	bool status = ammunition.write((DWORD) 5000);
	if (status == false)
	{
		std::cout << "Failed :(" << std::endl;
	}
	std::cout << "Done" << std::endl;
	//ammunition.get<DWORD>();
}
