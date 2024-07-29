#ifndef SERVER_HPP
#define SERVER_HPP
#define _CRT_SECURE_NO_WARNINGS

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <ctime>  
#include <chrono>
#include <iomanip> 
#include <cstring>
#include <sstream>



#pragma comment(lib, "Ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS


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
    static constexpr uint32_t PORT = 12345;
    static constexpr uint32_t BUFFER = 1024;
};

#endif // SERVER_HPP
