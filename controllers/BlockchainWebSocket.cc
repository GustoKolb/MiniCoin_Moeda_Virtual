// EchoWebsock.cc
#include "BlockchainWebSocket.h"
#include "models/BlockChain.hpp"
#include "Message.hpp"
#include <iostream>
#include "models/utils.hpp"

void handleDeposit(const Message &msg) {
    try {
        Currency value(std::stod(msg.getValue()));
        BlockChain::get().depositValue(value);
        //Falta fazer o Log 
        std::cout  << "[" << currentTime() << "]" << "[SERVER] " <<  " Novo depósito efetuado por cliente " << msg.getName() << " de valor " << value.number << std::endl ;
    } catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

//------------------------------------------------------------
void handleWithdraw(const Message &msg) {
    try {
        Currency value(std::stod(msg.getValue()));
        bool check = BlockChain::get().withdrawValue(value);
        if(check)
            std::cout  << "[" << currentTime() << "]" << "[SERVER]" << " Nova retirada efetuada por cliente " << msg.getName() << " de valor " << value.number << std::endl ;
        else
            std::cout  << "[" << currentTime() << "]" << "[SERVER]" << "[ERROR]" << " Falha em retirada por cliente " << msg.getName() << " de valor " << value.number << std::endl ;
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
        std::cout  << "[" << currentTime() << "]" << "[SERVER]" << "Nova blockchain criada, cliente: " << msg.getName() << std::endl;
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
            default: std::cout  << "[" << currentTime() << "]" << "[SERVER]" << "[ERROR]" << " Tipo de Mensagem Desconhecida" << std::endl;
        }
    } catch (const std::exception& e) {}//Deixei sem tratamento pq se vier algo diferente n importa
}
//------------------------------------------------------------
void BlockchainWebSocket::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr)
{
    std::cout  << "[" << currentTime() << "]" << "[SERVER] " << "Cliente conectado!" << std::endl;
    //Ver o que dá pra fazer aqui
}
//------------------------------------------------------------
void BlockchainWebSocket::handleConnectionClosed(const WebSocketConnectionPtr &wsConnPtr)
{
    std::cout  << "[" << currentTime() << "]" << "[SERVER] " << "Cliente desconectado!" << std::endl;
    //Aqui também, talvez guardar os logs num arquivo? n sei
}

//------------------------------------------------------------


