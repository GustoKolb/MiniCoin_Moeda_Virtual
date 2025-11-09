#include <iostream>
#include <ixwebsocket/IXWebSocket.h>

int main() {
    ix::WebSocket ws;
    ws.setUrl("ws://127.0.0.1:5555/ws");
    cout << "Cliente inicializado" << std::endl;
    
    ws.setOnMessageCallback([](const ix::WebSocketMessagePtr& msg) {
        if (msg->type == ix::WebSocketMessageType::Open)
            std::cout << "Conectado ao servidor Drogon!" << std::endl;
        else if (msg->type == ix::WebSocketMessageType::Message)
            std::cout << "Servidor disse: " << msg->str << std::endl;
    });

    ws.start();


    std::string name;
    long value;
    std::cout << "Digite seu Nome: ";
    std::cin >> name;
    std::cout << "Olá " << name << ", quanto você quer depositar?:";
    std::cin >> value;



    while(true){
        ws.sendText("Olá servidor!");
    }


    std::cin.get();
    ws.stop();

    return 0;
}
