#ifndef CONCURRENT_READ_WRITE_WRITER_HPP
#define CONCURRENT_READ_WRITE_WRITER_HPP

#include <string>

namespace writer{
void write( std::string path, std::atomic<bool>& error_occured );
}

#endif //CONCURRENT_READ_WRITE_WRITER_HPP
