#include <vector>
#include <string>
#include "Flow.h"

int main( int argv, char** argc )
{
    std::string file_name;
    if( argv > 1 )
        file_name=to_string( argc[1] );
    Flow flow;
    flow.SetFile(file_name);
    return 0;
}