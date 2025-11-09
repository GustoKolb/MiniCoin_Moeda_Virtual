#include <iostream>
#include <ixwebsocket/IXWebSocket.h>

int main() {
    ix::WebSocket ws;
    ws.setUrl("ws://127.0.0.1:8080/ws");
    cout << "Cliente inicializado" << std::endl;
    
    ws.setOnMessageCallback([](const ix::WebSocketMessagePtr& msg) {
        if (msg->type == ix::WebSocketMessageType::Open)
            std::cout << "Conectado ao servidor Drogon!" << std::endl;
        else if (msg->type == ix::WebSocketMessageType::Message)
            std::cout << "Servidor disse: " << msg->str << std::endl;
    });

    ws.start();
    ws.sendText("Olá servidor!");

    std::cin.get();
    ws.stop();

    return 0;
}
