
//Autoria de Augusto Antonio Kolb Schiavini (GRR 20232337) e João Eduardo Zangari Ambrosio(GRR 20232344)|

#include <iostream>
#include <cmath>
#include <ixwebsocket/IXWebSocket.h>
#include <atomic>
#include "Message.hpp"

bool checkValidDouble(double x)
{
    double rounded = std::round(x * 100.0) / 100.0;
    return std::fabs(x - rounded) < 1e-9;
}
//----------------------------------------------------------------------------------
bool checkValidValue(double value)
{
    return (value >= 0 && checkValidDouble(value));
}

//----------------------------------------------------------------------------------
double inputDouble() {
    
    std::string input;
    double value;
    while (true) {
        try {
            std::getline(std::cin, input);
            value = std::stod(input);
            if (value >= 0) 
                return value;
            else 
                std::cout << "Valor Negativo, Tente Novamente: ";

        } catch (std::exception& e){
            std::cout << "Valor Não Numérico, Tente Novamente: ";
        }

    }
    return value;

}
//----------------------------------------------------------------------------------
int main()
{
    ix::WebSocket ws;
    ws.setUrl("ws://127.0.0.1:5555/ws");
    std::cout << "Cliente inicializado" << std::endl;

    std::atomic<bool> connected(false);
    std::atomic<bool> loggedIn(false);
    std::atomic<bool> valid(false);

    ws.setOnMessageCallback([&connected, &loggedIn, &ws](const ix::WebSocketMessagePtr &msg)
                            {
        if (msg->type == ix::WebSocketMessageType::Open) {
            std::cout << "Conectado ao servidor Drogon!" << std::endl;
            connected = true;
            Message msg("","","",Type::LOGGEDIN); //check se ja criou usuario
            ws.send(msg.toString());
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); //espera resposta


        } else if (msg->type == ix::WebSocketMessageType::Message) {
            Message message(msg->str);

            if(message.getType() == Type::LOGGEDIN && !loggedIn){
                std::cout << "Cliente já criado! Reconectando...\n";
                loggedIn = true;
            }

            std::cout << message.getComment() << std::endl;
        } });
 
    
    ws.start();

    while (!connected)
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

    std::string name;
    std::string valueStr;
    double value;
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); //espera resposta
    if (!loggedIn)
    {
        std::cout << "Digite seu Nome: ";
        std::getline(std::cin, name);
        std::cout << "Faça um Depósito Inicial: ";
        while (!valid)
        {
            std::getline(std::cin, valueStr);
            try
            {
                value = std::stod(valueStr);
                Message msg(name, std::to_string(value), "", Type::INIT);
                ws.sendText(msg.toString());
                valid = true;
                loggedIn = true;
            }
            catch (...)
            {
                std::cout << "Valor inválido. Digite um número.\n";
            }
        }
    }

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
            std::getline(std::cin, valueStr);

            try
            {
                value = std::stod(valueStr);
                Message msg(name, std::to_string(value), "", Type::DEPOSIT);
                ws.sendText(msg.toString());
                std::this_thread::sleep_for(std::chrono::milliseconds(500)); // espera resposta servidor para print do menu
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
                std::this_thread::sleep_for(std::chrono::milliseconds(500)); // espera resposta servidor para print do menu
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
