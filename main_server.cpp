#include "server.hpp"
#include <iostream>
#include <exception>

int main() {
    try {
        Server server;
        server.start();
    }
    catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return  EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
