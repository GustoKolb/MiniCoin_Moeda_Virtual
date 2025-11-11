#include <iostream>
#include <ixwebsocket/IXWebSocket.h>
#include <atomic>
#include "Message.hpp"

int main()
{
    ix::WebSocket ws;
    ws.setUrl("ws://127.0.0.1:5555/ws");
    std::cout << "Cliente inicializado" << std::endl;

    std::atomic<bool> connected(false);

    ws.setOnMessageCallback([&connected](const ix::WebSocketMessagePtr &msg)
                            {
        if (msg->type == ix::WebSocketMessageType::Open) {
            std::cout << "Conectado ao servidor Drogon!" << std::endl;
            connected = true;
        } else if (msg->type == ix::WebSocketMessageType::Message) {
            std::cout << "Servidor disse: " << msg->str << std::endl;
        } });

    ws.start();

    // Esperar conexão antes de continuar
    while (!connected)
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

    // Agora é seguro interagir
    std::string name;
    double value;
    std::cout << "Digite seu Nome: ";
    std::cin >> name;

    Message msg(name, std::to_string(0), "", Type::INIT);
    ws.sendText(msg.toString());

    bool running = true;
    while (running)
    {
        std::cout << "\n======= MENU =======\n";
        std::cout << "1. Depósito\n";
        std::cout << "2. Retirada\n";
        std::cout << "3. Sair\n";
        std::cout << "====================\n";
        std::cout << "Escolha uma opção: ";

        std::string opcaoStr;
        std::getline(std::cin, opcaoStr);

        if (opcaoStr == "1")
        {
            std::cout << "Valor para depósito: ";
            std::string valorStr;
            std::getline(std::cin, valorStr);

            try
            {
                double valor = std::stod(valorStr);
                Message msg(name, std::to_string(valor), "", Type::DEPOSIT);
                ws.sendText(msg.toString());
            }
            catch (...)
            {
                std::cout << "Valor inválido. Digite um número.\n";
            }
        }
        else if (opcaoStr == "2")
        {
            std::cout << "Valor para retirada: ";
            std::string valorStr;
            std::getline(std::cin, valorStr);

            try
            {
                double valor = std::stod(valorStr);
                Message msg(name, std::to_string(valor), "", Type::WITHDRAW);
                ws.sendText(msg.toString());
            }
            catch (...)
            {
                std::cout << "Valor inválido. Digite um número.\n";
            }
        }
        else if (opcaoStr == "3")
        {
            std::cout << "Saindo...\n";
            running = false;
        }
        else
        {
            std::cout << "Opção inválida! Tente novamente.\n";
        }
    }

    ws.stop();
    return 0;
}
