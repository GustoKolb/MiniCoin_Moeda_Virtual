
//Autoria de Augusto Antonio Kolb Schiavini (GRR 20232337) e João Eduardo Zangari Ambrosio(GRR 20232344)|

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

   Logger::Log(std::format("Deploy de servidor, escutando em porta {}", port));

    drogon::app().run();

    Logger::Log("Server desligado. Log salvo em logs/");
    Logger::Close();

    return 0;
}
