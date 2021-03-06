// client_main_II.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)

#include "WSA_Session.h"
#include "UDP_Socket.h"

#include <time.h>

#define BUFF_SIZE 1024
#define IP "127.0.0.1"
#define PORT 9500

int _tmain(int argc, _TCHAR argv[])
{
	try
	{
		WSA_Session wsa;
		UDP_Socket socket;
		char buffer[BUFF_SIZE] = "";

		std::cout << "::Client II Side" << std::endl;

		while (true)
		{
			// Send data to server
			std::cout << "::Enter your message : ";
			if (fgets(buffer, sizeof(buffer), stdin) == NULL)
				break;
			socket.SendTo(IP, PORT, buffer, strlen(buffer));

			// Buffer memory clear
			memset(&buffer, NULL, sizeof(buffer));

			// Receive data from server
			socket.RecvFrom(buffer, sizeof(buffer), 0);

			// Show Data
			std::cout << "::Message : " << buffer << std::endl;
		}
	}
	catch (std::system_error& e)
	{
		std::cout << e.what();
	}

	return 0;
}

