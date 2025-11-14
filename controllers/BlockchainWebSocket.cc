
//Autoria de Augusto Antonio Kolb Schiavini (GRR 20232337) e João Eduardo Zangari Ambrosio(GRR 20232344)|
#include "BlockchainWebSocket.h"
#include "models/BlockChain.hpp"
#include "Message.hpp"
#include "models/utils.hpp"
#include "models/logger.hpp"
#include <iostream>

//handleDeposit
//handleInit
//handleWithdraw
//handleLoggedIn
//handleNewMessage
//handleNewConnection
//handleConnectionClosed


void handleDeposit(const Message &msg, const WebSocketConnectionPtr &wsConnPtr)
{
    try //Testa se o Valor é valido
    {
        Currency value(std::stod(msg.getValue()));
        try
        {
            Logger::Log(std::format("Novo depósito efetuado por cliente {}", msg.getName()));
            BlockChain::get().depositValue(value);

            Message msgBack("", "", "Depósito realizado com sucesso!", Type::SUCCESS);
            wsConnPtr->send(msgBack.toString());
        }
        catch (const std::exception &e)
        {
            Logger::Log(e.what());
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        std::string comment = e.what();
        Message msgBack("", "", comment, Type::REFUSED);
        wsConnPtr->send(msgBack.toString());
    }
}

//------------------------------------------------------------
void handleWithdraw(const Message &msg, const WebSocketConnectionPtr &wsConnPtr)
{
    try //Testa se o Valor é válido 
    {
        Currency value(std::stod(msg.getValue()));
        Logger::Log(std::format("Nova tentativa de retirada efetuada por cliente {} de valor {}", msg.getName(), value.getCurrency()));
        try
        {
            bool check = BlockChain::get().withdrawValue(value);
            if (!check)
            {
                Logger::Log(std::format("Falha em retirada de valor {}\n", value.getCurrency()));

                std::ostringstream oss;
                oss << "Falha em retirada " << " de valor " << value.getCurrency() << ", Saldo Disponível: " << BlockChain::get().getBalance().getCurrency();
                Message msgBack("", "", oss.str(), Type::REFUSED);
                wsConnPtr->send(msgBack.toString());
            }
            else
            {
                Message msgBack("", "", "Retirada realizada com sucesso!", Type::SUCCESS);
                wsConnPtr->send(msgBack.toString());
            }
        }
        catch (const std::exception &e)
        {
            Logger::Log(e.what());
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        std::string comment = e.what();
        Message msgBack("", "", comment, Type::REFUSED);
        wsConnPtr->send(msgBack.toString());
    }
}

//------------------------------------------------------------
void handleInit(const Message &msg, const WebSocketConnectionPtr &wsConnPtr)
{
    try //Inicia a BlockChain
    {
        Currency value(std::stod(msg.getValue()));
        BlockChain::init(msg.getName(), value);
        Logger::Log("Nova Blockchain Criada\n");
        BlockChain::get().printHead();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

//------------------------------------------------------------
void handleLoggedIn(const Message &msg, const WebSocketConnectionPtr &wsConnPtr)
{
    try //Testa se a BlockChain já existe, i.e, se o cliente já criou a conta antes
    {
        BlockChain::get();
        Message msgBack("", "", "", Type::LOGGEDIN);
        wsConnPtr->send(msgBack.toString());
    }
    catch(...)
    {
    }
}

//------------------------------------------------------------
void BlockchainWebSocket::handleNewMessage(const WebSocketConnectionPtr &wsConnPtr, std::string &&message, const WebSocketMessageType &type)
{

    try
    {
        Message msg(message);
        switch (msg.getType())
        {
        case Type::DEPOSIT:
            handleDeposit(msg, wsConnPtr);
            break;
        case Type::WITHDRAW:
            handleWithdraw(msg, wsConnPtr);
            break;
        case Type::INIT:
            handleInit(msg, wsConnPtr);
            break;
        case Type::LOGGEDIN:
            handleLoggedIn(msg, wsConnPtr);
            break;
        default:
            Logger::Log(std::format("[ERROR] Tipo de Mensagem Desconhecida: {}", message));
        }
    }
    catch (const std::exception &e)
    {
    }
}
//------------------------------------------------------------
void BlockchainWebSocket::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr)
{
    Logger::Log("Cliente conectado!");
}
//------------------------------------------------------------
void BlockchainWebSocket::handleConnectionClosed(const WebSocketConnectionPtr &wsConnPtr)
{
    Logger::Log("Cliente desconectado!");
}

//------------------------------------------------------------
