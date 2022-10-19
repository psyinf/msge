#include <Core.h>
#include <SimpleScene.h>
#include <StaticEntity.h>

#include <exception>
#include <iostream>
#include <memory>


using namespace msge;

int main(int argc, char** argv)
try
{
    std::vector<std::string_view> arguments(argv, argv + argc);
    Core::initializeLogging(arguments);

    auto bs = std::make_unique<SimpleScene>("scene1");
    
    StaticEntity se("se1");
    bs->addEntity(std::make_shared<StaticEntity>(std::move(se)));

}
catch (const std::exception& e)
{
    LOG(ERROR) << e.what();
    std::cerr << "Uncaught exception: " << e.what() << "\n";
}