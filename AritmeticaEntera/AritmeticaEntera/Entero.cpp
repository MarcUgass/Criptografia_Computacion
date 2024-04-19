#include "Entero.h"
#include <utility>

using namespace std;

// Constructor de la clase Entero que inicializa el objeto a partir de una cadena hexadecimal
Entero::Entero(const std::string& valor) {
    // Verifica si el valor es negativo
    if (valor.substr(0, 3) == "-0x") {
        positivo = false;
        std::string numero_hex = valor.substr(3); // Obtiene la parte del número hexadecimal
        std::reverse(numero_hex.begin(), numero_hex.end()); // Invierte la cadena para facilitar la manipulación
        // Convierte cada dígito hexadecimal en un entero y lo agrega al vector num
        for (size_t i = 0; i < numero_hex.length(); ++i) {
            num.push_back(hexCharToUint(numero_hex[i]));
        }
    }
    // Verifica si el valor es positivo
    else if (valor.substr(0, 2) == "0x") {
        positivo = true;
        std::string numero_hex = valor.substr(2); // Obtiene la parte del número hexadecimal
        std::reverse(numero_hex.begin(), numero_hex.end()); // Invierte la cadena para facilitar la manipulación
        // Convierte cada dígito hexadecimal en un entero y lo agrega al vector num
        for (size_t i = 0; i < numero_hex.length(); ++i) {
            num.push_back(hexCharToUint(numero_hex[i]));
        }
    }
}

// Método para imprimir el número en formato hexadecimal
void Entero::imprimirHexadecimal() const {
    // Imprime el signo si el número es negativo
    if (!positivo)
        std::cout << "-";
    std::cout << "0x";

    // Imprime cada dígito hexadecimal del número
    for (auto it = num.rbegin(); it != num.rend(); ++it) {
        std::cout << uintToHexChar(*it);
    }
    std::cout << std::endl;
}

// Método que convierte un carácter hexadecimal en un entero sin signo
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

// Método que convierte un entero sin signo en un carácter hexadecimal
char Entero::uintToHexChar(uint64_t n) const {
    if (n >= 0 && n <= 9)
        return '0' + n;
    else if (n >= 10 && n <= 15)
        return 'A' + (n - 10);
    else
        return 0;
}

// Método para cambiar el signo del número
void Entero::cambiarSigno() {
    positivo = !positivo;
}

// Método para normalizar el número, eliminando ceros no significativos
void Entero::normalizar() {
    while (num.size() > 1 && num.back() == 0) {
        num.pop_back(); // Elimina ceros no significativos del final del vector
    }
    if (num.size() == 1 && num[0] == 0) {
        positivo = true; // Si el número es 0, se establece como positivo
    }
}

// Método para obtener el máximo entre dos objetos Entero
Entero Entero::obtenerMaximo(const Entero& otro) const {
    // Compara las longitudes de los vectores de dígitos
    if (num.size() > otro.num.size())
        return *this; // Devuelve este objeto si tiene más dígitos
    else if (num.size() < otro.num.size())
        return otro; // Devuelve el otro objeto si tiene más dígitos
    else {
        // Si los vectores tienen la misma longitud, compara los dígitos de mayor a menor
        for (int i = num.size() - 1; i >= 0; --i) {
            if (num[i] > otro.num[i])
                return *this; // Devuelve este objeto si tiene un dígito mayor
            else if (num[i] < otro.num[i])
                return otro; // Devuelve el otro objeto si tiene un dígito mayor
        }
        return *this; // Devuelve este objeto si son iguales
    }
}

// Método para sumar dos objetos Entero
Entero Entero::sumar(Entero& otro) {
    if (positivo == otro.positivo) {

        // Suma de números con el mismo signo
        Entero resultado("0x0"); // Inicializa el resultado como 0
        uint64_t carry = 0; // Inicializa el acarreo como 0
        size_t i = 0;

        // Realiza la suma de dígitos mientras haya dígitos o acarreo
        while (i < num.size() || i < otro.num.size() || carry) {
            if (i == resultado.num.size())
                resultado.num.push_back(0); // Agrega un nuevo dígito al resultado si es necesario
            // Suma los dígitos más el acarreo, teniendo en cuenta la posibilidad de que los vectores sean de diferentes longitudes
            uint64_t sum = carry + (i < num.size() ? num[i] : 0) + (i < otro.num.size() ? otro.num[i] : 0);
            resultado.num[i] = sum % 16; // Guarda el dígito en la posición correspondiente del resultado
            carry = sum / 16; // Actualiza el acarreo
            ++i;
        }
        resultado.positivo = positivo; // Establece el signo del resultado como el mismo que los operandos
        return resultado;
    }
    else {
        // Si los números tienen signos opuestos, realiza la resta
        return restar(otro);
    }
}

