#ifndef CONCURRENT_FILE_READING_EXCEPTIONS_HPP
#define CONCURRENT_FILE_READING_EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

namespace exceptions {

struct command_line_error : std::invalid_argument {
    using std::invalid_argument::invalid_argument;
};

struct read_error : std::domain_error {
//    using std::domain_error::domain_error;
    read_error( const std::string &path ) : std::domain_error( "Failed to read a line from " + path ) {};
};

struct write_error : std::domain_error {
//    using std::domain_error::domain_error;
    write_error( const std::string &path ) : std::domain_error( "Failed to write a line to " + path ) {};
};

} // namespace exceptions



#endif //CONCURRENT_FILE_READING_EXCEPTIONS_HPP
