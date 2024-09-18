1)
#include <stdio.h>
#include <ctype.h>

int caracteresPertenecenAlAlfabeto (char*s); 
int esPalabra(char*, int*); 
int columna(int);

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

	return 0;
}

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

/*-------------------------------------INTENTO DE PROGRAMAR EL AUTOMATA--------------------------------------------*/
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
