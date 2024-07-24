#ifndef SERVER_HPP
#define SERVER_HPP

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
constexpr int PORT = 12345;
constexpr int BUFFER = 1024;

class Server {
public:
    Server();
    ~Server();
    void InitializeWinsock();
    void CreateSocket();
    void BindSocket();
    void StartListening();
    void HandleConnections();
    void DisplayActiveClients();
    void Start();

private:
    int _server_fd;
    sockaddr_in _serverAddr;
    fd_set _master;
};

#endif // SERVER_HPP
