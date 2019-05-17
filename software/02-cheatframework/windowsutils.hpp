// Needed for HANDLE
#include <WinNT.h>

class AutomaticHandle
{
	public:
		AutomaticHandle(): m_handle(nullptr) {}
		~AutomaticHandle() { CloseHandle(m_handle); }
		HANDLE get() const { return m_handle;}
		void set(HANDLE value) { m_handle = value; }
	private:
		HANDLE m_handle;
};
