# Consignas

Se deben incluir impresiones de las pantallas mostrando el funcionamiento del mismo.
La entrega debe contener los archivos fuente y un pdf con las pantallas, instructivo y especificaciones acerca de las decisiones tomadas para la resolución del mismo.

1) Dada una cadena que contenga varios números que pueden ser decimales, octales o hexadecimales, con o sin signo para el caso de los decimales, separados por el carácter ‘#’ , reconocer los tres grupos de constantes enteras, indicando si hubo un error léxico, en caso de ser correcto contar la cantidad de cada grupo.
Debe diagramar y entregar el o los autómatas utilizados y las matrices de transición.
La cadena debe ingresar por línea de comando o por archivo.

2) Debe realizar una función que reciba un carácter numérico y retorne un número entero.
   
3) Ingresar una cadena que represente una operación simple con enteros decimales y obtener su resultado, se debe operar con +,_ ,/ y *. Ejemplo = 3+4*7+3-8/4 = 32. Debe poder operar con cualquier número de operandos y operadores respetando la precedencia de los operadores aritméticos.
La cadena ingresada debe ser validada previamente preferentemente reutilizando las
funciones del ejercicio 1.
Para poder realizar la operación los caracteres deben convertirse a números utilizando la
función 2.
La cadena debe ingresar por línea de comando o por archivo

# COMENTARIOS DE LA PROFE SOBRE EL TP:
//HACER VALIDACION PREVIA PARA VER SI LA VIA ES DECIMAL, OCTA, Y HACER 1 MAT PAR CADA UNA
//MEJOR OPCION: 
//HACER UNA MATRIZ PARA LOS 3 (primero hay que armar el automata obviamente) 

//2da parte tp
//yo recibo una cadena. ej la cadena +23 se debe convertir en el numero 23
//PARA HACER ESTO LEER PG 68 DE CARNIGAN Y RICHI--> mecanismo donde resivo caracteres y convierto la cadena +23 en el num 23
//convierto la cadena numero a un numero, y ese numero puede ser uno neg

//3RA PARTE
//eso lo necesito para el pto que le sigue 
//expresion aritmetica simple: + - * /
//ej: 3+4*6-12 --> esa cadena debe devolverme le nro del rdo. la cadena 3 debe convertirse en el num 3 y asi con todas (para esto necesito la funcion anterior)
//avanzo hasta encontrar el signo y lo convierto en numero
//calculadoras antiguas usaban un metordo para hacer estos calculos, algo que tal vez vimos en discreta
//debo encontrar de la forma de haver esas operaciones matematicas
//arboles tal vez
//debe funcionar bien sin parentesis (lo de los signos)

