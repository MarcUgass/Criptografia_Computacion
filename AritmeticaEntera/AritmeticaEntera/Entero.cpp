#include "Entero.h"
#include <utility>
#include <bitset>

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
    Entero a_low("0x0"), a_high("0x0"), b_low("0x0"), b_high("0x0");
    vector<uint64_t> va_low(n1.num.begin(), n1.num.begin() + half);
    vector<uint64_t> va_high(n1.num.begin() + half, n1.num.end());
    vector<uint64_t> vb_low(n2.num.begin(), n2.num.begin() + half);
    vector<uint64_t> vb_high(n2.num.begin() + half, n2.num.end());
    a_low.num = va_low;
    a_high.num = va_high;
    b_low.num = vb_low;
    b_high.num = vb_high;

    // Realiza las multiplicaciones recursivas
    Entero z0 = Karatsuba(a_low, b_low);
    Entero z2 = Karatsuba(a_high, a_low);
    Entero aux0 = a_low.sumar(a_high);
    Entero aux1 = b_low.sumar(b_high);
    Entero aux2 = Karatsuba(aux0, aux1);

    // Calcula los términos intermedios
    aux0 = aux2.restar(z0);
    Entero z1 = aux0.restar(z2);

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


// Función para realizar la división hexadecimal
void Entero::dividir(const Entero& dividendo, Entero& divisor, Entero& cociente, Entero& residuo) {
    cociente.num.clear();
    residuo = dividendo;

    int tamanoDivisor = divisor.num.size();

    while (residuo.num.size() >= tamanoDivisor && cociente.num.size() < divisor.num.size()) {
        // Encontrar el dígito más significativo del cociente
        int i = residuo.num.size() - tamanoDivisor;
        uint64_t q = 0;

        // Realizar la división para el dígito actual
        while (i > 0) {
            // Calcular el residuo parcial
            std::vector<uint64_t> residuoParcial(residuo.num.begin() + i, residuo.num.begin() + i + tamanoDivisor);
            Entero rp("0x0");
            rp.num = residuoParcial;
            while (residuoParcial.size() < tamanoDivisor + 1)
                residuoParcial.insert(residuoParcial.begin(), 0);

            // Calcular el dígito del cociente
            q = 0;
            while (comparar(residuoParcial, divisor.num) >= 0) {
                q++;
                rp = rp.restar(divisor);
            }

            // Actualizar el cociente y el residuo
            cociente.num.push_back(q);
            residuo.num.erase(residuo.num.begin() + i, residuo.num.begin() + i + tamanoDivisor);
            residuo.num.insert(residuo.num.begin() + i, residuoParcial.begin() + 1, residuoParcial.end());

            // Actualizar el índice
            i--;
        }
    }
}

void Entero::EuclidesExtendido(Entero& a, Entero& b, Entero& d, Entero& u, Entero& v) {
    // Algoritmo de Euclides Extendido para encontrar el máximo común divisor y los coeficientes
    // de Bézout.
    if (b.esCero()) {
        // Si b es cero, entonces el máximo común divisor es a, y los coeficientes son 1 y 0.
        d = a;
        u = Entero("0x1");
        v = Entero("0x0");
        return;
    }

    // Inicialización de variables necesarias para el algoritmo.
    Entero x0("0x1"), x1("0x0"), y0("0x0"), y1("0x1"), q("0x0"), r("0x0"), x("0x0"), y("0x0"), aux0("0x0");
    pair<Entero, Entero> result = make_pair(q, r);
    Entero num1 = a;
    Entero num2 = b;

    // Algoritmo de Euclides Extendido.
    while (!num2.esCero()) {
        //result = num1.dividir(num2);
        dividir(num1, num2, result.first, result.second);
        aux0 = result.first.multiplicar(x1);
        x = x0.restar(aux0);

        aux0 = result.first.multiplicar(y1);
        y = y0.restar(aux0);
        num1 = num2;
        num2 = result.second;
        x0 = x1;
        x1 = x;
        y0 = y1;
        y1 = y;
    }

    // Asignación de los resultados obtenidos.
    d = num1;
    u = x0;
    v = y0;
}

