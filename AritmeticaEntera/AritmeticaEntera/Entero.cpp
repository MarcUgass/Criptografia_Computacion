#include "Entero.h"

using namespace std;

// Constructor de la clase Entero que inicializa el objeto a partir de una cadena hexadecimal
Entero::Entero(const std::string& valor) {
    // Verifica si el valor es negativo
    if (valor.substr(0, 3) == "-0x") {
        positivo = false;
        std::string numero_hex = valor.substr(3); // Obtiene la parte del n�mero hexadecimal
        std::reverse(numero_hex.begin(), numero_hex.end()); // Invierte la cadena para facilitar la manipulaci�n
        // Convierte cada d�gito hexadecimal en un entero y lo agrega al vector num
        for (size_t i = 0; i < numero_hex.length(); ++i) {
            num.push_back(hexCharToUint(numero_hex[i]));
        }
    }
    // Verifica si el valor es positivo
    else if (valor.substr(0, 2) == "0x") {
        positivo = true;
        std::string numero_hex = valor.substr(2); // Obtiene la parte del n�mero hexadecimal
        std::reverse(numero_hex.begin(), numero_hex.end()); // Invierte la cadena para facilitar la manipulaci�n
        // Convierte cada d�gito hexadecimal en un entero y lo agrega al vector num
        for (size_t i = 0; i < numero_hex.length(); ++i) {
            num.push_back(hexCharToUint(numero_hex[i]));
        }
    }
}

// M�todo para imprimir el n�mero en formato hexadecimal
void Entero::imprimirHexadecimal() const {
    // Imprime el signo si el n�mero es negativo
    if (!positivo)
        std::cout << "-";
    std::cout << "0x";

    // Imprime cada d�gito hexadecimal del n�mero
    for (auto it = num.rbegin(); it != num.rend(); ++it) {
        std::cout << uintToHexChar(*it);
    }
    std::cout << std::endl;
}

// M�todo que convierte un car�cter hexadecimal en un entero sin signo
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

// M�todo que convierte un entero sin signo en un car�cter hexadecimal
char Entero::uintToHexChar(uint64_t n) const {
    if (n >= 0 && n <= 9)
        return '0' + n;
    else if (n >= 10 && n <= 15)
        return 'A' + (n - 10);
    else
        return 0;
}

// M�todo para cambiar el signo del n�mero
void Entero::cambiarSigno() {
    positivo = !positivo;
}

// M�todo para normalizar el n�mero, eliminando ceros no significativos
void Entero::normalizar() {
    while (num.size() > 1 && num.back() == 0) {
        num.pop_back(); // Elimina ceros no significativos del final del vector
    }
    if (num.size() == 1 && num[0] == 0) {
        positivo = true; // Si el n�mero es 0, se establece como positivo
    }
}

// M�todo para obtener el m�ximo entre dos objetos Entero
Entero Entero::obtenerMaximo(const Entero& otro) const {
    // Compara las longitudes de los vectores de d�gitos
    if (num.size() > otro.num.size())
        return *this; // Devuelve este objeto si tiene m�s d�gitos
    else if (num.size() < otro.num.size())
        return otro; // Devuelve el otro objeto si tiene m�s d�gitos
    else {
        // Si los vectores tienen la misma longitud, compara los d�gitos de mayor a menor
        for (int i = num.size() - 1; i >= 0; --i) {
            if (num[i] > otro.num[i])
                return *this; // Devuelve este objeto si tiene un d�gito mayor
            else if (num[i] < otro.num[i])
                return otro; // Devuelve el otro objeto si tiene un d�gito mayor
        }
        return *this; // Devuelve este objeto si son iguales
    }
}

// M�todo para sumar dos objetos Entero
Entero Entero::sumar(Entero& otro) {
    if (positivo == otro.positivo) {

        // Suma de n�meros con el mismo signo
        Entero resultado("0x0"); // Inicializa el resultado como 0
        uint64_t carry = 0; // Inicializa el acarreo como 0
        size_t i = 0;

        // Realiza la suma de d�gitos mientras haya d�gitos o acarreo
        while (i < num.size() || i < otro.num.size() || carry) {
            if (i == resultado.num.size())
                resultado.num.push_back(0); // Agrega un nuevo d�gito al resultado si es necesario
            // Suma los d�gitos m�s el acarreo, teniendo en cuenta la posibilidad de que los vectores sean de diferentes longitudes
            uint64_t sum = carry + (i < num.size() ? num[i] : 0) + (i < otro.num.size() ? otro.num[i] : 0);
            resultado.num[i] = sum % 16; // Guarda el d�gito en la posici�n correspondiente del resultado
            carry = sum / 16; // Actualiza el acarreo
            ++i;
        }
        resultado.positivo = positivo; // Establece el signo del resultado como el mismo que los operandos
        return resultado;
    }
    else {
        // Si los n�meros tienen signos opuestos, realiza la resta
        return restar(otro);
    }
}

