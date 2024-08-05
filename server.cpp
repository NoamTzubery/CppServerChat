#include "server.hpp"
#include "Message.hpp"

Server::Server() {
    FD_ZERO(&_master);  // clear the set
}

Server::~Server() {
    WSACleanup();
}

void Server::initializeWinsock() {
    WSADATA ws;
    if (WSAStartup(MAKEWORD(MAJOR_VERSION, MINOR_VERSION), &ws) != 0) {
        throw std::runtime_error("WSA Failed to Initialize");
    }
    else {
        std::cout << "WSA opened Successfully\n";
    }
}

void Server::createSocket() {
    _server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_server_fd == INVALID_SOCKET) {
        throw std::runtime_error("Failed to Initialize the socket");
    }
    else {
        std::cout << "The socket opened Successfully\n";
    }
}

void Server::bindSocket() {
    _serverAddr.sin_family = AF_INET;
    _serverAddr.sin_port = htons(PORT);
    _serverAddr.sin_addr.s_addr = INADDR_ANY;

    int bindResult = bind(_server_fd, (sockaddr*)&_serverAddr, sizeof(sockaddr));
    if (bindResult == SOCKET_ERROR) {
        throw std::runtime_error("Failed to bind to local server");
    }
    else {
        std::cout << "Successfully bind to local port\n";
    }
}

void Server::startListening() {
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
std::string Server::receiveMessage(SOCKET client_socket) {
    uint32_t messageSize;
    int bytesReceived = recv(client_socket, reinterpret_cast<char*>(&messageSize), sizeof(messageSize), 0);
    if (bytesReceived == sizeof(messageSize)) {
        messageSize = ntohl(messageSize); // Convert to host byte order
        std::vector<char> buffer(messageSize);

        bytesReceived = recv(client_socket, buffer.data(), messageSize, 0);
        if (bytesReceived == messageSize) {
            return std::string(buffer.begin(), buffer.end());
        }
    }
    return "";
}

void Server::handleConnections() {
    while (true) {
        fd_set copy = _master;
        int activeSocketCount = select(FD_SETSIZE, &copy, nullptr, nullptr, nullptr);
        for (int i = 0; i < activeSocketCount; i++) {
            SOCKET sock = copy.fd_array[i];
            if (FD_ISSET(_server_fd, &copy)) {
                // Accept a new connection
                SOCKET client = accept(_server_fd, nullptr, nullptr);
                FD_SET(client, &_master);
                displayActiveClients();
            }
            else {
                // Receive a new message
                std::string messageContent = receiveMessage(sock);
                if (!messageContent.empty()) {
                    // Create a Message instance and convert it to string
                    Message message(messageContent);
                    std::string messageStr = message.toString();
                    // Send the formatted message to other clients
                    for (int i = 0; i < _master.fd_count; i++) {
                        SOCKET outSocket = _master.fd_array[i];
                        if (outSocket != _server_fd && outSocket != sock) {
                            uint32_t messageSize = htonl(static_cast<uint32_t>(messageStr.size()));
                            send(outSocket, reinterpret_cast<char*>(&messageSize), sizeof(messageSize), 0);
                            send(outSocket, messageStr.c_str(), messageStr.size(), 0);
                        }
                    }
                }
                else {
                    closesocket(sock);
                    FD_CLR(sock, &_master);
                    displayActiveClients();
                }
            }
        }
    }
}

void Server::displayActiveClients() {
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

void Server::start() {
    initializeWinsock();
    createSocket();
    bindSocket();
    startListening();
    handleConnections();
}
