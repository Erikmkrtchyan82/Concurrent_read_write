#include <iostream>
#include <fstream>
#include <thread>
#include <sstream>
#include <vector>

#include "exceptions.hpp"
#include "reader.hpp"
#include "counter.hpp"
#include "writer.hpp"
#include "variables.hpp"

using namespace std::literals::chrono_literals;

void print_letter() {
	
    int count = 0;
    std::vector<char> syms;

	// finding max number of occurrences
	for(auto&[sym,num]:global_vars::symbols ) {
        if ( num > count )
            count = num;
	}

	// finding all letters with max occurrences
    for ( auto &[sym, num] : global_vars::symbols ) {
        if ( num == count )
            syms.push_back( sym );
    }
	
    std::ostringstream ss;
    ss << "The most commonly occurring letter";

    ss << ( syms.size() > 1 ? "s are " : " is " );

    for ( int i = 0; i < syms.size(); ++i ) {
        ss << syms[ i ] << ( i + 1 == syms.size() ? "" : ", " );
    }

    ss << " - " << count << " times" << ( syms.size() > 1 ? " each " : "" );
    std::cout << ss.str() << std::endl;
}

int main( int argc, char *argv[] ) {

    using thread = std::thread;

	
    try {
        if ( argc < 2 ) {
            throw exceptions::command_line_error(
                "Usage: " + std::string( argv[ 0 ] ) + " <input-file-path>..." );
        }

        std::vector<thread> readers;

        std::this_thread::sleep_for( 20s );

        for ( int i = 1; i < argc; ++i ) {
            readers.emplace_back( reader::read, argv[ i ] );
        }

        std::atomic<bool> finished = false;

        thread counter( counter::count,  finished );

        thread write( writer::write, "output.txt" );

        std::this_thread::sleep_for( 30ms );


        for ( auto &t : readers )
            t.join();

        finished = true;

        counter.join();

        write.join();

        if ( global_vars::symbols.empty() )
            std::cout << "No letters" << std::endl;
        else
            print_letter();

    	
        return 0;
    }
    catch ( std::exception &e ) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    catch ( ... ) {
        std::cerr << "Error: Unexpected error\n";
        return -2;
    }
}
