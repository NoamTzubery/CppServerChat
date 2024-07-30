#include "server.hpp"
#include "Message.hpp"


Server::Server() {
    FD_ZERO(&_master);  // clear the set
}

Server::~Server() {
    WSACleanup();
}

void Server::InitializeWinsock() {
    WSADATA ws;
    if (WSAStartup(MAKEWORD(2, 2), &ws) == FAILED) {
        std::cout << "WSA Failed to Initialize\n";
        exit(1);
    }
    else {
        std::cout << "WSA opened Successfully\n";
    }
}

void Server::CreateSocket() {
    _server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_server_fd == FAILED) {
        std::cout << "Failed to Initialize the socket\n";
        exit(1);
    }
    else {
        std::cout << "The socket opened Successfully\n";
    }
}

void Server::BindSocket() {
    _serverAddr.sin_family = AF_INET;
    _serverAddr.sin_port = htons(PORT);
    _serverAddr.sin_addr.s_addr = INADDR_ANY;

    int bindResult = bind(_server_fd, (sockaddr*)&_serverAddr, sizeof(sockaddr));
    if (bindResult == FAILED) {
        std::cout << "Failed to bind to local server\n";
        exit(1);
    }
    else {
        std::cout << "Successfully bind to local port\n";
    }
}

void Server::StartListening() {
    int listenResult = listen(_server_fd, LISTENINGS_NUMBER);
    if (listenResult == FAILED) {
        std::cout << "Failed to listen to local server\n";
        exit(1);
    }
    else {
        std::cout << "Listening...\n";
    }
    FD_SET(_server_fd, &_master); // Add the listening socket to the set
}

void Server::HandleConnections() {
    while (true) {
        fd_set copy = _master;
        int activeSocketCount = select(FD_SETSIZE, &copy, nullptr, nullptr, nullptr);
        for (int i = 0; i < activeSocketCount; i++) {
            SOCKET sock = copy.fd_array[i];
            if (FD_ISSET(_server_fd, &copy)) {
                // Accept a new connection
                SOCKET client = accept(sock, (sockaddr*)&client, nullptr);
                FD_SET(client, &_master);
                DisplayActiveClients();
            } else {
                // Receive a new message
                char buf[BUFFER];
                memset(&buf, 0, BUFFER);
                int bytes = recv(sock, buf, BUFFER, 0);
                if (bytes == -1) {
                    closesocket(sock);
                    FD_CLR(sock, &_master);
                    DisplayActiveClients();
                } else {
                    // Create a Message instance and convert it to string
                    std::uint32_t messageSize = bytes;
                    std::uint64_t timestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                    std::string messageContent(buf, bytes);

                    Message message(messageSize, timestamp, messageContent);
                    std::string messageStr = message.toString();

                    // Send the formatted message to other clients
                    for (int i = 0; i < _master.fd_count; i++) {
                        SOCKET outSocket = _master.fd_array[i];
                        if (outSocket != _server_fd && outSocket != sock) {
                            send(outSocket, messageStr.c_str(), messageStr.size(), 0);
                        }
                    }
                }
            }
        }
    }
}


void Server::DisplayActiveClients() {
    std::cout << "The connected clients:\n";
    if (_master.fd_count == 0) {
        std::cout << "None\n";
    }
    for (int i = 0; i < _master.fd_count; i++) {
        if (_master.fd_array[i] != _server_fd) {
            std::cout << "Socket fd is: " << _master.fd_array[i] << std::endl;
        }
    }
}

void Server::Start() {
    InitializeWinsock();
    CreateSocket();
    BindSocket();
    StartListening();
    HandleConnections();
}
