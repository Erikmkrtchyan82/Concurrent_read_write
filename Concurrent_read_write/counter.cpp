#include <vector>
#include <string>
#include <map>
#include "counter.hpp"

#include "variables.hpp"

namespace counter{

void count(std::atomic<bool>& finished, std::atomic<bool> &error_occured ) {
	
    while ( true ) {

        if ( error_occured )
            break;
    	
        std::vector< std::string > local_rows;

        {
            std::lock_guard l(global_vars::rows_mutex );
            local_rows.swap(global_vars::rows );
        }

        for ( auto &str:local_rows ) {
            for ( auto &c:str ) {
                if ( isalpha( c ))
                    ++global_vars::symbols[ tolower(c) ];
            }
        }

        {
            std::lock_guard l(global_vars::ready_rows_mutex );
            global_vars::ready_rows.insert( global_vars::ready_rows.end(), local_rows.begin(), local_rows.end() );
        }

    	//  if all reader threads have finished their work and there wasn't any new rows to count letters
        if ( finished && global_vars::rows.empty() )
            break;
    }
	
    global_vars::count_done = true;
}

} // namespace counter
