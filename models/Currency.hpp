#ifndef CURRENCY_HPP
#define CURRENCY_HPP

#include <string>

class Currency {
    public:

        static constexpr unsigned short DEFAULT_DECIMAL = 2;
        Currency() : number{0} {}
        Currency(double number);//a escolher
        Currency(const Currency& other): //Cópia
        number{other.number} {}
        
        Currency& operator=(const Currency& other) {

            if (this != &other) {
                this->number = other.number;
            }
            return *this;
        }
        ~Currency() = default;


        long number;
        double getCurrency() const;
};


#endif // !CURRENCY_HPP
