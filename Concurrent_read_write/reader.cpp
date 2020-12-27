#include "reader.hpp"
#include "exceptions.hpp"
#include "counter.hpp"

#include <fstream>
#include <vector>
#include <thread>

#include "variables.hpp"

namespace reader {

void read( std::string path) {

    std::ifstream input( path );

	if ( !input )
        throw exceptions::read_error( "Failed to open " + path + " for reading" );

	std::string row;

    while ( std::getline( input, row, '\n' ) ) {
        std::lock_guard l( global_vars::rows_mutex );
        global_vars::rows.push_back( row );
    }

    input.close();
}

}
