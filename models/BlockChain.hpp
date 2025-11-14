#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP
#include "Currency.hpp"
#include "logger.hpp"
#include <iostream>
#include <string>
#include <ctime>
#include <memory>


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
class BlockChain {//Singleton

    public:
        //Evitar cópia
        BlockChain(const BlockChain&) = delete;
        BlockChain& operator=(const BlockChain&) = delete;
        static void init( std::string name, Currency value);
        static BlockChain& get();
        ~BlockChain();
        void depositValue(Currency value);
        bool withdrawValue(Currency value);
        Currency getBalance();
        void printChain();
        void printHead();
        std::string getName();
        
    
    private:
        void printTransaction(Block* b);
        static std::unique_ptr<BlockChain> instance;
        BlockChain(std::string name, Currency value);
        FirstBlock* head;
        Block* createBlock(Currency value); 
        bool checkWithdrawal(Currency value); 
        size_t combineHash(size_t h1, size_t h2);
        size_t createCurrencyHash(Currency* value);
};


#endif //BLOCKCHAIN_HPP
