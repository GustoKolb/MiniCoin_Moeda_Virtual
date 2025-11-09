#ifndef CURRENCY_HPP
#define CURRENCY_HPP

#include <string>

class Currency {
    public:

        static constexpr unsigned short DEFAULT_DECIMAL = 2;
        Currency() : number{0}, decimal {DEFAULT_DECIMAL} {}//pronto
        Currency(long number, unsigned short decimal);//a escolher
        Currency(const Currency& other): //Cópia
        number{other.number}, decimal{other.decimal} {}
        
        Currency& operator=(const Currency& other) {

            if (this != &other) {
                this->number = other.number;
            }
            return *this;
        }
        ~Currency() = default;


        long number;
        const unsigned short decimal;
        std::string getCurrency() const;
};


#endif // !CURRENCY_HPP
