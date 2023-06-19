#include "ClientInterface.hpp"

int main()
{
    ClientInterface client("127.0.0.1");

    client.Process();

    system("pause");

    return 0;
}
