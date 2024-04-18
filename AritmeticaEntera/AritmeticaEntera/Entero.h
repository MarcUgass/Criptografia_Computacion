#include <iostream>
#include <vector>
#include <cstdint>
#include <string>

class Entero {
private:
    std::vector<uint64_t> num; // Vector que almacena los d�gitos del n�mero
    bool positivo; // Bandera que indica si el n�mero es positivo o negativo
public:
    // Constructor que inicializa un objeto Entero a partir de una cadena hexadecimal
    Entero(const std::string& hexString);

    // M�todo para imprimir el n�mero en formato hexadecimal
    void imprimirHexadecimal() const;

    // M�todo que convierte un car�cter hexadecimal en un entero sin signo
    uint64_t hexCharToUint(char c) const;

    // M�todo que convierte un entero sin signo en un car�cter hexadecimal
    char uintToHexChar(uint64_t n) const;

    // M�todo para cambiar el signo del n�mero
    void cambiarSigno();

    // M�todo para sumar dos objetos Entero
    Entero sumar(Entero& otro);

    // M�todo para restar dos objetos Entero
    Entero restar(Entero& otro);

    // M�todo para multiplicar dos objetos Entero
    Entero multiplicar(Entero& otro);

    // M�todo para dividir dos objetos Entero, devuelve el cociente y el residuo
    std::pair<Entero, Entero> dividir(Entero& otro);

    // Implementaci�n del algoritmo de Karatsuba para la multiplicaci�n de dos n�meros grandes
    Entero Karatsuba(Entero& n1, Entero& n2);

    // M�todo para normalizar el n�mero, eliminando ceros no significativos
    void normalizar();

    // M�todo para obtener el m�ximo entre dos objetos Entero
    Entero obtenerMaximo(const Entero& otro) const;

    // M�todo para eliminar ceros no significativos de un objeto Entero
    void RemoveLeadingZeros(Entero& e);

    // M�todo para desplazar a la izquierda un objeto Entero un n�mero determinado de bits
    std::vector<uint64_t> ShiftLeft(const Entero& e, int shift);
};