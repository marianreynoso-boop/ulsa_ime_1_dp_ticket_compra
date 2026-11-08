# Práctica: Ticket de compra

> Llena cada sección en la fase que se indica. Las instrucciones completas están en `PRACTICA.md`.
> Si una pregunta no aplica (por ejemplo, no hiciste el Experimento C o no tuviste dudas), escribe `No aplica`. Si te sobran filas en una tabla, bórralas.

## 1. Descripción del problema (Fase 1)
<!-- Explica con tus palabras qué hace tu programa y para qué serviría en la vida real. Máximo 4 líneas. -->
El programa registra la compra de un producto: solicita su nombre, precio, cantidad y porcentaje de descuento. Después calcula y muestra el subtotal, el descuento, el IVA y el total en un ticket.

## 2. Entradas y salidas (Fase 1)
<!-- Define cada entrada y cada salida, con su tipo de dato y la función de utilerias.h con la que la vas a leer. -->

**Entradas:**

| Entrada | Tipo de dato | Función de `utilerias.h` |
|---|---|---|
| Nombre | `std::string` | `leerCadena` |
| Precio | double | leerDecimal |
| Cantidad | int | leerEntero |
| Descuento | double | leerDecimal |

**Salida** (¿qué datos muestra el ticket?):
Nombre del producto, cantidad, precio unitario, subtotal, monto y porcentaje de descuento, IVA y total.

**¿El IVA se calcula sobre el subtotal o sobre lo que queda después del descuento? ¿Por qué?**
Debe calcularse sobre lo que queda después de aplicar el descuento, porque el impuesto corresponde al valor que se paga. La implementación actual todavía calcula el IVA sobre el subtotal completo; hay que corregirla para que coincida con esta decisión.

## 3. Restricciones e invariante (Fases 1 y 2)

**Restricciones** (¿qué debe cumplirse?):

| Dato | ¿Qué valores son válidos? | ¿Por qué? |
|---|---|---|
| Nombre del producto | Texto no vacío; puede incluir espacios | Identifica el producto. `leerCadena` rechaza una entrada vacía. |
| Precio | Número finito mayor que 0; puede tener decimales | Representa el precio por unidad. |
| Cantidad | Número entero mayor que 0 | Indica cuántas piezas se compran. |
| Descuento (%) | Número entre 0 y 100, inclusive | Es el porcentaje que se resta del subtotal. El código actual acepta de 0 a 99, así que debe ajustarse para aceptar también 100. |

**¿Qué hace mi programa si el usuario escribe un dato fuera de rango?**
Muestra un mensaje de error y vuelve a pedirlo. Las funciones de `utilerias.h` también vuelven a preguntar cuando el formato del dato no es válido.

**¿Puede el total salir negativo? ¿Por qué?**
No. El descuento no puede superar el subtotal si el porcentaje está entre 0 y 100; por eso el total no debe ser negativo.

**Invariante 1** (después del ciclo que valida el precio, ¿qué es siempre cierto sobre `precio`?):
`precio > 0`.

**Invariante 2** (¿qué relación se cumple siempre entre el subtotal, el descuento, el IVA y el total?):
`total = subtotal - montoDescuento + IVA`, y `0 <= montoDescuento <= subtotal`. El IVA debe calcularse sobre `subtotal - montoDescuento`.

## 4. Casos resueltos a mano (Fase 1)

| Caso | Nombre | Precio | Cantidad | Descuento (%) | Subtotal | Descuento ($) | IVA (16 % después del descuento) | Total |
|---|---|---|---|---|---|---|---|---|
| 1 (sin descuento) | Cuaderno | $50.00 | 1 | 0 % | $50.00 | $0.00 | $8.00 | $58.00 |
| 2 (con descuento) | Cuaderno | $50.00 | 1 | 15 % | $50.00 | $7.50 | $6.80 | $49.30 |
| 3 (precio con centavos) | Pluma | $50.63 | 1 | 15 % | $50.63 | $7.5945 | $6.88568 | $49.92118 |

## 5. Tipo de dato abstracto (Fase 1)

| TDA | Datos (¿qué tiene?) | Operaciones (¿qué se puede hacer con él?) |
|---|---|---|
| Producto | nombre (texto), precio unitario, cantidad | calcular su subtotal |
| Ticket | nombre del producto, precio, cantidad, subtotal, descuento, IVA y total | calcular los importes y mostrar la compra |

