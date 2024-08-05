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
#include <vector>

#pragma comment(lib, "Ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS

/**
 * @class Server
 * @brief Manages a network server using Winsock.
 *
 * This class encapsulates the functionality required to set up and manage a
 * network server, including initializing Winsock, creating and binding a
 * socket, and handling client connections.
 */
class Server {
public:

    Server();

    ~Server();
   
    /**
     * @brief Starts the server and enters the main event loop.
     *
     * Initializes Winsock, creates a socket, binds it to a local address,
     * starts listening for connections, and then enters the main connection
     * handling loop.
     */
    void start();

private:
    int _server_fd;                ///< File descriptor for the server socket.
    sockaddr_in _serverAddr;       ///< Address structure for the server.
    fd_set _master;                ///< Master file descriptor set for managing client connections.
    static constexpr auto PORT = 12345; ///< Port number on which the server listens.
    static constexpr auto FAILED = -1; ///< When functions fail they send -1 so this is for checking that.
    static constexpr auto LISTENINGS_NUMBER = 5; ///< The number of pending connections the server can have.
    static constexpr int MAJOR_VERSION = 2; ///< the version of winsocket
    static constexpr int MINOR_VERSION = 2; ///< the minor version of winsocket

    /**
     * @brief Receives a message from a client.
    *
    * First receives a 32-bit integer indicating the size of the incoming message,
    * then receives the actual message data.
    * @param client_socket The socket descriptor for the client connection.
    * @return A string containing the received message.
    */
    std::string receiveMessage(SOCKET client_socket);

    /**
     * @brief Initializes the Winsock library.
    *
     * Sets up the Winsock API for network communication. Exits the program
    * if initialization fails.
    */
    void initializeWinsock();

    /**
     * @brief Creates a TCP socket for the server.
     *
     * Configures a socket to use the TCP protocol and stores its file descriptor.
     * Exits the program if socket creation fails.
     */
    void createSocket();

    /**
     * @brief Binds the socket to a local address and port.
     *
     * Configures the socket to listen on a specified port and address.
     * Exits the program if binding fails.
     */
    void bindSocket();

    /**
     * @brief Starts listening for incoming client connections.
     *
     * Configures the socket to listen for client connections with a specified
     * backlog queue size. Exits the program if listening fails.
     */
    void startListening();

    /**
     * @brief Handles incoming client connections and messages.
     *
     * Manages the main server loop, including accepting new connections,
     * receiving messages from clients, and broadcasting messages to all
     * connected clients. Handles disconnections and updates the list of
     * active clients.
     */
    void handleConnections();

    /**
     * @brief Displays a list of active client connections.
     *
     * Prints the file descriptors of all currently connected clients.
     */
    void displayActiveClients();

};

#endif // SERVER_HPP
