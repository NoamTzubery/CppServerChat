#define _CRT_SECURE_NO_WARNINGS
#include "Message.hpp"
#include <chrono>

// Constructor implementation
Message::Message(const std::string& msg) {
    _size = static_cast<std::uint32_t>(msg.size());
    _timestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    _message = msg;
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
