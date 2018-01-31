#include "stdafx.h"
#include "WSA_Session.h"

WSA_Session::WSA_Session()
	: retval(0)
{
	{
		retval = WSAStartup(MAKEWORD(2, 2), &wsa);
		if (retval != 0)
		{
			throw std::system_error(WSAGetLastError(), std::system_category(), "WSAStartup() Failed");
		}
	}
}

WSA_Session::~WSA_Session()
{
	WSACleanup();
}
