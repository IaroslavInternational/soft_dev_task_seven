#include "ClientInterface.hpp"

ClientInterface::ClientInterface(const std::string& addr)
{
    WORD dllVer = MAKEWORD(2, 1);
    WSAData wsad;

    WSAStartup(dllVer, &wsad);

    memset(&addr_info, 0, sizeof(SOCKADDR_IN));

    addr_info.sin_addr.S_un.S_addr = inet_addr(addr.c_str());
    addr_info.sin_port = htons(4321);
    addr_info.sin_family = AF_INET;

    s_client = socket(AF_INET, SOCK_STREAM, 0);

    std::cout << "** Client side **" << std::endl;
}

void ClientInterface::Process()
{
    if (connect(s_client, (sockaddr*)&addr_info, sizeof(addr_info)) == 0)
    {
        std::cout << "Client is connected to Server" << std::endl;
        RecieveFile(&s_client);
    }
    else
    {
        std::cout << "Client is not connected to Server" << std::endl;
    }
}

void ClientInterface::RecieveFile(SOCKET* socket)
{
    char file_size_str[16];
    char file_name[16];

    recv(*socket, file_size_str, 16, 0);

    int file_size = std::atoi(file_size_str);
    char* bytes = new char[file_size];

    recv(*socket, file_name, 32, 0);

    std::fstream file;
    file.open(file_name, std::ios_base::out | std::ios_base::binary);

    std::cout << "File size:\t" << file_size << std::endl;
    std::cout << "File name:\t" << file_name << std::endl;

    if (file.is_open())
    {
        std::cout << "Saving file..." << std::endl;
        file.write(bytes, file_size);
        std::cout << "File saved" << std::endl;
    }
    else
    {
        std::cout << "Error while opening the file!" << std::endl;
    }

    delete[] bytes;

    file.close();
}
