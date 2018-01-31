#include "stdafx.h"
#include "UDP_Socket.h"

UDP_Socket::UDP_Socket()
	: retval(0), client_addr_len(0)
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

void UDP_Socket::Bind(USHORT port)
{
	// Server Socket
	ZeroMemory(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;									// Family
	server_addr.sin_port = htons(port);								// Port
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);		// IP

	retval = bind(sock, (SOCKADDR*)&server_addr, sizeof(server_addr));

	if (retval == SOCKET_ERROR)
		throw std::system_error(WSAGetLastError(), std::system_category(), "Bind failed");
}

sockaddr_in UDP_Socket::RecvFrom(char* buffer, int buffer_size, int flags)
{
	client_addr_len = sizeof(client_addr);

	retval = recvfrom(
		sock,
		buffer,
		buffer_size,
		flags,
		(SOCKADDR*)&client_addr,
		&client_addr_len
	);

	if (retval == SOCKET_ERROR)
		throw std::system_error(WSAGetLastError(), std::system_category(), "recvfrom failed");

	buffer[retval] = 0;

	return client_addr;
}

void UDP_Socket::SendTo(sockaddr_in addr, char* buffer, int buffer_size)
{
	retval = sendto(
		sock,
		buffer,
		buffer_size,
		0,
		(SOCKADDR*)&addr,
		sizeof(addr)
	);

	if (retval == SOCKET_ERROR)
		throw std::system_error(WSAGetLastError(), std::system_category(), "sendto failed");
}