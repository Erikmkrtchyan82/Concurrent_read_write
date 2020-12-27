#ifndef CONCURRENT_READ_WRITE_VARIABLES_HPP
#define CONCURRENT_READ_WRITE_VARIABLES_HPP

#include <atomic>
#include <vector>
#include <map>
#include <mutex>
#include <string>

struct global_vars {

	inline static std::map<char, unsigned> symbols;			// all symbols to count
	inline static std::vector<std::string> rows;			// all rows that already read
	inline static std::vector <std::string> ready_rows;		// all rows thar already count
	inline static std::mutex rows_mutex;					// mutex for already read rows
	inline static std::mutex ready_rows_mutex;				// mutex for already counted rows
	inline static std::atomic<bool> ready=false;			// read has finished
	inline static std::atomic< bool > count_done=false;		// count has finished

	inline static std::exception exception_message;
	
};

#endif //CONCURRENT_READ_WRITE_VARIABLES_HPP
