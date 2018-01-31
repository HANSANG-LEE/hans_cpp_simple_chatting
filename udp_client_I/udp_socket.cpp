#include "stdafx.h"
#include "UDP_Socket.h"

UDP_Socket::UDP_Socket()
	: retval(0), server_addr_len(0)
{
	// AF_INET : IPv4 Internet Protocol
	// SOCK_DGRAM : UDP
	// IPPROTO_UDP : UDP
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (sock == INVALID_SOCKET)
		throw std::system_error(WSAGetLastError(), std::system_category(), "Error opening socket");
}

UDP_Socket::~UDP_Socket()
{
	closesocket(sock);
}

void UDP_Socket::RecvFrom(char* buffer, int buffer_size, int flags)
{
	server_addr_len = sizeof(server_addr);

	retval = recvfrom(
		sock,
		buffer,
		buffer_size,
		flags,
		(SOCKADDR*)&server_addr,
		&server_addr_len
	);

	if (retval == SOCKET_ERROR)
		throw std::system_error(WSAGetLastError(), std::system_category(), "recvfrom failed");

	buffer[retval] = 0;
}

void UDP_Socket::SendTo(const std::string& ip, USHORT port, char* buffer, int buffer_size)
{
	ZeroMemory(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;									// Family
	server_addr.sin_port = htons(port);								// Port
	server_addr.sin_addr.s_addr = inet_addr(ip.c_str());		// IP

	retval = sendto(
		sock,
		buffer,
		buffer_size,
		0,
		(SOCKADDR*)&server_addr,
		sizeof(server_addr)
	);

	if (retval == SOCKET_ERROR)
		throw std::system_error(WSAGetLastError(), std::system_category(), "sendto failed");
}