#include "BlockChain.h"
#include <iostream>

void BlockChain::handleNewMessage(const WebSocketConnectionPtr& wsConnPtr, std::string &&message, const WebSocketMessageType &type)
{
    std::cout << message << std::endl;
    // write your application logic here
}

void BlockChain::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr& wsConnPtr)
{
    std::cout << "Nova conexão WebSocket!" << std::endl;
    // write your application logic here
}

void BlockChain::handleConnectionClosed(const WebSocketConnectionPtr& wsConnPtr)
{
    // write your application logic here
}
