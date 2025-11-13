#include <drogon/drogon.h>
#include <csignal>
#include "models/utils.hpp"
#include "models/logger.hpp"


int main()
{
    Logger::Init();
    const int port = 5555;
    // Set HTTP listener address and port
    drogon::app().addListener("0.0.0.0", port);

    // Load config file
    // drogon::app().loadConfigFile("../config.json");
    // drogon::app().loadConfigFile("../config.yaml");
    // Run HTTP framework,the method will block in the internal event loop
    Logger::Log(std::format("Deploy de servidor, escutando em porta {}", port));

    drogon::app().run();

    Logger::Log("Server desligado. Log salvo em logs/");
    Logger::Close();

    return 0;
}
