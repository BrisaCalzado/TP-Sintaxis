#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

//--------------------PROTOTIPOS DEL PUNTO 1-----------------------
int caracteresPertenecenAlAlfabeto (char*cadena); 
int esPalabra(char*, int*); 
int columna(int);
//--------------------PROTOTIPOS DEL PUNTO 2-----------------------
int convertirCadenaAEntero(char cadena[]);
//--------------------PROTOTIPOS DEL PUNTO 3-----------------------
int esOperador(char c);
int precedencia(char op);
int hacerOperacion(int a, int b, char op);
int evaluarCadenaPosfija(char* tokens);
void infijaAPosfija(char* expresion, char* cadenaDeSalida);
int caracteresPertenecenAlAlfabetoP3 (char*cadena);
int esPalabraP3(char*); 
int columnaP3(int);

int main()
{
	//--------------------PUNTO 1-----------------------
	char cadena[MAX];
	
	printf("Ingrese la cadena de numeros separados por '#': ");
	scanf("%s", cadena);
	
	if(!caracteresPertenecenAlAlfabeto(cadena)) // si NO verifica la cadena
	{
		printf("Hay caracteres que no pertenecen al alfabeto.");
		return 0; 
	}

	int i=0, j=0, inicio=0;
	int contadorDecimales=0, contadorOctales=0, contadorHexadecimales=0;
	char subcadena[MAX];
	
	while(cadena[i] != '\0')
	{
		if(cadena[i] == '#')
		{
			int largo = i - inicio;
			for(j=0; j<largo; j++)
			{
				subcadena[j] = cadena[inicio + j];
			}
			subcadena[largo] = '\0'; //"cierro" la subcadena
			
			//meter subcadena en el automata, fijarme que tipo de numero es, y sumar
			int tipoNumero = 0;
			esPalabra(subcadena, &tipoNumero);
			
			if(tipoNumero == 1)
			{
				contadorDecimales++;
			} else if(tipoNumero == 2)
			{
				contadorOctales++;
			} else if(tipoNumero == 3)
			{
				contadorHexadecimales++;
			} else if(tipoNumero == 4)
			{
				printf("Hay error lexico en: %s\n", subcadena); //ej079--> los octales no pueden tener 9
				return 0;
			}
			
			inicio = i + 1; // proximo caracter + 1
		}
		i++;
	}
	//para procesar el ultimo token (que no termina con #)
	int largo = i - inicio;
	for(j=0; j<largo; j++)
	{
		subcadena[j] = cadena[inicio + j];
	}
	subcadena[largo] = '\0'; //"cierro" la subcadena
	
	//meter subcadena en el automata, fijarme que tipo de numero es, y sumar
	int tipoNumero = 0;
	esPalabra(subcadena, &tipoNumero);
		
	if(tipoNumero == 1)
	{
		contadorDecimales++;
	} else if(tipoNumero == 2)
	{
		contadorOctales++;
	} else if(tipoNumero == 3)
	{
		contadorHexadecimales++;
	} else if(tipoNumero == 4)
	{
		printf("Hay error lexico en: %s\n", subcadena); //ej079--> los octales no pueden tener 9
		return 0;
	}

	printf("Cantidad de decimales: %d\n", contadorDecimales);
	printf("Cantidad de octales: %d\n", contadorOctales);
	printf("Cantidad de hexadecimales: %d\n", contadorHexadecimales);

	//--------------------PUNTO 2-----------------------
	char cadena2[11] ; //por la longitud del int que es 10 + 1 digito
    	printf("Ingrese una cadena: ");
    	scanf("%s", cadena2);
    	int numero = convertirCadenaAEntero(cadena2);
    	printf("El numero convertido es: %d\n", numero);  // Salida: -1234
	//--------------------PUNTO 3-----------------------
	char expresion[MAX];
    printf("Ingrese un calculo sencillo:  (sin espacios y pudiendo utilizar los operadores + - / *)\n");
    scanf("%s", expresion);    

if(!caracteresPertenecenAlAlfabetoP3(expresion)) // si NO verifica algun caracter
	{
		printf("La expresión contiene caracteres que no pertenecen al alfabeto.\n");
		return 0;
	}

	if (!esPalabraP3(expresion)) // si NO verifica expresion
	{
		printf("La expresión contiene un error sintáctico\n");
		return 0;
	}


	if(!caracteresPertenecenAlAlfabetoP3(expresion)) // si NO verifica algun caracter
	{
		printf("La expresión contiene caracteres que no pertenecen al alfabeto.\n");
		return 0;
	}

	if (!esPalabraP3(expresion)) // si NO verifica expresion
	{
		printf("La expresión contiene un error sintáctico\n");
		return 0;
	}

    char expresionPosfija[MAX];
    infijaAPosfija(expresion, expresionPosfija);
    printf("Resultado: %d\n", evaluarCadenaPosfija(expresionPosfija));

	return 0;
}

