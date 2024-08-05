#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include <cstdint>
#include <ctime>
#include <iomanip>
#include <sstream>

/**
 * @class Message
 * @brief Represents a message with a size, timestamp, and content.
 *
 * This class provides functionality to store a message along with its size
 * and timestamp, and to convert the message into a formatted string.
 */
class Message {
public:
    /**
     * @brief Constructs a Message object.
     *
     * @param msg The content of the message.
     */
    Message(const std::string& msg);

    /**
     * @brief Converts the message to a formatted string.
     *
     * @return A string representation of the message in the format "size$HH:MM$message".
     */
    std::string toString() const;

private:
    std::uint32_t _size;           ///< The size of the message content in bytes.
    std::uint64_t _timestamp;      ///< The timestamp of the message, in Unix time.
    std::string _message;          ///< The message content stored in a std::string.

    static constexpr char SEPARATER = '$'; ///< The char that separates the different parts of the message.
    static constexpr char NULL_TERMINATOR = '\0'; ///< More clear view of null terminator
    static constexpr auto TIME_VIEW_SIZE = 2; ///< The standard way of showing hours or minutes (HH:MM)
};

#endif // MESSAGE_HPP