**Jerarquías:** una tienda vende productos por pieza (un cuaderno) y productos por peso (un kilo de tortillas). ¿Los dos son productos? ¿Qué datos tienen en común y cuál cambia?
Sí. Ambos tienen nombre y precio; cambia la unidad o forma de expresar la cantidad, por piezas o por peso.

## 6. Análisis descendente (Fase 2)
<!-- Completa el árbol. Marca con (ya existe) las partes que ya resuelve una función de utilerias.h o de ticket.h. -->

```
Generar ticket de compra
├── 1. Mostrar bienvenida
├── 2. Pedir y validar los datos
│     ├── 2.1 Pedir el nombre del producto (leerCadena, ya existe)
│     ├── 2.2 Pedir el precio y validar que sea > 0 (leerDecimal, ya existe)
│     ├── 2.3 Pedir la cantidad y validar que sea > 0 (leerEntero, ya existe)
│     └── 2.4 Pedir el descuento y validar que esté entre 0 y 100 (leerDecimal, ya existe)
├── 3. Calcular los importes
│     ├── 3.1 Calcular el subtotal (calcularSubtotal, ya existe)
│     ├── 3.2 Calcular el monto del descuento (calcularDescuento, ya existe)
│     ├── 3.3 Calcular el IVA sobre el subtotal con descuento (calcularIVA, pendiente de corregir)
│     └── 3.4 Calcular el total
└── 4. Imprimir el ticket (imprimirTicket)
```

Este árbol describe el comportamiento deseado. En el código actual, `main` calcula los importes directamente y todavía no llama a `calcularSubtotal`, `calcularDescuento` ni `calcularIVA`.

**Análisis ascendente: ¿qué partes del árbol ya estaban resueltas por una función que existe? ¿Cuáles?**
`leerCadena`, `leerDecimal` y `leerEntero` ya leen y validan el formato de las entradas; `calcularSubtotal` y `calcularDescuento` ya existen en `ticket.h`. La bienvenida, las validaciones de rango, el IVA, el total y la impresión se completan en el programa.

**¿Alguna parte del árbol hacía más de una cosa? ¿Cómo la dividiste?**
Sí: pedir cada dato y validar su rango son tareas distintas. Las separé en la lectura y el ciclo que repite la pregunta mientras el valor esté fuera del rango.

## 7. Módulos y receta (Fase 2)

| Módulo | ¿Qué recibe? | ¿Qué devuelve? | ¿Función o procedimiento? |
|---|---|---|---|
| `calcularSubtotal` | precio, cantidad | el subtotal | Función |
| `calcularDescuento` | subtotal, porcentaje | el monto del descuento | Función |
| `calcularIVA` | En el diseño: subtotal y monto del descuento | IVA sobre el subtotal después del descuento | Función; la versión actual de `ticket.h` recibe tres parámetros y devuelve una expresión de total, así que debe corregirse |
| `imprimirTicket` | nombre, cantidad, precio, subtotal, descuento, IVA, total y porcentaje | No devuelve un valor; muestra el ticket | Procedimiento (`void`) |
| `calcularPorcentaje` (propuesta para Fase 4) | cantidad base y porcentaje | el monto correspondiente al porcentaje | Función; pendiente de implementar |

<!-- Tu receta va en el archivo RECETA.md. Aquí solo responde las preguntas. -->

**¿Probé mi receta a mano con mis 3 casos?** Sí 
**¿Tuve que corregirla? ¿Qué cambié?** cambie lo de los modulos

## 8. Cómo compilar y ejecutar (Fase 3)

Compilar (desde la carpeta del proyecto):

```bash
g++ -Wall -Wextra -std=c++17 -Iinclude src/main.cpp -o ticket
```

Ejecutar en macOS:

```bash
./ticket
```

Ejecutar en Windows:

```bash
.\ticket.exe
```

**¿En qué sistema operativo trabajé?** Windows.

## 9. Ejemplo de ejecución (Fase 3)
<!-- Pega aquí lo que muestra tu programa en pantalla con el caso 2 de la tabla de pruebas (Cuaderno, 50, 2, 10). -->

