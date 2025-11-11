// EchoWebsock.cc
#include "BlockchainWebSocket.h"
#include "models/BlockChain.hpp"
#include "Message.hpp"
#include <iostream>

void handleDeposit(const Message &msg) {
    try {
        Currency value(std::stod(msg.getValue()));
        BlockChain::get().depositValue(value);
        std::cout << "Depositou " << value.number << std::endl;
        //Falta fazer o Log 
    } catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

//------------------------------------------------------------
void handleWithdraw(const Message &msg) {
    try {
        Currency value(std::stod(msg.getValue()));
        bool check = BlockChain::get().withdrawValue(value);
        std::cout << (check ? "Retirou " + std::to_string(value.number): "Tentativa de retirar não deu") << std::endl;
        //Falta fazer o Log 
    } catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

//------------------------------------------------------------
void handleInit(const Message &msg) {
    try {
        Currency value(std::stod(msg.getValue()));
        BlockChain::init(msg.getName(), value);
        std::cout << "Conta criada: " << msg.getName() << " Saldo: " << value.getCurrency() << std::endl;
        //Pseudo-log 
    } catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

//------------------------------------------------------------
void BlockchainWebSocket::handleNewMessage(const WebSocketConnectionPtr &wsConnPtr, std::string &&message, const WebSocketMessageType &type)
{

    try {
        Message msg(message);
        switch(msg.getType()) {
            case Type::DEPOSIT: handleDeposit(msg); break;
            case Type::WITHDRAW: handleWithdraw(msg); break;
            case Type::INIT: handleInit(msg); break;
            default: std::cout << "Tipo de Mensagem Desconhecida" << std::endl;
        }
    } catch (const std::exception& e) {}//Deixei sem tratamento pq se vier algo diferente n importa
}
//------------------------------------------------------------
void BlockchainWebSocket::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr)
{
    //Ver o que dá pra fazer aqui
}
//------------------------------------------------------------
void BlockchainWebSocket::handleConnectionClosed(const WebSocketConnectionPtr &wsConnPtr)
{
    //Aqui também, talvez guardar os logs num arquivo? n sei
}

//------------------------------------------------------------


