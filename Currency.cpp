
#include "Currency.hpp"
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>

Currency::Currency(long number, unsigned short decimal)
    : number(number), decimal(decimal) {}

//------------------------------------------------------------     
std::string Currency::getCurrency() const {
    long factor = 1;
    for (int i = 0; i < this->decimal; ++i)
        factor *= 10;

    long intPart = this->number / factor;
    long decimalPart = std::abs(this->number % factor);

    std::ostringstream oss;
    oss << intPart << "," << std::setw(this->decimal) << std::setfill('0') << decimalPart;
    return oss.str();
}
