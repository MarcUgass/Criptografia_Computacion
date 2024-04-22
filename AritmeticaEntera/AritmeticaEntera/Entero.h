#include <iostream>
#include <vector>
#include <cstdint>
#include <string>

class Entero {
private:
    std::vector<uint64_t> num; // Vector que almacena los d�gitos del n�mero
    bool positivo; // Variable que indica si el n�mero es positivo o negativo
public:
    // Constructor que inicializa un objeto Entero a partir de una cadena
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
    void dividir(const Entero& dividendo, Entero& divisor, Entero& cociente, Entero& residuo);

    // Implementaci�n del algoritmo de Karatsuba para la multiplicaci�n de dos n�meros grandes
    Entero Karatsuba(Entero& n1, Entero& n2);

    //Implementaci�n del algoritmo Extendido de Euclides entre dos n�meros grandes
    void EuclidesExtendido(Entero& a, Entero& b, Entero& d, Entero& u, Entero& v);

    //Implemtanci�n de la oepraci�n exponenciaci�n modular r�pida 
    Entero ExponencialModularRapida(Entero& base, Entero& exponente, Entero& modulo);

    //Funci�n para devolver el modulo de dos numeros
    Entero modulo( Entero& m);

    //vector<bool> hexToBinaryVector(uint64_t hexValue);
    void girarIzquierda();

    //Funci�n que devuelve true, si un valor Entero es zero
    bool esCero() const;

    //Funci�n para combrobar si un valor Entero es mayor o Igual que otro
    bool esMayorOIgualQue(const Entero& otro) const;

    // M�todo para normalizar el n�mero, eliminando ceros no significativos
    void normalizar();

    // M�todo para obtener el m�ximo entre dos objetos Entero
    Entero obtenerMaximo(const Entero& otro) const;

    // M�todo para eliminar ceros no significativos de un objeto Entero
    void RemoveLeadingZeros(Entero& e);

    // M�todo para desplazar a la izquierda un objeto Entero un n�mero determinado de bits
    Entero ShiftLeft(const Entero& e, int shift);

    //Funciona muy parecido al esMayorOIGual, pero compara solo entre vectores, y devuelve tipo int, para hacer preubas con la funcion division
    int comparar(const std::vector<uint64_t>& a, const std::vector<uint64_t>& b);
};
