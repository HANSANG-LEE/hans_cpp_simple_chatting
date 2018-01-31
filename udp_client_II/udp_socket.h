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
	void RecvFrom(char* buffer, int buffer_size, int flags = 0);
	void SendTo(const std::string& ip, USHORT port, char* buffer, int buffer_size);

private:
	int retval;
	SOCKET sock;
	SOCKADDR_IN server_addr;
	int server_addr_len;
};