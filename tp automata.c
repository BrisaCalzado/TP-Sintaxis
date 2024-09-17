/*1)Dada una cadena que contenga varios números que pueden ser decimales, octales o
hexadecimales, con o sin signo para el caso de los decimales, separados por el carácter
‘#’ , reconocer los tres grupos de constantes enteras, indicando si hubo un error léxico ,
en caso de ser correcto contar la cantidad de cada grupo.
Debe diagramar y entregar el o los autómatas utilizados y las matrices de transición.
La cadena debe ingresar por línea de comando o por archivo.
*/

/*Entrada y Separación por Caracter ‘#’:

Se debe leer la cadena completa y dividirla en partes usando el separador #.
Cada parte debe ser analizada por separado para determinar si es un número decimal, octal o hexadecimal.*/

#include <stdio.h>
#include <ctype.h>

int caracteresPertenecenAlAlfabeto (char*s); 


int main()
{
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
			subcadena[length] = '\0'; //"cierro" la subcadena
			
			//fijarme que tipo de numero es, y sumar
			if(esDecimal(subcadena))
			{
				contadorDecimales++;
			}
			else if(esOctal(subcadena))
			{
				contadorOctales++;
			}
			else if(esHexadecimal(subcadena))
			{
				contadorHexadecimales++;
			}
			else 
			{
				printf("Hay error lexico en: %s", subcadena); //ej079--> los octales no pueden tener 9
				return 0; //se termino
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
	subcadena[length] = '\0'; //"cierro" la subcadena
			
	//fijarme que tipo de numero es, y sumar
	if(esDecimal(subcadena))
	{
		contadorDecimales++;
	}
	else if(esOctal(subcadena))
	{
		contadorOctales++;
	}
	else if(esHexadecimal(subcadena))
	{
		contadorHexadecimales++;
	}
	else 
	{
		printf("Hay error lexico en: %s", subcadena); //ej079--> los octales no pueden tener 9
		return 0; 
	}

	printf("Cantidad de decimales: %d\n", contadorDecimales);
	printf("Cantidad de octales: %d\n", contadorOctales);
	printf("Cantidad de hexadecimales: %d\n", contadorHexadecimales);

	return 0;
}
//HICE ALGO MAL. UNA VEZ QUE TENGO LA SUBCADENA, METERLA AL AUTOMATA Y AHI VERIFICO ESTO: printf("Hay error lexico en: %s", subcadena)
//SI LLEGA A ESTAR TODO BIEN, AHI LO METO EN LAS FUNCIONES DE DECIMAL, OCTAL, ETC

int caracteresPertenecenAlAlfabeto(char* cadena)
{
	int i = 0;
	int j = 0;
	char caracteresValidos [27] = "ABCDEFXabcdefx0123456789-+#";
	
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

/*-------------------------------------INTENTO DE PROGRAMAR EL AUTOMATA--------------------------------------------*/
int esPalabra(char* cadena)
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
	int i=0; //lo que voy a usar para ir avanzando en la cadeena
	
	//ALTERNATIVA 1: avanzo hasta el final de la cadena sin importar los estados intermedios. solo importa el estado final
	int c=cadena[0]; //los char son un subconjunto de los enteros
	
	while(c != '\0')//itero mientras que no sea fin de cadena
	{
		estado=tt[estado][columna(c)]; //el nuevo estado
		
		c=cadena[++i]; //++i: primero suma y despues asigno
	}
	//cuando sale del while sale en un estado, a mi me interesan los estados de ACEPTACION
	if(estado==2)
	{
		return 1;//devulvo verdadero porque 2 es un estado de aceptaion
	}
	if(estado==4)
	{
		return 1;
	}
	if(estado==6)
	{
		return 1;
	}
	//HAY QUE VER LA FORMA DE QUE SI ESTADO==2 => DECIMAL, ==4 => OCTAL, ==6 => HEXADECIMAL
	//SI PUEDO HACER ESO=> NO IRIA LAS FUNCIONES ESDECIMAL, ETC
	
	return 0;
}


int columna (int c)
{
	if(c == '+')
	{
		return 1;//numero de columna que devuelve 
	}
	if(c == '-')
	{
		return 2;
	}
	if(c == '0')
	{
		return 3;
	}
	if(c == 'x' || c == 'X')
	{
		return 4;
	}
	if(c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7')
	{
		return 5;
	}
	if(c == '8' || c == '9')
	{
		return 6;
	}
	if(c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f' || c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == 'E' || c == 'F')
	{
		return 7;
	}
	else
	{
		return 0;
	}
}
