#include "Entero.h"
#include <utility>

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
    Entero resultado("0x0"); // Inicializa el resultado como 0
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


//Este c�digo implementa el algoritmo de multiplicaci�n Karatsuba para n�meros enteros grandes.
Entero Entero::Karatsuba(Entero& n1, Entero& n2) {
    // Calcula el tama�o total de los n�meros a multiplicar
    int n = n1.num.size() + n2.num.size();
    Entero resultado("0x0");

    // Si el tama�o total es peque�o, utiliza la multiplicaci�n normal
    if (n <= 4) {
        resultado = n1.multiplicar(n2);
        RemoveLeadingZeros(resultado);
        return resultado;
    }

    // Divide los n�meros en mitades
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

    // Calcula los t�rminos intermedios
    aux0 = aux2.restar(z0);
    z1 = aux0.restar(z2);

    // Realiza los desplazamientos necesarios
    aux0 = ShiftLeft(z2, 2 * half);
    aux1 = ShiftLeft(z1, half);

    // Suma los t�rminos para obtener el resultado final
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

    // Realizar la divisi�n larga
    Entero dividendo(*this); // Hacemos una copia del dividendo
    Entero cociente("0x0");
    Entero resto("0x0");
    Entero aux0("0x0");
    Entero aux1("0x0");

    // Verificar si el divisor es cero
    if (divisor.num.size() == 0) {
        std::cerr << "Error: Divisi�n por cero." << std::endl;
        return std::make_pair(cociente, resto); // Se podr�a lanzar una excepci�n en lugar de retornar un valor predeterminado
    }

    // Normalizamos los n�meros para eliminar los ceros no significativos
    RemoveLeadingZeros(dividendo);
    Entero divisorAbs = divisor;
    divisorAbs.positivo = true;
    RemoveLeadingZeros(divisorAbs);

    // Iteramos mientras el dividendo sea mayor o igual que el divisor
    while (!dividendo.esMayorOIgualQue(divisorAbs)) {
        // Obtenemos la parte del dividendo que vamos a dividir
        Entero tempDividendo = dividendo.obtenerMaximo(divisorAbs);

        int k = 0;
        // Realizamos la divisi�n por sustracci�n
        while (tempDividendo.esMayorOIgualQue(divisorAbs) && k < divisor.num.size()) {
            tempDividendo = tempDividendo.restar(divisorAbs);
            k++;
        }

        // Agregamos el cociente parcial al cociente final
        cociente.num.push_back(k);
        RemoveLeadingZeros(cociente);

        // Multiplicamos el divisor absoluto por el d�gito actual del cociente
        string aux2 = "0x" + std::to_string(k);
        aux0 = Entero(aux2);
        aux1 = divisorAbs.multiplicar(aux0);
        
        // Restamos el resultado de la multiplicaci�n del dividendo
        dividendo = dividendo.restar(aux1);
        RemoveLeadingZeros(dividendo);
    }

    // El resto es lo que queda del dividendo
    resto = dividendo;
    return std::make_pair(cociente, resto);
}


//Funci�n para combrobar si un valor Entero es mayor o Igual que otro
bool Entero::esMayorOIgualQue(const Entero& otro) const {
    // Comprobar la cantidad de d�gitos
    if (num.size() != otro.num.size()) {
        // El n�mero con m�s d�gitos es mayor si ambos tienen el mismo signo
        return (positivo && num.size() > otro.num.size()) || (!positivo && num.size() < otro.num.size());
    }

    // Comprobar los d�gitos uno por uno
    for (int i = num.size() - 1; i >= 0; --i) {
        if (num[i] != otro.num[i]) {
            // Si encontramos un d�gito diferente, podemos determinar cu�l n�mero es mayor
            return (positivo && num[i] > otro.num[i]) || (!positivo && num[i] < otro.num[i]);
        }
    }

    // Si llegamos hasta aqu�, ambos n�meros son iguales
    return true;
}


// Funci�n para remover ceros no significativos de un n�mero entero
void Entero::RemoveLeadingZeros(Entero& e) {
    while (e.num.size() > 1 && e.num.back() == 0) {
        e.num.pop_back();
    }
}

// Funci�n para desplazar un n�mero entero hacia la izquierda
Entero Entero::ShiftLeft(const Entero& e, int shift) {
    Entero resultado("0x0");
    vector<uint64_t> result(e.num.size() + shift, 0);
    resultado.num = result;
    copy(e.num.begin(), e.num.end(), resultado.num.begin() + shift);
    return resultado;
}