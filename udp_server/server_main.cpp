// Server_Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <WinSock2.h>
#include <list>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)

#include "WSA_Session.h"
#include "UDP_Socket.h"

#define BUFF_SIZE 1024
#define PORT 9500

bool IsExistedAddr(std::list<sockaddr_in> &list, sockaddr_in addr);

int _tmain(int argc, _TCHAR argv[])
{
	try
	{
		WSA_Session wsa;
		UDP_Socket socket;
		char buffer[BUFF_SIZE] = "";
		std::list<sockaddr_in> client_addr_list;

		socket.Bind(PORT);

		std::cout << "::Server Side" << std::endl << std::endl;

		while (true)
		{
			// Receive data from clients
			sockaddr_in temp_addr = socket.RecvFrom(buffer, sizeof(buffer), 0);
			std::cout << "::1. Received Message from a client" << std::endl;

			if (client_addr_list.empty() == true)
			{
				std::cout << "::2. List is empty - ";
				client_addr_list.push_back(temp_addr);
				std::cout << "and it newly be added on list." << std::endl;
			}
			else
			{
				std::cout << "::3. List is not empty - ";
				if (IsExistedAddr(client_addr_list, temp_addr) == true)
				{
					std::cout << "but it already does exist." << std::endl;
				}
				else
				{
					client_addr_list.push_back(temp_addr);
					std::cout << "and it newly be added on list." << std::endl;
				}
			}

			// Show data on server screen
			std::cout << " [ " << inet_ntoa(temp_addr.sin_addr) << " / ";
			std::cout << ntohs(temp_addr.sin_port) << " ] ";
			std::cout << " Message : " << buffer << std::endl;

			// Resend data to clinets
			std::list<sockaddr_in>::iterator it;
			for (it = client_addr_list.begin(); it != client_addr_list.end(); ++it)
			{
				socket.SendTo(*it, buffer, strlen(buffer));
			}

			// Buffer memory clear
			memset(&buffer, NULL, sizeof(buffer));
		}
	}
	catch (std::system_error& e)
	{
		std::cout << e.what();
	}

	return 0;
}

bool IsExistedAddr(std::list<sockaddr_in> &list, sockaddr_in addr)
{
	std::list<sockaddr_in>::iterator it;
	for (it = list.begin(); it != list.end(); ++it)
	{
		if (((*it).sin_addr.s_addr == addr.sin_addr.s_addr)	// IP
			&& ((*it).sin_port == addr.sin_port))					// Port
		{
			return true;
		}
		else
		{
			if (it == list.end())
				return false;
		}
	}
}