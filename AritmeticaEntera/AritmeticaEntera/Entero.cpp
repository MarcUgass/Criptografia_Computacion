#include "Entero.h"

Entero::Entero(const std::string& valor) {
    
    if (valor.substr(0, 3) == "-0x") {
        positivo = false;
        std::string numero_hex = valor.substr(3);
        std::reverse(numero_hex.begin(), numero_hex.end());
        for (size_t i = 0; i < numero_hex.length(); ++i) {
            num.push_back(hexCharToUint(numero_hex[i]));
        }
    }
    else if (valor.substr(0,2) == "0x") {
        positivo = true;
        std::string numero_hex = valor.substr(2);
        std::reverse(numero_hex.begin(), numero_hex.end());
        for (size_t i = 0; i < numero_hex.length(); ++i) {
            num.push_back(hexCharToUint(numero_hex[i]));
        }
    }
}

void Entero::imprimirHexadecimal() const { 
    if (!positivo)
        std::cout << "-";
    std::cout << "0x";

    for (auto it = num.rbegin(); it != num.rend(); ++it) {
        std::cout << uintToHexChar(*it);
    }
    std::cout << std::endl;
}

uint64_t Entero::hexCharToUint(char c) const {
    if (c >= '0' && c <= '9')
        return c - '0';
    else if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    else if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    else
        return 0;
}

char Entero::uintToHexChar(uint64_t n) const {
    if (n >= 0 && n <= 9)
        return '0' + n;
    else if (n >= 10 && n <= 15)
        return 'A' + (n - 10);
    else
        return 0;
}

void Entero::cambiarSigno() {
    positivo = !positivo;
}

void Entero::normalizar() {
    while (num.size() > 1 && num.back() == 0) {
        num.pop_back();
    }
    if (num.size() == 1 && num[0] == 0) {
        positivo = true;
    }
}

Entero Entero::obtenerMaximo(const Entero& otro) const {
    if (num.size() > otro.num.size())
        return *this;
    else if (num.size() < otro.num.size())
        return otro;
    else {
        for (int i = num.size() - 1; i >= 0; --i) {
            if (num[i] > otro.num[i])
                return *this;
            else if (num[i] < otro.num[i])
                return otro;
        }
        return *this; // En caso de ser iguales
    }
}

Entero Entero::sumar( Entero& otro)  {
    if (positivo == otro.positivo) {
        // Sumar ambos números normalmente
        Entero resultado("0x0");
        uint64_t carry = 0;
        size_t i = 0;
        while (i < num.size() || i < otro.num.size() || carry) {
            if (i == resultado.num.size())
                resultado.num.push_back(0);

            uint64_t sum = carry + (i < num.size() ? num[i] : 0) + (i < otro.num.size() ? otro.num[i] : 0);
            resultado.num[i] = sum % 16;
            carry = sum / 16;
            ++i;
        }
        resultado.positivo = positivo; // El resultado tiene el mismo signo que los operandos
        return resultado;
    }
    else {
        // Si los números tienen signos opuestos, realizar la resta
        return restar(otro);
    }
}

Entero Entero::restar( Entero& otro)  {
    Entero resultado("0x");
    uint64_t carry = 0;

    int maxSize = std::max(num.size(), otro.num.size());
    while (num.size() < maxSize) {num.push_back(uint64_t(0));} 
    while (otro.num.size() < maxSize) otro.num.push_back(uint64_t(0));

    for (size_t i = 0; i < maxSize; ++i) {
        uint64_t diff;
        if (num[i] < (otro.num[i] + carry)) {
            diff = 16 + num[i] - (otro.num[i] + carry);
            carry = 1;
        }
        else {
            diff = num[i] - (otro.num[i] + carry);
            carry = 0;
        }
        resultado.num.push_back(diff);
    }

    while (!resultado.num.empty() && resultado.num.back() == 0) resultado.num.pop_back();
    return resultado;
}
Entero Entero::multiplicar(Entero& otro) {
    std::vector<uint64_t> resultado(num.size() + otro.num.size(), 0);


    for (size_t i = 0; i < num.size(); ++i) {
        uint64_t carry = 0;
        for (size_t j = 0; j < otro.num.size() || carry; ++j) {
            //Se opera encima de la misma posicion del resultado, ya que por cada posicion de un numero se calcula un producto, que ambos se suman
            uint64_t temp = resultado[i + j] + num[i] * (j < otro.num.size() ? otro.num[j] : 0) + carry;
            resultado[i + j] = temp % 16;
            carry = temp / 16;
        }
    }

    while (!resultado.empty() && resultado.back() == 0) resultado.pop_back();

    Entero r("0x0");
    r.num = resultado;
    return r;
}

std::pair<Entero, Entero> Entero::dividir(Entero& otro) {
    Entero quotient("0x0");
    //std::vector<uint64_t> remainder = num; // Inicializamos el residuo con el dividendo
    Entero remainder("0x0");
    remainder.num = num;

    // Iteramos hasta que el residuo sea menor que el divisor
    while (remainder.num.size() >= otro.num.size()) {
        // Encontramos el cociente de la división
        uint64_t quotientDigit = 0;
        while (remainder.num >= otro.num) {
            remainder = remainder.restar(otro);
            //remainder = subtractHexVectors(remainder, divisor);
            ++quotientDigit;
        }
        quotient.num.push_back(quotientDigit);
    }

    return std::make_pair(quotient, remainder);
}
