// EchoWebsock.cc
#include "BlockchainWebSocket.h"
#include "models/BlockChain.hpp"

bool isNumber(const std::string str)
{
    try
    {
        std::size_t i;
        std::stod(str, &i);
        return i == str.size();
    }
    catch (...)
    {
        return false;
    }
}

bool checkMessageIsValid(const std::string message, const std::string prefix)
{
    const auto rest = message.substr(prefix.length());
    if (!isNumber(rest))
        return false;
}

void BlockchainWebSocket::handleNewMessage(const WebSocketConnectionPtr &wsConnPtr, std::string &&message, const WebSocketMessageType &type)
{
    std::cout << "teste";
    // write your application logic here
    if (message.starts_with("deposit") && checkMessageIsValid(message, "deposit"))
    {
        const auto value = std::stod(rest);

        auto deposit = new Currency(value);
        BlockChain::depositValue(deposit);
    }
    else if (message.starts_with("withdraw") && checkMessageIsValid(message, "withdraw"))
    {
        /* code */

        const auto value = std::stod(rest);

        auto withdrawal = new Currency(value);

        BlockChain::CheckWithdrawal(withdrawal);
    }
    else
    {
        wsConnPtr->send("Mensagem Inválida")
        /* code */
    }
}
void BlockchainWebSocket::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr)
{
    //Fazer check de se lista ja existe
    // write your application logic here
}
void BlockchainWebSocket::handleConnectionClosed(const WebSocketConnectionPtr &wsConnPtr)
{
    // write your application logic here
}