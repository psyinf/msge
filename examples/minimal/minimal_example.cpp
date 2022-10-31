#include "Core.h"
#include <exception>
#include <iostream>

using namespace msge;

int main(int argc, char** argv)
try
{
    std::vector<std::string_view> arguments(argv, argv + argc);
    Core::initializeLogging(arguments);


}
catch (const std::exception& e )
{
    LOG(ERROR) << e.what();
    std::cerr << "Uncaught exception: " << e.what() << "\n";
}