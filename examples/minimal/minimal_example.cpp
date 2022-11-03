#include "Core.h"

#include <exception>
#include <iostream>

using namespace msge;

int main(int argc, char** argv)
try
{
    /* Setup the core instance. Pass a configuration item and some command line arguments.*/
    Core core(Core::Config(), Core::makeCommandLineArgs(argc, argv));
    
}
catch (const std::exception& e)
{
    LOG(ERROR) << e.what();
    std::cerr << "Uncaught exception: " << e.what() << "\n";
}