// M�todo para restar dos objetos Entero
Entero Entero::restar(Entero& otro) {
    Entero resultado("0x"); // Inicializa el resultado como 0
    uint64_t carry = 0; // Inicializa el acarreo como 0

    // Ajusta los vectores para que tengan la misma longitud agregando ceros a la izquierda
    int maxSize = std::max(num.size(), otro.num.size());
    while (num.size() < maxSize) num.push_back(uint64_t(0));
    while (otro.num.size() < maxSize) otro.num.push_back(uint64_t(0));

    // Realiza la resta de d�gitos
    for (size_t i = 0; i < maxSize; ++i) {
        uint64_t diff;
        if (num[i] < (otro.num[i] + carry)) {
            // Si es necesario pedir prestado, ajusta el valor y el acarreo
            diff = 16 + num[i] - (otro.num[i] + carry);
            carry = 1;
        }
        else {
            // Si no es necesario pedir prestado, simplemente resta
            diff = num[i] - (otro.num[i] + carry);
            carry = 0;
        }
        resultado.num.push_back(diff); // Agrega el d�gito al resultado
    }

    // Elimina ceros no significativos del resultado
    while (!resultado.num.empty() && resultado.num.back() == 0) resultado.num.pop_back();
    return resultado;
}

// M�todo para multiplicar dos objetos Entero
Entero Entero::multiplicar(Entero& otro) {
    std::vector<uint64_t> resultado(num.size() + otro.num.size(), 0); // Inicializa el vector resultado con ceros

    // Realiza la multiplicaci�n de d�gitos
    for (size_t i = 0; i < num.size(); ++i) {
        uint64_t carry = 0; // Inicializa el acarreo como 0
        for (size_t j = 0; j < otro.num.size() || carry; ++j) {
            // Calcula el producto y el acarreo, y lo suma al resultado parcial
            uint64_t temp = resultado[i + j] + num[i] * (j < otro.num.size() ? otro.num[j] : 0) + carry;
            resultado[i + j] = temp % 16; // Guarda el d�gito correspondiente del resultado
            carry = temp / 16; // Actualiza el acarreo
        }
    }

    // Elimina ceros no significativos del resultado
    while (!resultado.empty() && resultado.back() == 0) resultado.pop_back();

    Entero r("0x0"); // Crea un objeto Entero para almacenar el resultado
    r.num = resultado; // Asigna el vector resultado al n�mero del objeto
    return r; // Devuelve el objeto Entero con el resultado de la multiplicaci�n
}


Entero Entero::Karatsuba(Entero& n1, Entero& n2) {
    int n = n1.num.size() + n2.num.size();
    Entero resultado("0x0");
    // Cuando el tama�o es peque�o se usa multiplicacion normals
    if (n <= 4) {
        resultado = n1.multiplicar(n2);
        RemoveLeadingZeros(resultado);
        return resultado;
    }
    int half = n / 2;

    Entero n11("0x0"), n12("0x0"), n21("0x0"), n22("0x0"), z0("0x0"), z1("0x0"), z2("0x0");
    vector<uint64_t> a1(n1.num.begin(), n1.num.begin() + min(half, int(n1.num.size())));
    vector<uint64_t> a0(n1.num.begin() + min(half, int(n1.num.size())), n1.num.end());
    vector<uint64_t> b1(n2.num.begin(), n2.num.begin() + min(half, int(n2.num.size())));
    vector<uint64_t> b0(n2.num.begin() + min(half, int(n2.num.size())), n2.num.end());

    n11.num = a1;
    n12.num = a0;
    n21.num = b1;
    n22.num = b0;

    z0 = Karatsuba(n12,n22);
    z2 = Karatsuba(n11,n21);
    Entero aux0 = n12.sumar(n11);
    Entero aux1 = n22.sumar(n21);
    Entero aux2 = Karatsuba(aux0, aux1);
    Entero aux3 = z0.restar(aux2);
    z1 = z2.restar(aux3);

    return z1;
}

void Entero::RemoveLeadingZeros(Entero& e) {
    while (e.num.size() > 1 && e.num.back() == 0) {
        e.num.pop_back();
    }
}

vector<uint64_t> Entero::ShiftLeft(const Entero& e, int shift) {
    vector<uint64_t> result(e.num.size() + shift, 0);
    copy(e.num.begin(), e.num.end(), result.begin() + shift);
    return result;
}

/*
vector<int> ShiftLeft(const vector<int>& num, int shift) {
    vector<int> result(num.size() + shift, 0);
    copy(num.begin(), num.end(), result.begin() + shift);
    return result;
}
*/

/*
std::pair<Entero, Entero> Entero::dividir(Entero& otro) {
    Entero quotient("0x0");
    //std::vector<uint64_t> remainder = num; // Inicializamos el residuo con el dividendo
    Entero remainder("0x0");
    remainder.num = num;

    // Iteramos hasta que el residuo sea menor que el divisor
    while (remainder.num.size() >= otro.num.size()) {
        // Encontramos el cociente de la divisi�n
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
*/