#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Estructura para almacenar nombre y salario de un empleado
struct Empleado {
    string nombre;
    int salario;
};

// Función para ajustar el montículo desde el nodo i hasta la raíz
void reajustarMonticulo(Empleado* empleados, int n, int i) {
    int mayor = i;
    int izquierda = 2 * i + 1;
    int derecha = 2 * i + 2;

    if (izquierda < n && empleados[izquierda].salario > empleados[mayor].salario)
        mayor = izquierda;

    if (derecha < n && empleados[derecha].salario > empleados[mayor].salario)
        mayor = derecha;

    if (mayor != i) {
        swap(empleados[i], empleados[mayor]);
        reajustarMonticulo(empleados, n, mayor);
    }
}

// Función para construir el montículo a partir de un arreglo de empleados
void construirMonticulo(Empleado* empleados, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        reajustarMonticulo(empleados, n, i);
    }
}

// Función para realizar el ordenamiento usando montículo
void ordenarPorMonticulo(Empleado* empleados, int n) {
    construirMonticulo(empleados, n);
    for (int i = n - 1; i > 0; i--) {
        swap(empleados[0], empleados[i]);
        reajustarMonticulo(empleados, i, 0);
    }
}

// Imprimir los empleados 
void imprimirResultados(Empleado* empleados, int n) {
    
    int anchoNombre = 20;
    int anchoSalario = 10;

    cout << "+----------------------+------------+" << endl;


    cout << "| " << "Nombre" << string(anchoNombre - 6, ' ')
         << " | " << "Salario" << string(anchoSalario - 7, ' ') << " |" << endl;

    cout << "+----------------------+------------+" << endl;

    for (int i = n - 1; i >= 0; i--) {
        cout << "| " << empleados[i].nombre 
             << string(anchoNombre - empleados[i].nombre.length(), ' ') << " | ";

        cout << empleados[i].salario 
             << string(anchoSalario - to_string(empleados[i].salario).length(), ' ') 
             << " |" << endl;
    }
    cout << "+----------------------+------------+" << endl;
}

int main() {
    int capacidad = 100;
    int n = 0;  
    Empleado* empleados = new Empleado[capacidad];

    ifstream archivo("salarios.txt"); // Archivo de entrada

    if (!archivo) {
        cerr << "No se pudo abrir el archivo de salarios." << endl;
        return 1;
    }

    string nombre;
    int salario;

    while (archivo >> nombre >> salario) {
        if (n == capacidad) {
            capacidad *= 2;
            Empleado* nuevoArray = new Empleado[capacidad];
            for (int i = 0; i < n; i++) {
                nuevoArray[i] = empleados[i];
            }
            delete[] empleados;
            empleados = nuevoArray;
        }

        empleados[n].nombre = nombre;
        empleados[n].salario = salario;
        n++;
    }

    archivo.close(); 

    // Ordenar los empleados por sus salarios 
    ordenarPorMonticulo(empleados, n);

 
    imprimirResultados(empleados, n);

    delete[] empleados;

    return 0;
}
