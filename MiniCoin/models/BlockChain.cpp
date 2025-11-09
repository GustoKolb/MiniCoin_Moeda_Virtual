#include <iostream>
#include "BlockChain.hpp"

BlockChain::BlockChain(std::string name,Currency value) {

    //Cria Primeiro Block e o Hash de cada parte dele
    this->head = new FirstBlock;
    this->head->name = name;
    this->head->value = value;
    time_t timestamp = time(&timestamp);
    this->head->datetime = *localtime(&timestamp);

    size_t hashName = std::hash<std::string>{}(this->head->name);
    size_t hashValue = createCurrencyHash(&this->head->value);
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
    newBlock->hash = combineHash(olderHash, createCurrencyHash(&value));

    if (!this->head->next) {
        this->head->next = newBlock;
    } else {
        aux->next = newBlock;
    }
    return newBlock;
}

//------------------------------------------------------------

bool BlockChain::checkWithdrawal(Currency value){

    Currency account_value;
    account_value.number = head->value.number;
    Block* aux = this->head->next;

    while (aux != nullptr) {
        account_value.number += aux->value.number;
        //calcular o hash aqui
        aux = aux->next;
    }
    if (account_value.number < value.number) 
        return false;
    return true;
}

//------------------------------------------------------------     
void BlockChain::depositValue(Currency value){
    
    if (value.number <= 0){
        throw std::invalid_argument("Valor depositado não Positivo");
        return;
    }
    createBlock(value);
}



//------------------------------------------------------------     
void BlockChain::withdrawValue(Currency value){

    if (value.number <= 0){
        throw std::invalid_argument("Valor depositado não Positivo");
        return;
    }
    if (checkWithdrawal(value)) {
        value.number = -value.number;
        createBlock(value);
    }
    return;
}

//------------------------------------------------------------     
void BlockChain::printChain() {
    
    Block* aux = this->head->next;
    if (this->head) {
        std::cout << "Dono da Conta: " << this->head->name << "\n";
        std::cout << "Data de criação: " << asctime(&this->head->datetime);
        std::cout << "Valor: " << this->head->value.getCurrency() << "\n";
        std::cout << "Hash: " << this->head->hash << "\n\n";
        
        while (aux){
            std::cout << "Valor: " << aux->value.getCurrency() << "\n";
            std::cout << "Hash: " << aux->hash << "\n\n";
            aux = aux->next;
        }
    }
}


//------------------------------------------------------------
size_t BlockChain::combineHash(size_t h1, size_t h2) {
    return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
}
       
//------------------------------------------------------------     
size_t BlockChain::createCurrencyHash(Currency* value){
    
    size_t hashLong = std::hash<long> {}(value->number);
    size_t hashShort = std::hash<unsigned short> {}(value->decimal);
    return combineHash(hashLong, hashShort);
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
