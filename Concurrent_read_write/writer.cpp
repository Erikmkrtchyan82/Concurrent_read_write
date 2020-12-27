#include <fstream>
#include <string>
#include <mutex>
#include <vector>
#include "writer.hpp"
#include "variables.hpp"
#include "exceptions.hpp"


namespace writer {

void write( std::string path, std::atomic<bool>& error_occured ) {

    std::ofstream output( path );

    if ( !output ) {
        if ( !error_occured ) {
            global_vars::exception_message = exceptions::read_error( "Failed to open " + path + " for writing" );
            error_occured = true;
        }
        return;
    }
    	
    while ( true ) {
        std::vector< std::string > local_rows;

        {
            std::lock_guard l( global_vars::ready_rows_mutex );
            local_rows.swap( global_vars::ready_rows );
        }

        std::copy( local_rows.begin(), local_rows.end(), std::ostream_iterator<std::string>( output,"\n" ) );

        if ( global_vars::count_done && global_vars::ready_rows.empty() )
            break;
    }
    output.close();
}

}
