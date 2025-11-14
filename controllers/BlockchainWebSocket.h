
//Autoria de Augusto Antonio Kolb Schiavini (GRR 20232337) e João Eduardo Zangari Ambrosio(GRR 20232344)|
#pragma once
#include <drogon/WebSocketController.h>
using namespace drogon;
class BlockchainWebSocket:public drogon::WebSocketController<BlockchainWebSocket>
{
public:
    virtual void handleNewMessage(const WebSocketConnectionPtr&, 
    std::string &&, const WebSocketMessageType &)override;

    virtual void handleNewConnection(const HttpRequestPtr &,
    const WebSocketConnectionPtr&)override;

    virtual void handleConnectionClosed(const WebSocketConnectionPtr&)override;

    WS_PATH_LIST_BEGIN
    WS_PATH_ADD("/ws", Get);//Nosso Caminho
    WS_PATH_LIST_END
};