```
---Ticket de Compra---
Producto: Cuaderno
Cantidad: 2
Precio $: 50
Subtotal $: 100
Descuento: $ 10
Iva: $ 16
Total : $ 106
Porcentaje Descuento : % 10
```

Este resultado corresponde al cálculo que hace actualmente `main.cpp`. No coincide con el resultado esperado de la guía porque el código calcula el IVA sobre el subtotal completo, en vez de calcularlo después del descuento.

## 10. De la receta al código (Fase 3)
<!-- Para cada paso de TU receta, escribe el módulo o la instrucción de C++ que lo implementa. Agrega las filas que necesites. -->

| Paso de la receta | Módulo o instrucción de C++ que lo implementa |
|---|---|
| Mostrar la bienvenida | `std::cout << "=== SISTEMA DE VENTAS MECATRONICA ===\n";` |
| Pedir el nombre | `leerCadena(...)` |
| Pedir y validar el precio | `leerDecimal(...)` y `while (precio <= 0)` |
| Pedir y validar la cantidad | `leerEntero(...)` y `while (cantidad <= 0)` |
| Pedir y validar el descuento | `leerDecimal(...)` y el ciclo que comprueba el rango |
| Calcular el subtotal | `precio * cantidad` (actualmente no llama a `calcularSubtotal`) |
| Calcular el descuento | `subtotal * porcentajeDescuento / 100.0` |
| Calcular el IVA y el total | `subtotal * 16.0 / 100.0` y `subtotal + iva - montoDescuento` |
| Imprimir el ticket | `imprimirTicket(nombre, cantidad, precio, subtotal, montoDescuento, iva, total, porcentajeDescuento)` |

**¿Hubo algún paso de mi receta que me costó traducir a C++? ¿Cuál y por qué?**
Me costó colocar las llaves correctamente; si una función no se cierra donde corresponde, el compilador interpreta mal el alcance del código y aparecen varios errores.

**Formato del ticket: ¿qué ancho usé en `std::setw` y por qué? ¿Qué pasa si uso un número menor que el largo de la etiqueta más larga?**
No usé `std::setw`. Si el ancho fuera menor que la etiqueta más larga, esa etiqueta no cabría en el espacio reservado y la alineación de los valores podría no quedar como se espera.

**¿Convertí el ancho de las líneas del ticket (36) en una constante? ¿Cómo la llamé? Si no, ¿por qué?**
No lo convertí en una constante porque mi versión actual no dibuja líneas de 36 caracteres en el ticket.

## 11. Experimentos y depuración (Fase 3)

**Experimento A: depuración de `calcularDescuento`**

| Paso de depuración | Lo que hice o encontré |
|---|---|
| 1. Reproduce: ¿con qué datos falló? | No está documentado que se haya reproducido con una ejecución. |
| 2. Aísla: ¿qué valor intermedio estaba mal? (salidas `[DEBUG]`) | Pendiente de aislar con salidas `[DEBUG]`. |
| 3. Explica: ¿cuál era la causa? | La función inicial debía dividir el porcentaje entre 100; en la versión actual `calcularDescuento` sí incluye esa división, pero `main` calcula el descuento directamente y no llama a esa función. |
| 4. Corrige: ¿qué cambiaste? | La función del encabezado ahora calcula `subtotal * porcentaje / 100`; falta usarla desde `main` y documentar una prueba real. |
| 5. Limpia: ¿comentaste tus salidas `[DEBUG]`? | No se observan salidas `[DEBUG]` activas en el código actual. |

**La prueba con 0 % pasó aunque la función tenía un error. ¿Qué me enseña eso sobre elegir mis casos de prueba?**
Que hay que probar valores distintos de cero y casos límite: con 0 %, el resultado es cero aunque la fórmula esté mal.

**Experimento B: al cambiar el IVA a 8 %, ¿cuántas líneas tuve que cambiar? ¿Qué mejoraría?**
Pendiente de realizar. Para facilitar ese cambio, la tasa debería guardarse en una constante y usarse tanto en el cálculo como en la etiqueta del ticket.

**¿Mi ticket seguía diciendo `IVA (16%)`? ¿Qué hice al respecto?**
El ticket actual muestra `Iva` sin indicar la tasa; no realicé el experimento de cambiarla a 8 %.

