#include "reader.hpp"
#include "exceptions.hpp"
#include "counter.hpp"

#include <fstream>
#include <vector>
#include <thread>

#include "variables.hpp"

namespace reader {

void read( std::string path, std::atomic<bool>& error_occured ) {

    std::ifstream input( path );

    if ( !input ) {
        if ( !error_occured ) {
            global_vars::exception_message = exceptions::read_error( "Failed to open " + path + " for reading" );
            error_occured = true;
        }
        return;
    }
	
	std::string row;

    while ( std::getline( input, row, '\n' ) ) {
        std::lock_guard l( global_vars::rows_mutex );
        global_vars::rows.push_back( row );
    }

    input.close();
}

}
