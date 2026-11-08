# Receta: Ticket de compra

<!-- Escribe aquí tus recetas en pseudocódigo, ANTES de programar.
     Primero la receta del programa principal (main) y después una receta corta para cada módulo que vas a escribir tú.
     El primer paso de main es solo un ejemplo del formato; el resto es tuyo.
     Si las corriges después de probarlas a mano, deja aquí la versión final. -->

## Receta del programa principal (`main`)

<!-- Debe leerse casi igual que tu árbol de análisis descendente (sección 6 del README). -->

```text
1. MOSTRAR "Bienvenido a mi programa"
2. PEDIR el nombre del producto
3. PEDIR el precio hasta que sea mayor que 0
4. PEDIR la cantidad hasta que sea mayor que 0
5. PEDIR el porcentaje de descuento mientras este entre 0-99
6. CALCULAR el subtotal con el precio y la cantidad
7. CALCULAR el monto del descuento, con subtotal y el porcentaje
8. CALCULAR el IVA sobre el subtotal despues de aplicar el descuento
9. CALCULAR el total sumando el subtotal menos el descuento mas el IVA
10. MOSTRAR el ticket con los datos del producto y los importes
11. CERRAR el programa
```

## Recetas de los módulos

<!-- Para cada módulo: qué recibe, qué hace y qué devuelve. -->

### `calcularIVA`

```text
MODULO calcularIVA(subtotal, montoDescuento)
    DEVOLVER (subtotal - montoDescuento) * 0.16
FIN MODULO
```

### `imprimirTicket`

```text
MODULO imprimirTicket(nombre, cantidad, precio, subtotal,
                       montoDescuento, iva, total, porcentajeDescuento)
    MOSTRAR los datos del producto y los importes del ticket
FIN MODULO
```

### `calcularPorcentaje` (Fase 4)

```text
MODULO calcularPorcentaje(subtotal, porcentajeDescuento)
    DEVOLVER subtotal * porcentajeDescuento / 100
FIN MODULO
```

### Otros módulos que agregues (por ejemplo, para tu reto)

```text
MODULO calcularSubtotal(precio, cantidad)
    DEVOLVER precio * cantidad
FIN MODULO
```
