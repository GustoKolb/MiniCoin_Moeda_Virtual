#include <iostream>
#include "BlockChain.hpp"
#include "Currency.hpp"

int main() { 

    Currency moeda(500,2);
    BlockChain* list = new BlockChain("Augusto", moeda);
    list->depositValue(moeda);
    list->depositValue(moeda);
    list->withdrawValue(moeda);
    list->printChain();

    return 0;
}
