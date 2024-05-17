

#include <Windows.h>

#include <string>
#include "Comm.h"


namespace comm
{
	bool Serial::open()
	{
		BOOL r = FALSE;

		if (INVALID_HANDLE_VALUE != (m_hFd = CreateFile(name.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL)))
		{
			memset(&m_dcb, 0, sizeof(m_dcb));
			if (TRUE == (r = GetCommState(m_hFd, &m_dcb)))
			{
				m_dcb.BaudRate = (DWORD)baud;		
				m_dcb.ByteSize = byteSize;		
				m_dcb.Parity = parity;
				m_dcb.StopBits = stopBits;
				m_dcb.fBinary = binary;			

				if (TRUE == (r = SetCommState(m_hFd, &m_dcb)))
				{
					if (TRUE == (r = SetCommMask(m_hFd, EV_RXCHAR)))
					{
						COMMTIMEOUTS timeouts = {0};

						timeouts.ReadIntervalTimeout = MAXDWORD;
						timeouts.ReadTotalTimeoutMultiplier = 0;
						timeouts.ReadTotalTimeoutConstant = 0;

						timeouts.WriteTotalTimeoutMultiplier = 1;
						timeouts.WriteTotalTimeoutConstant = 1;

						r = SetCommTimeouts(m_hFd, &timeouts);
					}
				}
			}
		}


		if (!r && m_hFd)
		{
			close();
			return false;
		}

		return true;
	}
	
	void Serial::close()
	{
		if(m_hFd)
			CloseHandle(m_hFd);

		m_hFd = nullptr;

	}


	uint16_t Serial::write(void* pBuff, uint16_t wSize) const
	{
		DWORD ret = 0;
		if (!WriteFile(m_hFd, pBuff, wSize, &ret, NULL))
		{
			if (ERROR_IO_PENDING == GetLastError())
				CancelIo(m_hFd);
		}
		
		return static_cast<uint16_t>(ret);
	}

	uint16_t Serial::read(void* pOut, uint16_t wMaxOut) const
	{
		DWORD dwRet = 0, dwRead;
		int nInt = 0;
		int nTime = 3;

		while (nInt < nTime && dwRet < wMaxOut)
		{
			ReadFile(m_hFd, (BYTE*)pOut + dwRet, 1, &dwRead, NULL);
			if (dwRead)
			{
				dwRet++;
				nInt = 0;
			}
			else
				nInt++;

		}

		return static_cast<uint16_t>(dwRet);
	}

} //comm



