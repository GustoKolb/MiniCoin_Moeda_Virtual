#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP
#include "Currency.hpp"
#include <iostream>
#include <string>
#include <ctime>


//------------------------------------------------------------
struct Block;

struct Block  {
    Currency value;
    size_t hash;
    Block* next;

};
//------------------------------------------------------------
struct FirstBlock {
    Currency value;
    std::string name;
    struct std::tm datetime;
    size_t hash;
    Block* next;
};
 
//------------------------------------------------------------
class BlockChain {

    public:
        BlockChain(std::string name, Currency value);
        ~BlockChain();
        void depositValue(Currency value);
        void withdrawValue(Currency value);
        void printChain();
    
    private:
        FirstBlock* head;
        Block* createBlock(Currency value); 
        bool checkWithdrawal(Currency value); 
        size_t combineHash(size_t h1, size_t h2);
        size_t createCurrencyHash(Currency* value);
};


#endif //BLOCKCHAIN_HPP
