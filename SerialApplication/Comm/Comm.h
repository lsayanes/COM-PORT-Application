
#pragma once

namespace comm
{

	struct Serial
	{
		std::string			name;
		int					baud;
		uint8_t				byteSize;		//NByte
		uint8_t				parity;			//Paridad
		uint8_t				stopBits;		//Bit de parada
		DWORD				binary;			//binary mode, no EOF check 
		DWORD				timeout;


		inline explicit Serial(
								const std::string& szName,
								int nBaud) :
						name{ szName },
						baud{ nBaud },
						byteSize{ 8 },
						parity{ 0 },
						stopBits{ ONESTOPBIT },
						binary{ TRUE },
						timeout{ MAXDWORD },
						m_dcb{},
						m_hFd{ nullptr }
		{
		}


		Serial(const Serial&) = delete;
		Serial(Serial&&) = delete;
		Serial& operator=(const Serial&) = delete;
		Serial& operator=(Serial&&) = delete;


		inline virtual ~Serial()
		{
			close();
		}


		bool open();
		void close();
		uint16_t write(void* pBuff, uint16_t wSize) const;
		uint16_t read(void* pOut, uint16_t wMaxOut) const;


		inline bool isOpen() const { return m_hFd?true:false; };


	private:
		DCB					m_dcb;
		HANDLE				m_hFd;

	};

}//comm
