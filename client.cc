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
            Message message(msg->str);
            std::cout << message.getComment() << std::endl;
        } });

    ws.start();

    while (!connected)
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

    std::string name;
    double value;
    std::cout << "Digite seu Nome: ";
    std::cin >> name;
    std::cout << "Faça um Depósito Inicial: ";
    std::cin >> value;
    while (value < 0)
    {
        std::cout << "Número Negativo" << std::endl;
        std::cout << "Tente Novamente: ";
        std::cin >> value;
    }

    Message msg(name, std::to_string(value), "", Type::INIT);
    ws.sendText(msg.toString());
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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
