#include <string>
#include "windowsutils.hpp"

namespace CheatLib {

class CheatGame
{
	public:
		CheatGame(): processID(NULL) {}

		bool bindToWindow(const std::string& windowName);

		bool bindToWindowContainingSubstring(const std::string& substring);

		// Determine if CheatGame class has been succesfully binded to running game
		bool isBinded() const;

		// Is game process still running
		bool isRunning() const;

		// Return handle
		HANDLE getHandle() const { return this->m_processHandle.get();}

		DWORD getProcessID() const { return this->processID; }
	private:
		// Handle, acquired using OpenProcess
		AutomaticHandle m_processHandle;
			
		// Process ID
		DWORD processID;

		bool openProcessHandle(DWORD processID);
};


/*
 * MemoryAccessor should provide more C++-stylish way of accessing game's memory.
 * 
 */
class MemoryAccessor
{
	public:
		MemoryAccessor(const CheatGame& game, DWORD address): m_game(game), m_address(address) {}
		// Write value of type T at address 
		template <class T>
		bool write(T& value) { return native_write(value, sizeof(T)); }
		// Write value of type T at address 
		template <class T>
		bool write(T value) { T tmp = value; return native_write(&tmp, sizeof(T)); }

		// Return value at address
		template <class T>
		T get() const { T tmp; native_read(&tmp, sizeof(T)); return tmp;}

		// Return accessor at address specified by current address
		// Eg. if current address is X and [X] = Y, then the new address will be Y+offset
		MemoryAccessor getPointerValue(DWORD offset = 0);

	private:
		const CheatGame& m_game;
		DWORD m_address;
		bool native_write(void* data, size_t sizeOfData) const;
		bool native_read(void* data, size_t sizeOfData) const;
};




} // CheatLib
