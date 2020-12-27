#ifndef CONCURRENT_FILE_READING_COUNTER_HPP
#define CONCURRENT_FILE_READING_COUNTER_HPP

#include <atomic>

namespace counter {

void count( std::atomic<bool> &finished );

} // namespace counter

#endif //CONCURRENT_FILE_READING_COUNTER_HPP
