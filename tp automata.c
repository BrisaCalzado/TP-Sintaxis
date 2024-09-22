#include <stdio.h>
#include <ctype.h>

//--------------------PROTOTIPOS DEL PUNTO 1-----------------------
int caracteresPertenecenAlAlfabeto (char*cadena); 
int esPalabra(char*, int*); 
int columna(int);
//--------------------PROTOTIPOS DEL PUNTO 2-----------------------
int convertirCadenaAEntero(char cadena[]);

int main()
{
	//--------------------PUNTO 1-----------------------
	char cadena[100];
	
	printf("Ingrese la cadena de numeros separados por '#': ");
	scanf("%s", cadena);
	
	if(!caracteresPertenecenAlAlfabeto(cadena)) // si NO verifica la cadena
	{
		printf("Hay caracteres que no pertenecen al alfabeto.");
		return 0; 
	}

	int i=0, j=0, inicio=0;
	int contadorDecimales=0, contadorOctales=0, contadorHexadecimales=0;
	char subcadena[100];
	
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




