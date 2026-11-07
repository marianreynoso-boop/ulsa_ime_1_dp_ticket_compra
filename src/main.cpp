// Práctica: Ticket de compra
// main() solo coordina: pide los datos, llama a los módulos y muestra el ticket.
// Deja el comentario "// Paso N" sobre cada bloque, con la numeración de TU receta.
//
// Compilar (desde la carpeta del proyecto):
//   g++ -Wall -Wextra -std=c++17 -Iinclude src/main.cpp -o ticket
// Ejecutar:
//   macOS:   ./ticket
//   Windows: .\ticket.exe

// ¿Recuerdas qué hace iostream?
#include <iostream>
#include <string>

#include "utilerias.h"
#include "ticket.h"
void imprimirTicket(
    const std::string& nombre, int cantidad, double precio,
    double subtotal, double montoDescuento, double iva, double total,
    double porcentajeDescuento
) { 
     // Variables (siempre inicializadas)
    // TODO: ¿cuántas necesitas? ¿De qué tipo es cada una?
     std::cout << "\n---Ticket de Compra---\n"
                << "Producto: " << nombre << '\n'
                << "Cantidad: " << cantidad << '\n'
                << "Precio $: " << precio << '\n'
                << "Subtotal $: " << subtotal << '\n'
                << "Descuento: $ " << montoDescuento << '\n'
                << "Iva: $ " << iva << '\n'
                << "Total : $ " << total << '\n'
                << "Porcentaje Descuento : % " << porcentajeDescuento << '\n';
  }

int main() {
    // Paso 1: mensaje de bienvenida
    // TODO
    std::cout << "=== SISTEMA DE VENTAS MECATRONICA ===\n";

    // Paso 1: solicitar el nombre del producto
    std::string nombre = leerCadena("Ingrese el nombre del producto: ");
    // Paso 2: pedir y validar los datos
    // TODO: ¿qué función de utilerias.h usas para cada dato?
    //       ¿Cómo vuelves a pedir un dato que está fuera de rango?
          // Paso 2: solicitar y validar precio, cantidad y descuento
    double precio = leerDecimal("Ingrese el precio unitario: ");
    while (precio <= 0) {
        std::cout << "[ERROR] El precio debe ser mayor a 0. Ingréselo de nuevo.\n";
        precio = leerDecimal("Ingrese el precio unitario: ");
    }
    int cantidad = 0;
    cantidad = leerEntero("Ingrese la cantidad de piezas: ");
    while (cantidad <= 0) {
        std::cout << "[ERROR] La cantidad debe ser mayor a 0. Intente de nuevo.\n";
        cantidad = leerEntero("Ingrese la cantidad de piezas: ");
    }

    double porcentajeDescuento = leerDecimal("Ingrese el porcentaje de descuento (0-99): ");
    while (porcentajeDescuento < 0 || porcentajeDescuento > 99) {
        std::cout << "[ERROR] El descuento debe estar entre 0 y 99. Ingréselo de nuevo.\n";
        porcentajeDescuento = leerDecimal("Ingrese el porcentaje de descuento (0-99): ");
    }

    // Paso 3: calcular los importes llamando a los módulos de ticket.h
    // TODO
      // Paso 3: calcular los importes
     double subtotal = precio * cantidad;
     double montoDescuento = subtotal * porcentajeDescuento / 100.0;
     double iva = subtotal * 16.0 / 100.0; // IVA del 16%
     double total = subtotal + iva - montoDescuento;
    // Paso 4: imprimir el ticket
    // TODO

    imprimirTicket(nombre, cantidad, precio, subtotal, montoDescuento, iva, total, porcentajeDescuento);
    // ¿Qué significa return 0;?
    return 0;
}
