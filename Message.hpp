#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include <cstdint>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <cstring>

class Message {
public:
    Message(std::uint32_t size, std::uint64_t timestamp, const std::string& msg);
    std::string toString() const;
private:
    std::uint32_t _size;
    std::uint64_t _timestamp;
    static constexpr uint32_t BUFFER = 1024;
    char _message[BUFFER];
};

#endif // MESSAGE_HPP
