#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include <cstdint>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <cstring>

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
     * @param size The size of the message content in bytes.
     * @param timestamp The timestamp of when the message was created, in Unix time.
     * @param msg The content of the message.
     */
    Message(std::uint32_t size, std::uint64_t timestamp, const std::string& msg);

    /**
     * @brief Converts the message to a formatted string.
     *
     * @return A string representation of the message in the format "size$HH:MM$message".
     */
    std::string toString() const;

private:
    std::uint32_t _size;           ///< The size of the message content in bytes.
    std::uint64_t _timestamp;      ///< The timestamp of the message, in Unix time.
    static constexpr uint32_t BUFFER = 4025; ///< The maximum buffer size for message content.
    char _message[BUFFER];         ///< The message content stored in a character array.
    static constexpr char SEPARATER = '$'; ///< The char that separates the diffrent part of the message.
    static constexpr char NULL_TERMINATOR = '\0'; ///< more clear view of null terminator
    static constexpr int TIME_VIEW_SIZE = 2; ///< the size of the standart way of showing hours or minutes
                                              /// (HH:MM <-- M appears twice so the lenght is 2)


};

#endif // MESSAGE_HPP