// Método para restar dos objetos Entero
Entero Entero::restar(Entero& otro) {
    Entero resultado("0x0"); // Inicializa el resultado como 0
    uint64_t carry = 0; // Inicializa el acarreo como 0

    // Ajusta los vectores para que tengan la misma longitud agregando ceros a la izquierda
    int maxSize = std::max(num.size(), otro.num.size());
    while (num.size() < maxSize) num.push_back(uint64_t(0));
    while (otro.num.size() < maxSize) otro.num.push_back(uint64_t(0));

    // Realiza la resta de dígitos
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
        resultado.num.push_back(diff); // Agrega el dígito al resultado
    }

    // Elimina ceros no significativos del resultado
    while (!resultado.num.empty() && resultado.num.back() == 0) resultado.num.pop_back();
    return resultado;
}

// Método para multiplicar dos objetos Entero
Entero Entero::multiplicar(Entero& otro) {
    std::vector<uint64_t> resultado(num.size() + otro.num.size(), 0); // Inicializa el vector resultado con ceros

    // Realiza la multiplicación de dígitos
    for (size_t i = 0; i < num.size(); ++i) {
        uint64_t carry = 0; // Inicializa el acarreo como 0
        for (size_t j = 0; j < otro.num.size() || carry; ++j) {
            // Calcula el producto y el acarreo, y lo suma al resultado parcial
            uint64_t temp = resultado[i + j] + num[i] * (j < otro.num.size() ? otro.num[j] : 0) + carry;
            resultado[i + j] = temp % 16; // Guarda el dígito correspondiente del resultado
            carry = temp / 16; // Actualiza el acarreo
        }
    }

    // Elimina ceros no significativos del resultado
    while (!resultado.empty() && resultado.back() == 0) resultado.pop_back();

    Entero r("0x0"); // Crea un objeto Entero para almacenar el resultado
    r.num = resultado; // Asigna el vector resultado al número del objeto
    return r; // Devuelve el objeto Entero con el resultado de la multiplicación
}


//Este código implementa el algoritmo de multiplicación Karatsuba para números enteros grandes.
Entero Entero::Karatsuba(Entero& n1, Entero& n2) {
    // Calcula el tamaño total de los números a multiplicar
    int n = n1.num.size() + n2.num.size();
    Entero resultado("0x0");

    // Si el tamaño total es pequeño, utiliza la multiplicación normal
    if (n <= 4) {
        resultado = n1.multiplicar(n2);
        RemoveLeadingZeros(resultado);
        return resultado;
    }

    // Divide los números en mitades
    int half = n1.num.size() / 2;
    Entero a_low("0x0"), a_high("0x0"), b_low("0x0"), b_high("0x0"), z0("0x0"), z1("0x0"), z2("0x0"), aux0("0x0"), aux1("0x0"), aux2("0x0");
    vector<uint64_t> va_low(n1.num.begin(), n1.num.begin() + half);
    vector<uint64_t> va_high(n1.num.begin() + half, n1.num.end());
    vector<uint64_t> vb_low(n2.num.begin(), n2.num.begin() + half);
    vector<uint64_t> vb_high(n2.num.begin() + half, n2.num.end());
    a_low.num = va_low;
    a_high.num = va_high;
    b_low.num = vb_low;
    b_high.num = vb_high;

    // Realiza las multiplicaciones recursivas
    z0 = Karatsuba(a_low, b_low);
    z2 = Karatsuba(a_high, a_low);
    aux0 = a_low.sumar(a_high);
    aux1 = b_low.sumar(b_high);
    aux2 = Karatsuba(aux0, aux1);

    // Calcula los términos intermedios
    aux0 = aux2.restar(z0);
    z1 = aux0.restar(z2);

    // Realiza los desplazamientos necesarios
    aux0 = ShiftLeft(z2, 2 * half);
    aux1 = ShiftLeft(z1, half);

    // Suma los términos para obtener el resultado final
    aux2 = aux0.sumar(aux1);
    resultado = aux2.sumar(z0);

    // Remueve ceros no significativos del resultado
    RemoveLeadingZeros(resultado);
    return resultado;
}

