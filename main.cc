#include <drogon/drogon.h>
#include "models/utils.hpp"

int main()
{
    const int port = 5555;
    // Set HTTP listener address and port
    drogon::app().addListener("0.0.0.0", port);
    // Load config file
    // drogon::app().loadConfigFile("../config.json");
    // drogon::app().loadConfigFile("../config.yaml");
    // Run HTTP framework,the method will block in the internal event loop
    std::cout << "[" << currentTime() << "]" << "[SERVER]" << " Deploy de servidor, escutando em porta " << port << std::endl;

    drogon::app().run();
    return 0;
}
