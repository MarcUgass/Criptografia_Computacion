
// AritmeticaEntera.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "Entero.h"
#include <chrono>
#include <sstream>

using namespace std;
using namespace std::chrono;

void mostrarMenu() {
    cout << "Seleccione una opcion:" << endl;
    cout << "1. Imprimir" << endl;
    cout << "2. Cambiar signo" << endl;
    cout << "3. Suma" << endl;
    cout << "4. Resta" << endl;
    cout << "5. Multiplicacion" << endl;
    cout << "6. Division" << endl;
    cout << "7. Karatsuba " << endl;
    cout << "8. Euclides Extendido " << endl;
    cout << "9. Exponenciacion modular rapida " << endl;
    cout << "10. Salir" << endl;
    cout << "Opcion: " << endl;
}

string generateHexDigits(int numDigits) {
    std::stringstream ss;
    srand(time(NULL)); // Semilla para números aleatorios

    for (int i = 0; i < numDigits; ++i) {
        int randomDigit = rand() % 16; // Generar un dígito hexadecimal aleatorio (entre 0 y 15)
        ss << std::hex << randomDigit; // Agregar el dígito hexadecimal a la cadena
    }

    return ss.str(); // Devolver la cadena hexadecimal generada
}

int main()
{
    int op = 0;
    std::string hexadecimal = "0xfd0456c3831c20cda400d540b";
    Entero entero(hexadecimal);
    
    //Operaciones básicas
    int c = 100;
    pair<string, string> operaciones = make_pair("0x"+ generateHexDigits(c), "0x" + generateHexDigits(c));
    
    //aritméticas basicas
    Entero operaciones1(operaciones.first);
    Entero operaciones2(operaciones.second);

    Entero resultado("0x0");

    //división
    int m = 100; //Digitos de divisón
    int n = m / 2;
    Entero dividendo("0x" + generateHexDigits(m));
    Entero divisor("0x" + generateHexDigits(n));
    Entero cociente("0x0");
    Entero residuo( "0x0");

    //Euclides Extendido
    int x = 10;
    Entero a("0x" + generateHexDigits(x));
    Entero b("0x0" + generateHexDigits(x));
    Entero d("0x0");
    Entero u("0x0");
    Entero v("0x0");

    //Exponenciación modular rápida
    int exp = 3;
    //Entero base("0x" + generateHexDigits(exp));
    //Entero exponente("0x" + generateHexDigits(exp));
    //Entero modulo("0x" + generateHexDigits(exp));

    Entero base("0x25");
    Entero exponente("0x37");
    Entero modulo("0x221");


    // Registra el tiempo de inicio


    mostrarMenu();
    cin >> op;
    auto start = high_resolution_clock::now();
    switch (op) {
    case 1:
        entero.imprimirHexadecimal();
        break;
    case 2:
        entero.cambiarSigno();
        entero.imprimirHexadecimal();
        break;
    case 3:
        resultado = operaciones1.sumar(operaciones2);
        resultado.imprimirHexadecimal();

        break;
    case 4:
        resultado = operaciones1.restar(operaciones2);
        resultado.imprimirHexadecimal();
        break;
    case 5:
        resultado = operaciones1.multiplicar(operaciones2);
        resultado.imprimirHexadecimal();
        break;
    case 6:
        cociente.dividir(dividendo,divisor,cociente, residuo);
        cociente.imprimirHexadecimal();
        residuo.imprimirHexadecimal();
    case 7:
        resultado = operaciones1.Karatsuba(operaciones1, operaciones2);
        resultado.imprimirHexadecimal();
        break;
    case 8:
        a.EuclidesExtendido(a, b, d, u, v);
        d.imprimirHexadecimal();
        u.imprimirHexadecimal();
        v.imprimirHexadecimal();
    case 9:
        resultado = base.ExponencialModularRapida(base, exponente, modulo);
        resultado.imprimirHexadecimal();
    }


    // Registra el tiempo de finalización
    auto end = high_resolution_clock::now();

    // Calcula la duración del tiempo transcurrido
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Duracion: " << duration.count();

    return 0;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
