#pragma once

#include <iostream>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)

class UDP_Socket
{
public:
	UDP_Socket();
	virtual ~UDP_Socket();

public:
	void Bind(USHORT port);
	sockaddr_in RecvFrom(char* buffer, int buffer_size, int flags = 0);
	void SendTo(sockaddr_in addr, char* buffer, int buffer_size);
	
private:
	int retval;
	SOCKET sock;
	SOCKADDR_IN server_addr;
	SOCKADDR_IN client_addr;
	int client_addr_len;
};