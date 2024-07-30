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
    /**
     * @brief Default constructor for the Server class.
     *
     * Initializes the file descriptor set used to manage client connections.
     */
    Server();

    /**
     * @brief Destructor for the Server class.
     *
     * Cleans up Winsock resources when the Server object is destroyed.
     */
    ~Server();

    /**
     * @brief Initializes the Winsock library.
     *
     * Sets up the Winsock API for network communication. Exits the program
     * if initialization fails.
     */
    void InitializeWinsock();

    /**
     * @brief Creates a TCP socket for the server.
     *
     * Configures a socket to use the TCP protocol and stores its file descriptor.
     * Exits the program if socket creation fails.
     */
    void CreateSocket();

    /**
     * @brief Binds the socket to a local address and port.
     *
     * Configures the socket to listen on a specified port and address.
     * Exits the program if binding fails.
     */
    void BindSocket();

    /**
     * @brief Starts listening for incoming client connections.
     *
     * Configures the socket to listen for client connections with a specified
     * backlog queue size. Exits the program if listening fails.
     */
    void StartListening();

    /**
     * @brief Handles incoming client connections and messages.
     *
     * Manages the main server loop, including accepting new connections,
     * receiving messages from clients, and broadcasting messages to all
     * connected clients. Handles disconnections and updates the list of
     * active clients.
     */
    void HandleConnections();

    /**
     * @brief Displays a list of active client connections.
     *
     * Prints the file descriptors of all currently connected clients.
     */
    void DisplayActiveClients();

    /**
     * @brief Starts the server and enters the main event loop.
     *
     * Initializes Winsock, creates a socket, binds it to a local address,
     * starts listening for connections, and then enters the main connection
     * handling loop.
     */
    void Start();

private:
    int _server_fd;                ///< File descriptor for the server socket.
    sockaddr_in _serverAddr;       ///< Address structure for the server.
    fd_set _master;                ///< Master file descriptor set for managing client connections.
    static constexpr uint32_t PORT = 12345; ///< Port number on which the server listens.
    static constexpr uint32_t BUFFER = 4025; ///< Buffer size for receiving messages.
    static constexpr int FAILED = -1; ///< When functions fails they send -1 so this is for checking that
    static constexpr int LISTENINGS_NUMBER ///< The numbers of pending connection the server can have 
};

#endif // SERVER_HPP
