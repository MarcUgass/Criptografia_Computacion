
// AritmeticaEntera.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "Entero.h"
#include <chrono>

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
    cout << "10. Salir" << endl;
    cout << "Opcion: " << endl;
}
int main()
{
    int op = 0;
    std::string hexadecimal = "0x58436F83534A432C5342543C543F";
    Entero entero(hexadecimal);

    std::string op1 = "0x56A6532534ACD123554";
    std::string op2 = "0x75F353256A6532ADB23";
    Entero operaciones1(op1);
    Entero operaciones2(op2);
    Entero resultado("0x0");
    Entero residuo("0x0");

    // Registra el tiempo de inicio
    auto start = high_resolution_clock::now();

    mostrarMenu();
    cin >> op;
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
        //auto result = operaciones1.dividir(operaciones2);
        //result.first.imprimirHexadecimal();
        //result.second.imprimirHexadecimal();
    case 7:
        resultado = operaciones1.Karatsuba(operaciones1, operaciones2);
        resultado.imprimirHexadecimal();
        break;
    }


    // Registra el tiempo de finalización
    auto end = high_resolution_clock::now();

    // Calcula la duración del tiempo transcurrido
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Duración: " << duration.count();

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