**Experimento C (opcional): al cambiar el parámetro dentro de `calcularIVA`, ¿cambió la variable de `main()`? ¿Por qué?**
No aplica: no realicé el experimento opcional de paso por valor.

## 12. La constante "Le atendio" (Fase 3)

**¿Dónde definí la constante con mi nombre?** (marca una)
- [ ] Constante local dentro de `imprimirTicket`
- [ ] Constante a nivel de la librería, en `ticket.h`
- [ ] Función que siempre devuelve la misma cadena

**¿Por qué elegí esa opción?**
Todavía no definí la constante con el nombre de quien atiende. Una constante local dentro de `imprimirTicket` sería suficiente si solo se usa en el ticket; si se comparte con otras partes, convendría declararla en un lugar común.

**¿Qué otras partes del programa podrían necesitar el nombre de quien atiende? (un mensaje de bienvenida, un ticket de devolución...)**
Un mensaje de bienvenida, un ticket de devolución o un reporte de ventas.

**Si mañana atiende otra persona, ¿en cuántos lugares tengo que cambiar el nombre?**
Como la constante aún no está implementada, todavía no aplica. Si se agrega en un solo lugar y se reutiliza, bastaría con cambiarla allí.

**Si el nombre se leyera del teclado o de un archivo, ¿cuánto código tendría que cambiar con mi opción?**
Como todavía no elegí ni implementé la constante, queda pendiente. Si se centraliza la lectura en una función o variable, se cambiaría principalmente ese punto y se conservaría la impresión del ticket.

## 13. Tabla de pruebas (Fase 4)
<!-- Los datos de entrada de cada caso están en PRACTICA.md, Fase 4. -->

| # | Caso | Esperado (subtotal / descuento / IVA / total) | Obtenido | ¿Pasó? |
|---|---|---|---|---|
| 1 | Sin descuento | 100.00 / 0.00 / 16.00 / 116.00 | No ejecutado | Pendiente |
| 2 | Con descuento | 100.00 / 10.00 / 14.40 / 104.40 | No ejecutado; el código actual calcularía IVA de 16.00 y total de 106.00 | Pendiente; no coincide con lo esperado |
| 3 | Descuento de 15 % | 600.00 / 90.00 / 81.60 / 591.60 | No ejecutado; el código actual calcularía IVA de 96.00 y total de 606.00 | Pendiente; no coincide con lo esperado |
| 4 | Precio con centavos | 19.99 / 0.00 / 3.20 / 23.19 | No ejecutado | Pendiente |
| 5 | Descuento total | 90.00 / 90.00 / 0.00 / 0.00 | No ejecutado; el validador actual rechaza 100 % | Pendiente; ajustar validación |
| 6 | Precio inválido | vuelve a pedir el precio dos veces; 40.00 / 0.00 / 6.40 / 46.40 | No ejecutado | Pendiente |
| 7 | Cantidad inválida | vuelve a pedir la cantidad dos veces; 20.00 / 0.00 / 3.20 / 23.20 | No ejecutado | Pendiente |
| 8 | Descuento inválido | vuelve a pedir el descuento dos veces; 100.00 / 20.00 / 12.80 / 92.80 | No ejecutado; con el código actual el IVA sería 16.00 y el total 96.00 | Pendiente; no coincide con lo esperado |
| 9 | Texto en el precio | vuelve a pedir el precio una vez; 100.00 / 0.00 / 16.00 / 116.00 | No ejecutado | Pendiente |
| 10 | Nombre con espacios | muestra el nombre completo; 25.50 / 0.00 / 4.08 / 29.58 | No ejecutado | Pendiente |
| 11 | Nombre vacío | vuelve a pedir el nombre una vez; 12.00 / 0.00 / 1.92 / 13.92 | No ejecutado | Pendiente |
| 12 | Caso propio 1: descuento del 50 % | 60.00 / 30.00 / 4.80 / 34.80 | No ejecutado | Pendiente |
| 13 | Caso propio 2: compra sin descuento | 25.00 / 0.00 / 4.00 / 29.00 | No ejecutado | Pendiente |

