#pragma once

#include <iostream>
#include <string>

// Recibe: el precio de un producto y la cantidad comprada.
// Devuelve: el subtotal (precio por cantidad).
inline double calcularSubtotal(double precio, int cantidad) {
    return precio * cantidad;
}

// Recibe: el subtotal y el porcentaje de descuento (de 0 a 100).
// Devuelve: el monto del descuento en pesos.
// OJO: esta funcion tiene un error escondido a proposito. Lee la Fase 3.
inline double calcularDescuento(double subtotal, double porcentaje) {
    return subtotal * porcentaje /100;
}
// TODO: calcularIVA
//       ¿Qué recibe? ¿Qué devuelve? ¿Dónde guardas la tasa del 16 %?

inline double calcularIVA (double subtotal, double montoDescuento, double iva) {
    return subtotal - montoDescuento + iva;
}

// TODO: imprimirTicket
//       ¿Es función o procedimiento? ¿Qué datos necesita para imprimir el ticket?
