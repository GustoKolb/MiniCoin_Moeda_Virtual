#include <iostream>
#include <ixwebsocket/IXWebSocket.h>
#include <atomic>
#include "Message.hpp"

int main() {
    ix::WebSocket ws;
    ws.setUrl("ws://127.0.0.1:5555/ws");
    std::cout << "Cliente inicializado" << std::endl;

    std::atomic<bool> connected(false);

    ws.setOnMessageCallback([&connected](const ix::WebSocketMessagePtr& msg) {
        if (msg->type == ix::WebSocketMessageType::Open) {
            std::cout << "Conectado ao servidor Drogon!" << std::endl;
            connected = true;
        } else if (msg->type == ix::WebSocketMessageType::Message) {
            std::cout << "Servidor disse: " << msg->str << std::endl;
        }
    });

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

        int opcao;
        std::cin >> opcao;

        switch (opcao) {
            case 1: {
                double valor;
                std::cout << "Valor para depósito: ";
                std::cin >> valor;

                Message msg(name, std::to_string(valor), "", Type::DEPOSIT);
                ws.sendText(msg.toString());
                break;
            }
            case 2: {
                double valor;
                std::cout << "Valor para retirada: ";
                std::cin >> valor;

                Message msg(name, std::to_string(valor), "", Type::WITHDRAW);
                ws.sendText(msg.toString());
                break;
            }
            case 3:
                std::cout << "Saindo...\n";
                running = false;
                break;
            default:
                std::cout << "Opção inválida! Tente novamente.\n";
        }
    }

    std::cin.get();
    ws.stop();
    return 0;
}