**En el caso 4 el IVA real es 3.1984. ¿Por qué mi ticket muestra 3.20?**
Si se imprime con `std::fixed` y `std::setprecision(2)`, 3.1984 se redondea visualmente a 3.20; el valor guardado no cambia. El código actual no configura ese formato, así que todavía mostraría más decimales.

**En el caso 10, ¿el ticket siguió alineado? Si no, ¿qué corregí?**
No puedo confirmar el resultado sin ejecutar la prueba. El código actual no usa `std::setw`, así que no implementa todavía la alineación de columnas; habría que agregarla a `imprimirTicket`.

## 14. Generalización (Fase 4)

**¿Qué cálculo hacen `calcularDescuento` y `calcularIVA`? ¿Qué cambia entre una y otra?**
`calcularDescuento` obtiene una cantidad aplicando un porcentaje al subtotal. El IVA también es un porcentaje aplicado a una base, que debe ser el subtotal menos el descuento. En el código actual `calcularDescuento` divide entre 100, pero `calcularIVA` en `ticket.h` no calcula solamente el IVA y debe corregirse.

**Receta de `calcularPorcentaje`** (también va en `RECETA.md`):

```text
MODULO calcularPorcentaje(cantidadBase, porcentaje)
    DEVOLVER cantidadBase * porcentaje / 100
FIN MODULO
```

**¿Cómo quedaron el descuento y el IVA después del cambio?**
Pendiente: `calcularPorcentaje` todavía no está implementada ni se usa desde `main`. La fórmula debe aplicarse al subtotal para el descuento y al subtotal menos el descuento para el IVA.

**¿Volví a correr toda la tabla de pruebas después del cambio? ¿Todo siguió pasando?**
No. La tabla sigue pendiente de ejecución; además, los casos con descuento no coinciden con el cálculo actual del IVA.

**¿Agregué `calcularPorcentaje` a mi tabla de módulos (sección 7)?** Sí, como módulo propuesto; todavía está pendiente implementarlo.

**¿En qué otro programa podría reutilizar `calcularPorcentaje`?**
Para calcular una propina, una comisión o el porcentaje de batería de un dispositivo.

## 15. Revisión de calidad (Fase 4)

| Principio | Pregunta | ¿Lo cumple? | Evidencia |
|---|---|---|---|
| Correcto | ¿Pasa todas las pruebas de la tabla? | Pendiente | No se han ejecutado; el IVA y la validación del 100 % requieren corrección. |
| Robusto | ¿Resiste datos inválidos sin fallar ni terminar? | Parcialmente | Los lectores repiten entradas de formato incorrecto y `main` repite precio, cantidad y descuento fuera de rango. |
| Legible | ¿Otra persona entiende tu código sin que se lo expliques? | Parcialmente | Los nombres son descriptivos, pero hay comentarios TODO y falta hacer coincidir receta, módulos y código. |
| Modular | ¿Cada función hace una sola cosa? | Parcialmente | `imprimirTicket` solo imprime; `main` hace los cálculos directamente y no usa los módulos disponibles. |
| Sin números mágicos | ¿Los valores fijos tienen nombre? | No | El 16 % del IVA está escrito directamente en la operación de `main`. |
| Fácil de mantener | Si cambia el IVA o quien atiende, ¿cuántas líneas cambias? | No | La tasa y el nombre de quien atiende no están centralizados en constantes. |
| Reutilizable | ¿Alguna de tus funciones serviría en otro programa? | Sí | `calcularSubtotal` y `calcularDescuento` son cálculos generales, aunque `main` aún no los llama. |

## 16. Reto obligatorio (Fase 4)

**¿Qué reto elegí?** (número y nombre; el 4 no cuenta como obligatorio) Pendiente: todavía no está documentado ni implementado un reto.

**¿Por qué lo elegí?**
Pendiente de elegir el reto obligatorio.

**¿Cómo lo resolví? ¿Qué módulos agregué o cambié?**
Pendiente: primero debo elegir e implementar un reto y luego describir aquí los cambios realizados.

**¿Hice algún otro reto opcional? ¿Cuál?**
No está documentado que haya realizado otro reto.

## 17. Bitácora de mejoras (Fase 4)

