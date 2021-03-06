/*
Author: Roman "Romop5" Dobias
Purpose: A simple demonstration of WriteProcessMemory and WinAPI calls for create a simple cheat

HOW DOES IT WORK ?

1. At first, we need to get access to game's process in order to change game's memory and thus change our ammo.
2. To find game's process, we will list all windows in your Windows and search for the one with contains "Mafia"
	That is done inside getMafiaWindows() function. You can verify the correctness of the found process ID (PID) 
	using Task Manager which lists all processes, run at the moment.
4. Now, we know ID of the game's process. Before we can do anything, we need to acquire an access to the process
	using OpenProcess() api call. Sometimes, espcially when your game runs as administrator, this may fail.
	In that case, run this cheat as an administrator to get the same rights as the game has.
5. Now we can access game's memory using Write/ReadProcessMemory()
*/

#include <iostream>
#include <regex>
#include <locale>
#include <codecvt>
#include <Windows.h>

struct FoundWindow
{
	HWND targetHWND;
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
	int returnedLength = GetWindowText(hwnd, windowsTitleBuffer, 254);
	//std::wregex e("Mafia");
	if (returnedLength > 0)
	{
		// print it
		//std::wcout << windowsTitleBuffer << std::endl;

		std::wstring titleString(windowsTitleBuffer);
		using convert_type = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_type, wchar_t> converter;
		std::string converted_str = converter.to_bytes(windowsTitleBuffer);
		
		// if Mafia is part of the string
		if (converted_str.find("Mafia") != std::wstring::npos)
		{
			//std::cout << "Found it !" << converted_str <<  std::endl;
			lpWindow->targetHWND = hwnd;
			return TRUE;
		}
	}
	return TRUE;
}

DWORD getMafiaProcessID()
{
	FoundWindow result;
	result.targetHWND = NULL;
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


int main()
{
	std::cout << "Hello from the other side" << std::endl;
	
	// Try to find PID for any window which has "Mafia" in titlebar
	DWORD pid = getMafiaProcessID();
	if (pid == NULL)
		return 1;

	std::cout << "PID: " << pid << std::endl;

	// Now open an access to process, so that we were able to manipulate with its memory
	HANDLE processHandle = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_WRITE, false, (DWORD) pid);
	
	DWORD newAmmo = 50;
	SIZE_T noWritten = 0;

	// NOTE: this address is dynamic - you have to find yours with Cheat Engine :)
	DWORD ammoAddress = 0x09E52C04;
	if (WriteProcessMemory(processHandle, (LPVOID)ammoAddress, &newAmmo, sizeof(DWORD), &noWritten) == 0)
	{
		std::cout << "Failed to change ammo :( - WriteProcessMemory has failed" << std::endl;
		return 1;
	}
	// Close access correctly and terminate successfully :)
	CloseHandle(processHandle);
	std::cout << "Done" << std::endl;
    return 0;
}