// Implementación de la operación exponenciación modular rápida.
Entero Entero::ExponencialModularRapida(Entero& base, Entero& exponente, Entero& modulo) {
    // Inicialización del resultado.
    Entero resultado("0x1");
    //base = base.obtenerMaximo(modulo);
    vector<bool> cadena_binarios;
    exponente.normalizar();

    // Conversión del exponente a binario.
    for (uint64_t i = 0; i < exponente.num.size(); i++) {
        bitset<4> bits(exponente.num[i]);
        std::vector<bool> binaryVector;
        for (int i = 3; i >= 0; --i) {
            binaryVector.push_back(bits[i]);
        }
        cadena_binarios.insert(cadena_binarios.end(), binaryVector.begin(), binaryVector.end());
    }

    // Algoritmo de exponenciación modular rápida.
    for (int i = 0; i < cadena_binarios.size(); i++) {
        //En el caso del bit de posición es 1, se multiplica la base por el resultado y se hace el modulo
        if (cadena_binarios[i] == true) {
            resultado = resultado.multiplicar(base);
            resultado = resultado.modulo(modulo);
        }
            base = base.multiplicar(base);
            base = base.modulo(modulo);

    }
    return resultado;
}

// Implementación de la operación módulo.
Entero Entero::modulo(Entero& m) {
    Entero copia("0x0");
    copia.num = this->num;

    while (copia.esMayorOIgualQue(m)) {
        copia = copia.restar(m);
        copia.girarIzquierda();
        RemoveLeadingZeros(copia);
    }
    return copia;
}


void Entero::girarIzquierda() {
    // Si el vector de dígitos está vacío o tiene un solo dígito, no es necesario girar
    if (num.size() <= 1) {
        return;
    }

    // Guardar el primer dígito para reinsertarlo al final después de girar
    while (num[0] == 0) { //Itera los valores que estan enfrente del numero, `ya que son los menos significativos
        uint64_t primerDigito = num.front();
        // Mover todos los dígitos una posición hacia la izquierda
        for (size_t i = 0; i < num.size() - 1; ++i) {
            num[i] = num[i + 1];
        }

        // Insertar el primer dígito al final del vector
        num.back() = primerDigito;
    }
}
//Función que devuelve true, si un valor Entero es zero
bool Entero::esCero() const {
    return (num.size() == 1 && num[0] == 0);
}

//Función para combrobar si un valor Entero es mayor o Igual que otro
bool Entero::esMayorOIgualQue(const Entero& otro) const {
    // Normalizar ambos números para eliminar ceros no significativos
    Entero esteAbsoluto = *this;
    //esteAbsoluto.normalizar();
    Entero otroAbsoluto = otro;
    //otroAbsoluto.normalizar();

    // Comparar el tamaño de los vectores de dígitos
    if (esteAbsoluto.num.size() > otroAbsoluto.num.size()) {
        return true;
    }
    else if (esteAbsoluto.num.size() < otroAbsoluto.num.size()) {
        return false;
    }

    // Si tienen el mismo número de dígitos, comparar cada dígito
    for (int i = esteAbsoluto.num.size() - 1; i >= 0; --i) {
        if (esteAbsoluto.num[i] > otroAbsoluto.num[i]) {
            return true;
        }
        else if (esteAbsoluto.num[i] < otroAbsoluto.num[i]) {
            return false;
        }
    }

    // Si llegamos aquí, ambos números son iguales
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

int Entero::comparar(const std::vector<uint64_t>& a, const std::vector<uint64_t>& b) {
    int tamanoA = a.size();
    int tamanoB = b.size();

    if (tamanoA > tamanoB)
        return 1;
    else if (tamanoA < tamanoB)
        return -1;
    else {
        for (int i = tamanoA - 1; i >= 0; --i) {
            if (a[i] > b[i])
                return 1;
            else if (a[i] < b[i])
                return -1;
        }
        return 0;
    }
}