| # | ¿Qué falló o qué quise mejorar? | ¿Qué cambié? | ¿Funcionó? |
|---|---|---|---|
| 1 | El IVA del código no se calcula después del descuento. | Pendiente: ajustar la base del IVA y usar una función de cálculo. | Pendiente de probar. |
| 2 | El descuento de 100 % se rechaza y el ticket no muestra dos decimales alineados. | Pendiente: aceptar 100 % y agregar formato monetario al ticket. | Pendiente de probar. |

## 18. Dudas para el profesor (Fase 3)

| Duda | Lo que ya intenté |
|---|---|
| ¿Cómo debo ajustar `calcularIVA` para recibir el subtotal después del descuento y devolver solo el monto del IVA? | Revisé `ticket.h`: actualmente recibe tres parámetros y devuelve subtotal menos descuento más IVA, que corresponde al total y no al IVA. |
| ¿Cómo debo probar y documentar el ticket después de corregir las fórmulas? | Preparé una tabla con casos esperados; falta ejecutar el programa y anotar los resultados observados. |

## 19. Reflexión final

**¿Qué aprendí con esta práctica?**
Aprendí a separar el programa en funciones, validar entradas con ciclos y distinguir entre una función que devuelve un resultado y un procedimiento que realiza una acción como imprimir.

**Ahora que terminé, ¿qué cambiaría de mi proceso?**
Organizaría primero la receta y las funciones, y después probaría cada cambio con casos sin descuento, con descuento y con valores límite.

**¿Qué fue lo más difícil y cómo lo resolví?**
Lo más difícil fue acomodar las llaves y separar la definición de `imprimirTicket` de `main`. Lo resolví revisando el alcance de cada función y ordenando sus llaves.

**¿Qué pregunta me quedó sin responder?**
¿Cómo puedo organizar las funciones para que `main` solo coordine la lectura, los cálculos y la impresión del ticket?

**Comparado con las prácticas anteriores, donde todo estaba en `main()`, ¿dividir el programa en módulos me facilitó o me complicó el trabajo? ¿Por qué?**
Al principio me complicó porque tuve que definir qué recibe y qué devuelve cada módulo, pero separar los cálculos de la impresión hace más claro dónde corregirlos.

**¿Cómo encontré el error de `calcularDescuento`? ¿Lo habría encontrado si solo hubiera probado sin descuento?**
La documentación disponible no confirma que lo haya encontrado ejecutando el experimento. Probar solo con 0 % no habría revelado el error, porque el resultado del descuento sería cero incluso con una fórmula incorrecta; también hay que probar porcentajes distintos de cero.

## 20. Commits (Fase 5)

**¿Cuántos commits hice durante la práctica?** Al menos 5 commits aparecen en el historial consultado.

**Si hice menos de 3, ¿por qué?**
No aplica: el historial consultado muestra al menos 5 commits.

## 21. Lista de verificación antes de entregar (Fase 5)

- [ ] Llené las secciones 1 a 20 (no quedan `_____`; escribí `No aplica` donde corresponde)
- [ ] Completé el árbol de análisis descendente y la tabla de módulos
- [ ] Escribí en `RECETA.md` la receta de `main` y la de cada módulo, antes de programar
- [ ] Cada bloque de `main.cpp` tiene su comentario `// Paso N`, de acuerdo con mi receta
- [ ] Corregí el error de `calcularDescuento` y documenté cómo lo encontré
- [ ] Hice los Experimentos A y B y dejé el código correcto al terminar
- [ ] Mi ticket se ve alineado y termina con la línea "Le atendio:", leída de una constante
- [ ] Justifiqué dónde definí la constante con mi nombre
- [ ] Escribí `calcularPorcentaje` y volví a correr todas las pruebas
- [ ] Hice al menos uno de los retos y lo documenté
- [ ] No queda ninguna salida `[DEBUG]` activa
- [ ] Mi programa compila sin advertencias
- [ ] Probé todos los casos de la tabla
- [ ] Revisé los principios de calidad de mi programa
- [ ] No modifiqué `utilerias.h`
- [ ] Tengo al menos 3 commits con mensajes claros (o justifiqué por qué no)
- [ ] Hice `git push` y verifiqué mi fork en GitHub
- [ ] Mi fork se llama `ulsa_ime_1_dp_ticket_compra`, mis módulos están en `include/ticket.h` y mi programa principal en `src/main.cpp`
- [ ] Entregué el enlace de mi fork en Classroom
