#include <iostream>
#include <vector>
#include <cstdint>
#include <string>

class Entero {
private:
	std::vector<uint64_t> num;
	bool positivo;
public:
    Entero(const std::string& hexString);
    void imprimirHexadecimal() const;
    uint64_t hexCharToUint(char c) const;
    char uintToHexChar(uint64_t n) const;
    
    void cambiarSigno();
    Entero sumar( Entero& otro);
    Entero restar( Entero& otro);
    Entero multiplicar(Entero& otro);
    std::pair<Entero,Entero> dividir(Entero& otro);

    void normalizar();
    Entero obtenerMaximo(const Entero& otro) const;
};