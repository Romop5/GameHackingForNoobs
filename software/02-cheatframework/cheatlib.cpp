#include <Windows.h>
#include "cheatlib.h"

#include <iostream>
#include <regex>
#include <locale>
#include <codecvt>
#include <Windows.h>



namespace CheatLib {

struct FoundWindow
{
	// OUT: the resulting HWND
	HWND targetHWND;
	// IN: the substring
	std::string searchedSubstring;
};



/*
	This function is called by EnumWindows() function. It is called for each
	window that is running currently in your system. Each time the function
	is called, the window handle (hwnd) is passed together with our FoundWindow structure.

	The function effectively searches for any window containing "Mafia" in title, and then
	sets FoundWindow's value.
*/

BOOL CALLBACK MyEnumProcedure(
	_In_ HWND   hwnd,
	_In_ LPARAM param
)
{
	FoundWindow* lpWindow = reinterpret_cast<FoundWindow*>(param);
	//std::cout << "Enum proc called with hwnd:" << hwnd << std::endl;
	// Get title
	wchar_t windowsTitleBuffer[255];
	int returnedLength = GetWindowTextW(hwnd, windowsTitleBuffer, 254);
	if (returnedLength > 0)
	{
		// print it
		//std::wcout << windowsTitleBuffer << std::endl;

		std::wstring titleString(windowsTitleBuffer);
		using convert_type = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_type, wchar_t> converter;
		std::string converted_str = converter.to_bytes(windowsTitleBuffer);
		
		// if Mafia is part of the string
		if (converted_str.find(lpWindow->searchedSubstring) != std::wstring::npos)
		{
			//std::cout << "Found it !" << converted_str <<  std::endl;
			lpWindow->targetHWND = hwnd;
			return TRUE;
		}
	}
	return TRUE;
}

DWORD searchForProcessWithWindowsContainingSubstring(std::string substr)
{
	FoundWindow result;
	result.targetHWND = NULL;
	result.searchedSubstring = substr;
	// List all windows in system, and process each window using MyEnumProcedure
	if (EnumWindows(MyEnumProcedure, reinterpret_cast<LPARAM>(&result)) == 0)
	{
		std::cout << "Failed to enumerate all windows !" << std::endl;
		return NULL;
	}
	// Here, we already know what's the window handle, now we will try to get
	// the process owning the window
	if (result.targetHWND == NULL)
	{
		std::cout << "Failed to find any windows containing Mafia" << std::endl;
		return NULL;
	}

	// Now find window's proccess ID 
	DWORD processID = NULL;
	if (GetWindowThreadProcessId(result.targetHWND, &processID) == 0)
	{
		std::cout << "Failed to get process ID from target windows !" << std::endl;
		return NULL;
	}
	return (DWORD) processID;
}


bool CheatGame::bindToWindow(const std::string& windowName)
{
	return this->bindToWindowContainingSubstring(windowName);
}

bool CheatGame::bindToWindowContainingSubstring(const std::string& substring)
{
	this->processID = searchForProcessWithWindowsContainingSubstring(substring);
	return (this->processID != NULL);
}

bool CheatGame::isBinded() const
{
	return (this->processID == 0);
}

bool CheatGame::isRunning() const
{
	// TODO
	return true;
}

/*
 * =======================================================
 * MemoryAccessor 
 * =======================================================
 */
MemoryAccessor MemoryAccessor::getPointerValue(DWORD offset)
{
	DWORD newAddress = NULL;
	this->native_read(&address, sizeof(DWORD));
	return MemoryAccessor(this->m_game, newAddress+offset);
}

bool MemoryAccessor::native_write(void* data, size_t sizeOfData) const
{
	auto processHandle = (this->m_game.getHandle());
	if(processHandle != NULL)
		return false;
	SIZE_T readBytesCount = 0;
	auto returnStatus = WriteProcessMemory(processHandle, reinterpret_cast<LPVOID>(this->m_address), data, sizeOfData, &readBytesCount);
	// if return value is positive and the same amount of data was written as provided by caller
	if(returnStatus > 0 && readBytesCount == sizeOfData)
		return true;
	return false;
}

bool MemoryAccessor::native_read(void* data, size_t sizeOfData) const
{
	auto processHandle = (this->m_game.getHandle());
	if(processHandle != NULL)
		return false;
	SIZE_T readBytesCount = 0;
	auto returnStatus = ReadProcessMemory(processHandle, reinterpret_cast<LPVOID>(this->m_address), data, sizeOfData, &readBytesCount);
	// if return value is positive and the same amount of data was written as provided by caller
	if(returnStatus > 0 && readBytesCount == sizeOfData)
		return true;
	return false;

}
}

