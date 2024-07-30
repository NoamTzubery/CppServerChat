#define _CRT_SECURE_NO_WARNINGS
#include "Message.hpp"

// Constructor implementation
Message::Message(std::uint32_t size, std::uint64_t timestamp, const std::string& msg)
    : _size(size), _timestamp(timestamp) {
    strncpy(_message, msg.c_str(), BUFFER);
    _message[BUFFER - 1] = NULL_TERMINATOR; // Ensure null termination
}

// Method to convert message to string
std::string Message::toString() const {
    std::stringstream ss;
    ss << _size << SEPARATER;

    // Convert timestamp to time structure
    std::time_t time = _timestamp;
    std::tm* tm = std::localtime(&time);

    // Format time as HH:MM
    ss << std::setfill('0') << std::setw(TIME_VIEW_SIZE) << tm->tm_hour << ":"
        << std::setfill('0') << std::setw(TIME_VIEW_SIZE) << tm->tm_min << SEPARATER;

    ss << _message;
    return ss.str();
}
