
//Autoria de Augusto Antonio Kolb Schiavini (GRR 20232337) e João Eduardo Zangari Ambrosio(GRR 20232344)|
#include "Currency.hpp"
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>


Currency::Currency(double number) {

    //Checa se o número tem mais que DEFAULT_DECIMAL casa decimais
    double scaled = number * std::pow(10, DEFAULT_DECIMAL);
    double rounded = std::round(scaled);

    if (std::fabs(scaled - rounded) > 1e-6) {
        std::ostringstream oss;
        oss << "Erro: número com mais de " << DEFAULT_DECIMAL
        << " casas decimais: " << number;
        throw std::runtime_error(oss.str());
    }

    this->number = static_cast<long>(rounded);
   
}

//------------------------------------------------------------     
double Currency::getCurrency() const {

    return double(this->number / pow(10, DEFAULT_DECIMAL));
}
