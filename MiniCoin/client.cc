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
    std::cout << "Olá " << name << ", quanto você quer depositar?:";
    std::cin >> value;

    Message msg(name, std::to_string(value), "", Type::INIT);
    ws.sendText(msg.toString());
    std::cin.get();
    ws.stop();
    return 0;
}