std::tuple<Entero, Entero, Entero> Entero::EuclideanExtendido(const Entero& a, const Entero& b) {
    if (b.num.size() == 0)
        return std::make_tuple(a, Entero("1"), Entero("0"));

    Entero x1("0"), y1("1"), x2("1"), y2("0");
    Entero q, r, x, y;

    while (!(b.num.size() == 0)) {
        std::tie(q, r) = a.dividir(b);
        x = x1.restar(q.multiplicar(x2));
        y = y1.restar(q.multiplicar(y2));
        a = b;
        b = r;
        x1 = x2;
        y1 = y2;
        x2 = x;
        y2 = y;
    }

    return std::make_tuple(a, x1, y1);
}

std::pair<Entero, Entero> Entero::dividir(Entero& divisor) {

    // Realizar la división larga
    Entero dividendo(*this); // Hacemos una copia del dividendo
    Entero cociente("0x0");
    Entero resto("0x0");
    Entero aux0("0x0");
    Entero aux1("0x0");

    // Verificar si el divisor es cero
    if (divisor.num.size() == 0) {
        std::cerr << "Error: División por cero." << std::endl;
        return std::make_pair(cociente, resto); // Se podría lanzar una excepción en lugar de retornar un valor predeterminado
    }

    // Normalizamos los números para eliminar los ceros no significativos
    RemoveLeadingZeros(dividendo);
    Entero divisorAbs = divisor;
    divisorAbs.positivo = true;
    RemoveLeadingZeros(divisorAbs);

    // Iteramos mientras el dividendo sea mayor o igual que el divisor
    while (!dividendo.esMayorOIgualQue(divisorAbs)) {
        // Obtenemos la parte del dividendo que vamos a dividir
        Entero tempDividendo = dividendo.obtenerMaximo(divisorAbs);

        int k = 0;
        // Realizamos la división por sustracción
        while (tempDividendo.esMayorOIgualQue(divisorAbs) && k < divisor.num.size()) {
            tempDividendo = tempDividendo.restar(divisorAbs);
            k++;
        }

        // Agregamos el cociente parcial al cociente final
        cociente.num.push_back(k);
        RemoveLeadingZeros(cociente);

        // Multiplicamos el divisor absoluto por el dígito actual del cociente
        string aux2 = "0x" + std::to_string(k);
        aux0 = Entero(aux2);
        aux1 = divisorAbs.multiplicar(aux0);
        
        // Restamos el resultado de la multiplicación del dividendo
        dividendo = dividendo.restar(aux1);
        RemoveLeadingZeros(dividendo);
    }

    // El resto es lo que queda del dividendo
    resto = dividendo;
    return std::make_pair(cociente, resto);
}


//Función para combrobar si un valor Entero es mayor o Igual que otro
bool Entero::esMayorOIgualQue(const Entero& otro) const {
    // Comprobar la cantidad de dígitos
    if (num.size() != otro.num.size()) {
        // El número con más dígitos es mayor si ambos tienen el mismo signo
        return (positivo && num.size() > otro.num.size()) || (!positivo && num.size() < otro.num.size());
    }

    // Comprobar los dígitos uno por uno
    for (int i = num.size() - 1; i >= 0; --i) {
        if (num[i] != otro.num[i]) {
            // Si encontramos un dígito diferente, podemos determinar cuál número es mayor
            return (positivo && num[i] > otro.num[i]) || (!positivo && num[i] < otro.num[i]);
        }
    }

    // Si llegamos hasta aquí, ambos números son iguales
    return true;
}


// Función para remover ceros no significativos de un número entero
void Entero::RemoveLeadingZeros(Entero& e) {
    while (e.num.size() > 1 && e.num.back() == 0) {
        e.num.pop_back();
    }
}

// Función para desplazar un número entero hacia la izquierda
Entero Entero::ShiftLeft(const Entero& e, int shift) {
    Entero resultado("0x0");
    vector<uint64_t> result(e.num.size() + shift, 0);
    resultado.num = result;
    copy(e.num.begin(), e.num.end(), resultado.num.begin() + shift);
    return resultado;
}