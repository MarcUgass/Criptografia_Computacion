#include <iostream>
#include <vector>
#include <cstdint>
#include <string>

class Entero {
private:
    std::vector<uint64_t> num; // Vector que almacena los dígitos del número
    bool positivo; // Variable que indica si el número es positivo o negativo
public:
    // Constructor que inicializa un objeto Entero a partir de una cadena
    Entero(const std::string& hexString);

    // Método para imprimir el número en formato hexadecimal
    void imprimirHexadecimal() const;

    // Método que convierte un carácter hexadecimal en un entero sin signo
    uint64_t hexCharToUint(char c) const;

    // Método que convierte un entero sin signo en un carácter hexadecimal
    char uintToHexChar(uint64_t n) const;

    // Método para cambiar el signo del número
    void cambiarSigno();

    // Método para sumar dos objetos Entero
    Entero sumar(Entero& otro);

    // Método para restar dos objetos Entero
    Entero restar(Entero& otro);

    // Método para multiplicar dos objetos Entero
    Entero multiplicar(Entero& otro);

    // Método para dividir dos objetos Entero, devuelve el cociente y el residuo
    void dividir(const Entero& dividendo, Entero& divisor, Entero& cociente, Entero& residuo);

    // Implementación del algoritmo de Karatsuba para la multiplicación de dos números grandes
    Entero Karatsuba(Entero& n1, Entero& n2);

    //Implementación del algoritmo Extendido de Euclides entre dos números grandes
    void EuclidesExtendido(Entero& a, Entero& b, Entero& d, Entero& u, Entero& v);

    //Implemtanción de la oepración exponenciación modular rápida 
    Entero ExponencialModularRapida(Entero& base, Entero& exponente, Entero& modulo);

    //Función para devolver el modulo de dos numeros
    Entero modulo( Entero& m);

    //vector<bool> hexToBinaryVector(uint64_t hexValue);
    void girarIzquierda();

    //Función que devuelve true, si un valor Entero es zero
    bool esCero() const;

    //Función para combrobar si un valor Entero es mayor o Igual que otro
    bool esMayorOIgualQue(const Entero& otro) const;

    // Método para normalizar el número, eliminando ceros no significativos
    void normalizar();

    // Método para obtener el máximo entre dos objetos Entero
    Entero obtenerMaximo(const Entero& otro) const;

    // Método para eliminar ceros no significativos de un objeto Entero
    void RemoveLeadingZeros(Entero& e);

    // Método para desplazar a la izquierda un objeto Entero un número determinado de bits
    Entero ShiftLeft(const Entero& e, int shift);

    //Funciona muy parecido al esMayorOIGual, pero compara solo entre vectores, y devuelve tipo int, para hacer preubas con la funcion division
    int comparar(const std::vector<uint64_t>& a, const std::vector<uint64_t>& b);
};
