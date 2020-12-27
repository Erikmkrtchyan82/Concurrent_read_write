#ifndef CONCURRENT_FILE_READING_EXCEPTIONS_HPP
#define CONCURRENT_FILE_READING_EXCEPTIONS_HPP

#include <stdexcept>

namespace exceptions {

struct command_line_error : std::invalid_argument {
    using std::invalid_argument::invalid_argument;
};

struct read_error : std::domain_error {
    using std::domain_error::domain_error;
};

struct write_error : std::domain_error {
    using std::domain_error::domain_error;
};

} // namespace exceptions


#endif //CONCURRENT_FILE_READING_EXCEPTIONS_HPP