//--------------------FUNCIONES DEL PUNTO 1-----------------------
int caracteresPertenecenAlAlfabeto(char* cadena)
{
	int i = 0;
	int j = 0;
	char caracteresValidos[27] = "ABCDEFXabcdefx0123456789-+#";
	
	for (i = 0; cadena[i]; i++)
    {
        int esValido = 0; 
        
        for (j = 0; caracteresValidos[j]; j++) 
        {
            if (cadena[i] == caracteresValidos[j])
            {
                esValido = 1; 
            }
        }
        
        /*bucle en el que se compara un caracter de la cadena con todos los de 
		la lista de caracteres validos,*/
        
        if (!esValido)
        {
            return 0; 
        }
    }
    
    return 1; // Todos los caracteres son válidos
}

int esPalabra(char* cadena, int* tipoNumero)
{
	//1ero hay que hacer la matriz (TT)--> el la que me da la logica para saber si una cadena llega o no a un estado de aceptacion
	static int tt[8][7]={
							{1,1,3,7,2,2,7},
							{7,7,2,7,2,2,7},
							{7,7,2,7,2,2,7},
							{7,7,4,5,4,7,7},
							{7,7,4,7,4,7,7},
							{7,7,6,7,6,6,6},
							{7,7,6,7,6,6,6},
							{7,7,7,7,7,7,7}
						};
	
	int estado = 0; // ese es mi estado inicial
	int i=0;
	
	int c=cadena[0]; 
	
	while(c != '\0')
	{
		estado=tt[estado][columna(c)]; 
		c=cadena[++i]; 
	}
	//cuando sale del while sale en un estado, a mi me interesan los estados de ACEPTACION
	if(estado==2)
	{
		*tipoNumero = 1; // Decimal
		return 1; 
	}
	if (estado == 3) //para considerar el cero a secas como decimal ej: 123#0#123
	{
		*tipoNumero = 1; // Decimal
		return 1; 
	}
	if(estado==4)
	{
		*tipoNumero = 2; // Octal
		return 1; 
	}
	if(estado==6)
	{
		*tipoNumero = 3; // Hexadecimal
		return 1; //hexadecimal
	}
	
	*tipoNumero = 4; //Error léxico
	return 0; //no es una palabra valida
}

