#include "ServerInterface.hpp"

ServerInterface::ServerInterface()
{
    WORD dllVer = MAKEWORD(2, 1);
    WSAData wsad;

    WSAStartup(dllVer, &wsad);

    memset(&addr_info, 0, sizeof(SOCKADDR_IN));

    addr_info.sin_port = htons(4321);
    addr_info.sin_family = AF_INET;

    s_listen = socket(AF_INET, SOCK_STREAM, 0);
    bind(s_listen, (sockaddr*)&addr_info, sizeof(addr_info));
    listen(s_listen, SOMAXCONN);

    std::cout << "** Server side **" << std::endl;
}

void ServerInterface::Process()
{
    int size_addr = sizeof(addr_info);
    s_for_connect = accept(s_listen, (sockaddr*)&addr_info, &size_addr);

    if (s_for_connect != 0)
    {
        std::cout << "Client is connceted"        << std::endl 
                  << "Enter file's name to send:" << std::endl;

        std::string path;
        std::getline(std::cin, path);

        SendFile(&s_for_connect, path);
    }
}

void ServerInterface::SendFile(SOCKET* socket, const std::string& file_name)
{
    std::fstream file;
    file.open(file_name, std::ios_base::in | std::ios_base::binary);

    if (file.is_open())
    {
        int file_size = std::experimental::filesystem::file_size(file_name) + 1;

        char* bytes = new char[file_size];

        file.read((char*)bytes, file_size);

        std::cout << "File size:\t" << file_size << std::endl;
        std::cout << "File name:\t" << file_name << std::endl;

        send(*socket, std::to_string(file_size).c_str(), 16, 0);
        send(*socket, file_name.c_str(), 32, 0);
        send(*socket, bytes, file_size, 0);

        delete[] bytes;

        std::cout << "File is sent" << std::endl;
    }
    else
    {
        std::cout << "Error while opening the file!" << std::endl;
    }

    file.close();
}
