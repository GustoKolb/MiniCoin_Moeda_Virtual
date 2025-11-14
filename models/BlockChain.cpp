#include <iostream>
#include "BlockChain.hpp"
std::unique_ptr<BlockChain> BlockChain::instance = nullptr;
//------------------------------------------------------------
void BlockChain::init(std::string name,Currency value){
    if (instance) {
        throw std::runtime_error("A BlockChain já foi inicializada");
    }
    instance = std::unique_ptr<BlockChain>(new BlockChain(name, value));
}
//------------------------------------------------------------
BlockChain& BlockChain::get() {
    
    if (!instance)
            throw std::runtime_error("BlockChain não inicializada!");
    return *instance;
}
//------------------------------------------------------------

BlockChain::BlockChain(std::string name,Currency value) {

    if (value.number < 0) {
        throw std::invalid_argument("Valor Inicial Negativo");
        return;
    }
    //Cria Primeiro Block e o Hash de cada parte dele
    this->head = new FirstBlock;
    this->head->name = name;
    this->head->value = value;
    time_t timestamp = time(&timestamp);
    this->head->datetime = *localtime(&timestamp);

    size_t hashName = std::hash<std::string>{}(this->head->name);
    size_t hashValue = std::hash<long>{}(this->head->value.number);
    size_t hashTime = 0;
    hashTime = combineHash(hashTime, std::hash<int>{}(this->head->datetime.tm_sec));
    hashTime = combineHash(hashTime, std::hash<int>{}(this->head->datetime.tm_min));
    hashTime = combineHash(hashTime, std::hash<int>{}(this->head->datetime.tm_hour));
    hashTime = combineHash(hashTime, std::hash<int>{}(this->head->datetime.tm_mday));
    hashTime = combineHash(hashTime, std::hash<int>{}(this->head->datetime.tm_mon));
    hashTime = combineHash(hashTime, std::hash<int>{}(this->head->datetime.tm_year));
    
    size_t finalHash = hashName;
    finalHash = combineHash(finalHash, hashValue);
    finalHash = combineHash(finalHash, hashTime);
    this->head->hash = finalHash;
    this->head->next = nullptr;

}
//------------------------------------------------------------
Block* BlockChain::createBlock(Currency value) {

    //Acha último Bloco da Lista
    Block* aux = this->head->next;
    size_t olderHash = this->head->hash;
    if (aux) {
        olderHash = aux->hash;
        while (aux->next) {
            aux = aux->next;
            olderHash = aux->hash;
        }
    }

    //Cria Bloco 
    Block* newBlock = new Block();
    newBlock->value = value;
    newBlock->next = nullptr;
    newBlock->hash = combineHash(olderHash, std::hash<long>{}(newBlock->value.number));

    if (!this->head->next) {
        this->head->next = newBlock;
    } else {
        aux->next = newBlock;
    }
    return newBlock;
}

//------------------------------------------------------------
std::string BlockChain::getName() {
    return this->head->name;
}
//------------------------------------------------------------
Currency BlockChain::getBalance() {
    
    Currency account_value;
    account_value.number = head->value.number;
    Block* aux = this->head->next;

    while (aux != nullptr) {
        account_value.number += aux->value.number;
        aux = aux->next;
    }
    return account_value;
}
//------------------------------------------------------------     
bool BlockChain::checkWithdrawal(Currency value){
    return (getBalance().number >= value.number);
}

//------------------------------------------------------------     
void BlockChain::depositValue(Currency value){
    
    if (value.number <= 0){
        throw std::invalid_argument("Valor depositado não Positivo");
        return;
    }
    createBlock(value);
    Block* aux = this->head->next;
    while (aux->next){
        aux = aux->next;
    }
    if (aux)
        Logger::Log(std::format("\nTransação: {}\nHash: {}\n", aux->value.getCurrency(), aux->hash));
}



//------------------------------------------------------------     
bool BlockChain::withdrawValue(Currency value){

    if (value.number <= 0){
        throw std::invalid_argument("Valor depositado não Positivo");
        return false;
    }
    if (checkWithdrawal(value)) {
        value.number = -value.number;
        createBlock(value);
        Block* aux = this->head->next;
        while (aux->next){
            aux = aux->next;
        }
        if (aux)
            Logger::Log(std::format("\nTransação: {}\nHash: {}\n", aux->value.getCurrency(), aux->hash));

        return true;
    }     
    return false;
}

//------------------------------------------------------------     
void BlockChain::printHead() {

    if (this->head) 
        Logger::Log(std::format("\nDono da Conta: {}\nData de criação: {}Valor: {}\nHash: {}\n",
        this->head->name, asctime(&this->head->datetime), this->head->value.getCurrency(), this->head->hash));
   

}

//------------------------------------------------------------     
void BlockChain::printChain() {
    
    printHead();
    Block* aux = this->head->next;
       
        while (aux){
            Logger::Log(std::format("\nTransação: {}\nHash: {}\n\n", aux->value.getCurrency(), aux->hash));
           aux = aux->next;
        }
}


//------------------------------------------------------------
size_t BlockChain::combineHash(size_t h1, size_t h2) {
    return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
}
       
//------------------------------------------------------------     
BlockChain::~BlockChain() {

    Block* aux = this->head->next;
    while(aux) {
        Block* next = aux->next;
        delete aux;
        aux = next;

    }
    delete this->head;
    this->head = nullptr;

}