int columna (int c)
{
	if(c == '+')
	{
		return 0;//numero de columna que devuelve 
	}
	if(c == '-')
	{
		return 1;
	}
	if(c == '0')
	{
		return 2;
	}
	if(c == 'x' || c == 'X')
	{
		return 3;
	}
	if(c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7')
	{
		return 4;
	}
	if(c == '8' || c == '9')
	{
		return 5;
	}
	if(c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f' || c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == 'E' || c == 'F')
	{
		return 6;
	}
	else
	{
		return -1;
	}
}

//--------------------FUNCIONES DEL PUNTO 2-----------------------
int convertirCadenaAEntero(char cadena[]) {
    int i = 0, num = 0, signo = 1;

    // Ignorar espacios en blanco iniciales
    for (i = 0; isspace(cadena[i]); i++);

    // Determinar si hay un signo negativo o positivo
    if (cadena[i] == '-') {
        signo = -1;
        i++;
    } else if (cadena[i] == '+') {
        i++;
    }

    // Convertir los caracteres numéricos en el número entero
      
     for (num = 0; isdigit(cadena[i]); i++){
     	num = 10 * num + (cadena[i] - '0');
	 }
    
    /*El num en 10*num aumenta según el primer numero de la lista
	Ej en el numero 567, num = 5, dsp en la siguiente iteración va a ser 10*5 + 6, y dsp 10*56 + 7 
    En (cadena[i] - '0') lo que hace es restar el valor ascii del indice de la cadena y del 0
	Por ejemplo 0 = 48 ascii, si el numero que quiero es 1 = 49 ascii, 
 	hago 49 - 48 y ahí me da el 1 del que en verdad quiero*/

    // Devolver el número convertido, aplicando el signo
    return signo * num;
}

//--------------------FUNCIONES DEL PUNTO 3-----------------------
int esOperador(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int precedencia(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

int hacerOperacion(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

int evaluarCadenaPosfija(char* tokens) { //le pasamos la cadena YA en posfija
    int stack[MAX], top = -1; //array como pila y su indice (-1: para indicar que esta vacia)
    char numStr[MAX]; //arreglo temporal para construir numeros de muchos digitos
    int numStrIndex = 0; //indice para construir los numeros
    int len = strlen(tokens);
    int i = 0;

    for (i = 0; i<len; i++) {
        if (isdigit(tokens[i]) || (tokens[i] == '-' && isdigit(tokens[i+1]))) { //la 2da permite reconocer negativos
            numStr[numStrIndex++] = tokens[i];
            if (!isdigit(tokens[i+1])) {
                numStr[numStrIndex] = '\0';
                stack[++top] = convertirCadenaAEntero(numStr); //guarda en la pila el nro convertido
                numStrIndex = 0; //para construir el siguiente nro
            }
        } else if (esOperador(tokens[i])) { //si es operador
            int val2 = stack[top--]; //saca 2 nros de la pila
            int val1 = stack[top--];
            stack[++top] = hacerOperacion(val1, val2, tokens[i]); //realiza la operacion y lo pone en la pila
        }
    }
    return stack[top]; //cuando se proceso todo, el resultdo de la exp queda en la cima de la pila
}

void infijaAPosfija(char* expresion, char* cadenaDeSalida) {
    char stack[MAX]; //pila
    int top = -1, k = 0; //top es pos de la pila y k de la cadena de salida
    int len = strlen(expresion);
    int i = 0;
    
    for (i = 0; i<len; i++) {
        if (isdigit(expresion[i])) { //si es un digito
            while (isdigit(expresion[i])) {
                cadenaDeSalida[k++] = expresion[i++]; //copia el numero o los numeros en la cadena de salida
            }
            cadenaDeSalida[k++] = ' ';
            i--; //retrocede el índice i-- para no saltarse el siguiente carácter después del número.
        } else if (esOperador(expresion[i])) { //si es un operador
            while (top != -1 && precedencia(stack[top]) >= precedencia(expresion[i])) { //mientras: la pila no este vacia Y haya operadores en la pila con mayor
                cadenaDeSalida[k++] = stack[top--];					// o igual precedencia que el operador actual, se sacan de la pila y se ponen en la salida output
                cadenaDeSalida[k++] = ' ';
            }
            stack[++top] = expresion[i]; //coloca el operador actual a la pila
        }
    }
    while (top != -1) { //para verificar q no queden operadores en la pila, los saca y pone el la cadena de salida
        cadenaDeSalida[k++] = stack[top--];
        cadenaDeSalida[k++] = ' ';
    }
    cadenaDeSalida[k] = '\0'; //para terminar la cadena
}


int caracteresPertenecenAlAlfabetoP3(char* cadena)
{
	int i = 0;
	int j = 0;
	static char alfabetoP3[15] = "0123456789-+*/";
	
	for (i = 0; cadena[i]; i++)
    {
        int esValido = 0;
		
        for (j = 0; alfabetoP3[j]; j++) 
        {
            
			if (cadena[i] == alfabetoP3[j])
            {
                esValido = 1; 
            }
        }
        /*bucle en el que se compara un caracter de la cadena con todos los de 
		la lista de caracteres validos,*/
        
        if (!esValido)
        {
            return 0; 
        }
    }
    
    return 1; // Todos los caracteres son válidos
}


int esPalabraP3(char* cadena)
{
	//1ero hay que hacer la matriz (TT)--> el la que me da la logica para saber si una cadena llega o no a un estado de aceptacion
	static int ttP3[6][3]={
							{2,1,5},
							{2,5,5},
							{2,3,3},
							{4,5,5},
							{4,3,3},
							{5,5,5}
						};
	
	int estado = 0; // ese es mi estado inicial
	int i=0;
	
	int c=cadena[0]; 
	
	while(c != '\0')
	{
		estado=ttP3[estado][columnaP3(c)]; 
		c=cadena[++i]; 
	}
	//cuando sale del while sale en un estado, a mi me interesan los estados de ACEPTACION
	if(estado == 2 || estado == 4)
	{
		return 1; 
	} 
	else
	return 0; //no es una palabra valida
}


int columnaP3 (int c)
{
	if(isdigit(c))
	{
		return 0;//numero de columna que devuelve 
	}
	if(c == '+' || c == '-') //diferenciar +,- de *,/ permite empezar la expresion con + o -
	{
		return 1;
	}
	if(c == '*' || c == '/')
	{
		return 2;
	}
	else
	{
		return -1;
	}
}
