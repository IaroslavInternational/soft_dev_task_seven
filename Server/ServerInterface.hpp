#pragma once

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <iostream>
#include <fstream>
#include <string>
#include <experimental/filesystem>

#pragma comment(lib, "ws2_32.lib")

#include <WinSock2.h>

class ServerInterface
{
public:
	ServerInterface();
public:
	void Process();
private:
	void SendFile(SOCKET* socket, const std::string& file_name);
private:
	SOCKADDR_IN addr_info;
	SOCKET		s_listen;
	SOCKET      s_for_connect;
};