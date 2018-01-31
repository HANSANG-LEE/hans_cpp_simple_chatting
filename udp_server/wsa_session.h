#pragma once

#include <iostream>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)

class WSA_Session
{
public:
	WSA_Session();
	virtual ~WSA_Session();

private:
	WSADATA wsa;
	int retval;
};