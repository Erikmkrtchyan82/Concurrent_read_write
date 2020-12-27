#ifndef CONCURRENT_FILE_READING_READER_HPP
#define CONCURRENT_FILE_READING_READER_HPP

#include <atomic>
#include <string>

namespace reader{
void read( std::string path, std::atomic<bool>& error_occured );
}

#endif //CONCURRENT_FILE_READING_READER_HPP
