#pragma once

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <experimental/filesystem>

#pragma comment(lib, "ws2_32.lib")

#include <WinSock2.h>

class ClientInterface
{
public:
	ClientInterface(const std::string& addr);
public:
	void Process();
private:
	void RecieveFile(SOCKET* socket);
private:
	SOCKADDR_IN addr_info;
	SOCKET      s_client;
};

