// Autoria: Augusto Antonio Kolb Schiavini (GRR0232337) e João Eduardo Ambrosio

#include "BlockchainWebSocket.h"
#include "models/BlockChain.hpp"
#include "Message.hpp"
#include <iostream>
#include "models/utils.hpp"

void handleDeposit(const Message &msg, const WebSocketConnectionPtr &wsConnPtr) {
    try {
        Currency value(std::stod(msg.getValue()));
        try {
            std::cout  << "[" << currentTime() << "]" << "[SERVER] " <<  " Novo depósito efetuado por cliente " << msg.getName() << std::endl ;
            BlockChain::get().depositValue(value);
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    } catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        std::string comment = e.what();
        Message msgBack("", "", comment, Type::REFUSED);
        wsConnPtr->send(msgBack.toString());
    }
}

//------------------------------------------------------------
void handleWithdraw(const Message &msg, const WebSocketConnectionPtr &wsConnPtr) {
    try {
        Currency value(std::stod(msg.getValue()));
        std::cout  << "[" << currentTime() << "]" << "[SERVER]" << " Nova tentativa de retirada efetuada por cliente " << msg.getName() << " de valor " << value.getCurrency() << std::endl ;
        try {
            bool check = BlockChain::get().withdrawValue(value);
            if(!check) {
                std::ostringstream oss;
                oss <<  " Falha em retirada " << " de valor " << value.getCurrency() << ", Saldo Disponível: " << BlockChain::get().getBalance().getCurrency();
                std::cout << oss.str() << std::endl;
                Message msgBack("", "", oss.str(), Type::REFUSED);
                wsConnPtr->send(msgBack.toString());
            }
        } catch(const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
        
    } catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        std::string comment = e.what();
        Message msgBack("", "", comment, Type::REFUSED);
        wsConnPtr->send(msgBack.toString());
        
    }
}

//------------------------------------------------------------
void handleInit(const Message &msg, const WebSocketConnectionPtr &wsConnPtr) {
    try {
        Currency value(std::stod(msg.getValue()));
        BlockChain::init(msg.getName(), value);
        std::cout  << "[" << currentTime() << "]" << "[SERVER]" << "Nova BlockChain criada." << std::endl;
        BlockChain::get().printHead();
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
            case Type::DEPOSIT: handleDeposit(msg, wsConnPtr); break;
            case Type::WITHDRAW: handleWithdraw(msg, wsConnPtr); break;
            case Type::INIT: handleInit(msg, wsConnPtr); break;
            default: std::cout  << "[" << currentTime() << "]" << "[SERVER]" << "[ERROR]" << " Tipo de Mensagem Desconhecida" << std::endl;
        }
    } catch (const std::exception& e) {}
}
//------------------------------------------------------------
void BlockchainWebSocket::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr)
{
    std::cout  << "[" << currentTime() << "]" << "[SERVER] " << "Cliente conectado!" << std::endl;
}
//------------------------------------------------------------
void BlockchainWebSocket::handleConnectionClosed(const WebSocketConnectionPtr &wsConnPtr)
{
    std::cout  << "[" << currentTime() << "]" << "[SERVER] " << "Cliente desconectado!" << std::endl;
}

//------------------------------------------------------------


