#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

//Prototipo de la funcion para contar el numero de cadenas
void contarCadena(const char *entrada,const char *cadena,const char *salida);

//Prototipo de la funcion para contar el numero de vecs que se repite una subcadena prefijo
void contarSubcPre(const char *entrada, const char *cadena, const char *salida);

//Prototipo de la funcion para contar el numero de veces que se repite una subcadena sufijo
void contarSubcSuf(const char *entrada, const char *cadena, const char *salida);

//Prototipo de la funcion para contar el numero de caracteres
int contarCaracteres(const char *entrada);

//Prototipo de la funcion para contar el numero de lineas que existen
int contarLineas(const char *entrada);

//Prototipo de la funcion para contar el numero de palabras-cadenas
int contarCadenas(const char *entrada);

//Prototipo de la funcion para contar el numero de enteros que existen
int contarEnteros(const char* entrada);

//Prototipo de la funcion para contar el numero de flotantes que existen
int contarFlotantes(const char* entrada);

//Prototipo de la funcion que imprime el numero de linea con su respectiva
void imprimirLinea(const char *entrada,const char *salida);

//Prototipo de la funcion que lee e imprime solo las lineas seleccionadas
void imprimir_lineas_seleccionadas(const char *entrada, bool tablaDeRenglones[], const char *salida);

//Prototipo de la funcion que lee e imprime solo las columnas seleccionadas
void imprimir_columnas_seleccionadas(const char *entrada, bool tablaDeRenglones[], const char *salida);

//Prototipo de la funcion que lee e imprime el texto con saltos de linea indicados
void insertar_saltos(const char *entrada, bool tablaDeRenglones[], const char *salida);

//Prototipo de la funcion que lee e imprime el texto con tabuladores indicados
void insertar_tabuladores(const char *entrada, bool tablaDeRenglones[], const char *salida);

//Funcion Booleana que nos permite saber si es numero entero de acuerdo bajo ciertas condiciones
bool es_entero(const char *cadena);

//Funcion Booleana que nos permite saber si es numero flotante de acuerdo bajo ciertas condiciones
bool es_flotante(const char *cadena);

//Funcion main donde recibira argumentos por medio de consola cmd, de acuerdo a ellos, evaluara una condicion y realizara una accion 
int main(int argc,char *argv[]) {
	
	const char *archivoEnt = argv[1];
	const char *archivoSal = argv[argc - 1];
	char argumento[256];
	char comando[256];
    strcpy(argumento, argv[2]);
	
	if(strcmp(argumento,"CC")==0) {
		contarCadena(argv[1],argv[3],argv[4]);
		printf("Usted ingreso la opcion 5");
	}
	
	else if(strcmp(argumento,"CP")==0){
		contarSubcPre(argv[1],argv[3],argv[4]);
		printf("Usted ingreso la opcion 6");
	}
	
	else if(strcmp(argumento,"CS")==0){
		contarSubcSuf(argv[1],argv[3],argv[4]);
		printf("Usted ingreso la opcion 7");
	}
	else if(strcmp(argumento,"WC")==0){
		FILE *archivoSalida=fopen(archivoSal,"w");
		printf("El numero de caracteres encontrados es: %d\n",contarCaracteres(archivoEnt));
		printf("El numero de lineas encontradas es: %d\n",contarLineas(archivoEnt));
		printf("El numero de cadenas encontradas es: %d\n",contarCadenas(archivoEnt));
		//Aqui mandamos a imprimir en el archivo de salida la informacion
		fprintf(archivoSalida,"El numero de caracteres encontrados es: %d\n",contarCaracteres(archivoEnt));
		fprintf(archivoSalida,"El numero de lineas encontradas es: %d\n",contarLineas(archivoEnt));
		fprintf(archivoSalida,"El numero de cadenas encontradas es: %d\n",contarCadenas(archivoEnt));
		printf("Usted ingreso la opcion 8\n");
		fclose(archivoSalida);           
	}
	
	else if(strcmp(argumento,"WNUM")==0){
		FILE *archivoSalida=fopen(archivoSal,"w");
		printf("El numero de enteros que existen es: %d\n",contarEnteros(archivoEnt));
		printf("El numero de flotantes que existen es: %d\n",contarFlotantes(archivoEnt));
		printf("Usted ingreso la opcion 9");
		//Aqui mandamos a imprimir en el archivo de salida la informacion
		fprintf(archivoSalida,"El numero de enteros que existen es: %d\n",contarEnteros(archivoEnt));
		fprintf(archivoSalida,"El numero de flotantes que existen es: %d\n",contarFlotantes(archivoEnt));
		fclose(archivoSalida);  
	}
	
	else if(strcmp(argumento,"INC")==0){
		imprimirLinea(argv[1],argv[3]);
		printf("Usted ingreso la opcion 10");
	}

	else {
		// Obtenemos el comando y los valores dados puesto que se trata de un atributo tipo comando_valor1_valor2......
		sscanf(argumento, "%[^_]_%s", comando, argumento); // obtenemos comando y argumento se queda con el resto
		bool tablaDeValores[1000] = {false}; 
		int valor;
        char caracter;
        int k=0;
		do{
            valor = 0;
            while (('0' <= argumento[k]) && (argumento[k] <= '9')){ // Ciclamos la cadena 'argumento' mientras sea numero
                if (valor==0) // numero nuevo: lo copiamos
                    valor= argumento[k]-'0';
                else // subscecuente digito: recorremos un lugar decimal el que llevabamos y lo metemos
                    valor=valor*10+(argumento[k - 1]-'0');
                k++;
            } // encuentra algo distinto y termina el ciclo
            tablaDeValores[valor - 1] = true; // asignamos TRUE a la tabla de valores justo donde nos indico el usuario en sus argumentos
        }while (argumento[k++] == '_'); // mientras aun haya valores por leer del usuario

		if (strcmp(comando, "L") == 0) {
			imprimir_lineas_seleccionadas(archivoEnt, tablaDeValores, archivoSal);
		}
        else if (strcmp(comando, "C") == 0) {
			imprimir_columnas_seleccionadas(archivoEnt, tablaDeValores, archivoSal);
		}
        else if (strcmp(comando, "ILV") == 0) {
			insertar_saltos(archivoEnt, tablaDeValores, archivoSal);
		}
        else if (strcmp(comando, "IC") == 0) {
			insertar_tabuladores(archivoEnt, tablaDeValores, archivoSal);
		}
    }
	return 0;
}

void contarCadena(const char *entrada, const char *cadena, const char *salida){
	int contPalabIguales=0;
	char cadenaTemporal[256];
	FILE* archivoEntrada=fopen(entrada,"r");

	while(!feof(archivoEntrada)){
		fscanf(archivoEntrada,"%s",cadenaTemporal);
		
		if(strcmp(cadenaTemporal,cadena)==0){
			contPalabIguales=contPalabIguales+1;
		}
		
	}
	fclose(archivoEntrada);
	FILE* archivoSalida=fopen(salida,"w"); 
	fprintf(archivoSalida,"El numero de ocurrencias de la cadena [%s] es de %d:\n",cadena,contPalabIguales);
	printf("El numero de ocurrencias de la cadena [%s] es de: %d \n",cadena,contPalabIguales);
	fclose(archivoSalida);
}

void contarSubcPre(const char *entrada, const char *cadena, const char *salida){
	
	int contarSubc=0;
	char cadenaTemporal[256];
	FILE* archivoEntrada=fopen(entrada,"r");
	
	while(!feof(archivoEntrada)){
		fscanf(archivoEntrada,"%s",cadenaTemporal);
		
		if(strstr(cadenaTemporal,cadena)==cadenaTemporal && strcmp(cadenaTemporal,cadena)!=0){
			contarSubc=contarSubc+1;
		}
	}
	
	fclose(archivoEntrada);
	FILE* archivoSalida=fopen(salida,"w");
	printf("El numero de ocurrencias de la cadena [%s] es de: %d \n",cadena,contarSubc);
	fprintf(archivoSalida,"El numero de ocurrencias de la cadena [%s] es de: %d \n",cadena,contarSubc);
	fclose(archivoSalida);
}

void contarSubcSuf(const char *entrada, const char *cadena, const char *salida){
	int contarSubc=0;
	char cadenaTemporal[256];
	FILE* archivoEntrada=fopen(entrada,"r");

	
	while(!feof(archivoEntrada)){
		fscanf(archivoEntrada,"%s",cadenaTemporal);
		
		if(strstr(cadenaTemporal,cadena)!=&cadenaTemporal[0] && strstr(cadenaTemporal,cadena)){
			contarSubc=contarSubc+1;
		}
	}
	fclose(archivoEntrada);	
	FILE* archivoSalida=fopen(salida,"w");
	printf("El numero de ocurrencias de la cadena [%s] es de: %d \n",cadena,contarSubc);
	fprintf(archivoSalida,"El numero de ocurrencias de la cadena [%s] es de: %d \n",cadena,contarSubc);
	fclose(archivoSalida);
}

int contarLineas(const char *entrada){
	int numeroLineas=0;
	int cLineas=0;
	char cadenaTemporal[256];
	FILE* archivoEntrada=fopen(entrada,"r");
	
		while(!feof(archivoEntrada)){
			fgets(cadenaTemporal,256,archivoEntrada);
				numeroLineas=numeroLineas+1;
		}
		
	fclose(archivoEntrada);
	return numeroLineas;
}

int contarCaracteres(const char *entrada){
	int numeroCaracteres=0;
	int cCaracteres=0;
	FILE* archivoEntrada=fopen(entrada,"r");
	
		while((cCaracteres=fgetc(archivoEntrada))!=EOF){
			if(cCaracteres!=' ' && cCaracteres!='\n' && cCaracteres!='\t' )
				numeroCaracteres=numeroCaracteres+1;
		}
		
	fclose(archivoEntrada);
	return numeroCaracteres;
}

int contarCadenas(const char *entrada){
	int numeroCadenas=0;
	int cCadenas=0;
	char cadenaTemporal[256];
	FILE* archivoEntrada=fopen(entrada,"r");
	
	while(!feof(archivoEntrada)){
		fscanf(archivoEntrada,"%s",cadenaTemporal);
			numeroCadenas++;
	}
		
	fclose(archivoEntrada);
	return numeroCadenas;
}

int contarEnteros(const char* entrada){
	int conteoDeEnteros=0;
	char cadenaTemporal[256];
	FILE* archivoEntrada=fopen(entrada,"r");
	while(!feof(archivoEntrada)){
		fscanf(archivoEntrada,"%s",cadenaTemporal);
		if(es_entero(cadenaTemporal))
		conteoDeEnteros++;
	}
	return conteoDeEnteros;
}

int contarFlotantes(const char* entrada){
	int numFlot=0;
	char cadenaTemporal[256];
	FILE* archivoEntrada=fopen(entrada,"r");
	while(!feof(archivoEntrada)){
		fscanf(archivoEntrada,"%s",cadenaTemporal);
		if(es_flotante(cadenaTemporal)){
			numFlot++;
		}
	}
	return numFlot;
}

void imprimirLinea(const char *entrada, const char *salida){
	int i=1;
	char lineas[256];
	FILE* archivoEntrada=fopen(entrada,"r");
	FILE* archivoSalida=fopen(salida,"w");
	
	while(!feof(archivoEntrada)){
		fgets(lineas,256,archivoEntrada);
		fprintf(archivoSalida,"%d - %s\n",i,lineas);
		printf("%d-%s\n",i,lineas);
		i++;
	}
	fclose(archivoEntrada);
	fclose(archivoSalida);
	
}

void imprimir_lineas_seleccionadas(const char *entrada, bool tablaDeRenglones[], const char *salida){
	char texto[256];			
	// Si el valor de nuestra tabla de lineas a imprimir es 'true' la imprimimos del original, sino, solo imprimimos linea en blanco
	FILE *archivoEntrada = fopen(entrada, "r");
	FILE *archivoSalida = fopen(salida,"w");	
	int i = 0;	
	while (fgets(texto, 256, archivoEntrada) != NULL){
		if(tablaDeRenglones[i++] == true){
			printf("%s",texto);
			fprintf(archivoSalida,"%s",texto);
		}
		else{
			printf("\n");
			fprintf(archivoSalida,"\n");
		}
	}
	fclose(archivoEntrada);
	fclose(archivoSalida);
}

void imprimir_columnas_seleccionadas(const char *entrada, bool tablaDeRenglones[], const char *salida){
	char texto[256];
    int i;

	FILE *archivoEntrada = fopen(entrada, "r");	
	FILE *archivoSalida = fopen(salida,"w");
	while (fgets(texto, 256, archivoEntrada) != NULL) { // ciclamos cada linea
        i = 0;
        while (texto[i] != '\0') { // mientras no llegue al final de la linea
            if(tablaDeRenglones[i] == true){// si el usuario nos indico esa linea para imprimir
                printf("%c",texto[i]); // imprimimos el caracter
                fprintf(archivoSalida,"%c",texto[i]);
            }else{
                printf(" "); // espacio en blanco
                fprintf(archivoSalida," ");
            }
            i++;
        }
        printf("\n");
        fprintf(archivoSalida,"\n");
	}
	fclose(archivoEntrada);
	fclose(archivoSalida);
}

void insertar_saltos(const char *entrada, bool tablaDeRenglones[], const char *salida){
	char texto[256];			
	// Si el valor de nuestra tabla de lineas a imprimir es 'true' la imprimimos del original, sino, solo imprimimos linea en blancoo
	FILE *archivoEntrada = fopen(entrada, "r");
	FILE *archivoSalida = fopen(salida,"w");
	int i = 0;	
	while (fgets(texto, 256, archivoEntrada) != NULL){
		if(tablaDeRenglones[i++] == true){
			printf("%s\n",texto);
			fprintf(archivoSalida,"%s\n",texto);
		}
		else{
			printf("%s",texto);
			fprintf(archivoSalida,"%s",texto);
		}
	}
	fclose(archivoEntrada);
	fclose(archivoSalida);
}

void insertar_tabuladores(const char *entrada, bool tablaDeRenglones[], const char *salida){
	char texto[256];
    int i;

	FILE *archivoEntrada = fopen(entrada, "r");
	FILE *archivoSalida = fopen(salida,"w");
	while (fgets(texto, 256, archivoEntrada) != NULL) { // ciclamos cada linea
        i = 0;
        while (texto[i] != '\0') { // mientras no llegue al final de la linea
            if(tablaDeRenglones[i] == true){ // si el usuario nos indico esa linea para imprimir
                printf("%c\t",texto[i]); // imprimimos el caracter con tabulador
                fprintf(archivoSalida,"%c\t",texto[i]);
            }
            else{
                printf("%c",texto[i]); // solo imprimimos el caracter
                fprintf(archivoSalida,"%c",texto[i]);
            }
            i++;
        }
        printf("\n");
        fprintf(archivoSalida,"\n");
	}
	fclose(archivoEntrada);
	fclose(archivoSalida);
}

bool es_entero(const char *cadena){
  int i;
  int conteoNumeros = 0;
  int conteoPermitidos = 0;
  int conteoOtros = 0;
  
	for(i = 0; cadena[i] != '\0'; i++){
	    if (cadena[i] >= '0' && cadena[i] <='9')
	      conteoNumeros++;
	    else if (cadena[i]=='.' || cadena[i]==',' || cadena[i]==';')
	      conteoPermitidos++; 
	    else
	      conteoOtros++;
	}	
  
	if(conteoOtros == 0){
	    if (conteoPermitidos == 0)
	      return true;
	    else if ((conteoPermitidos == 1) && (cadena[i-1] == '.' || cadena[i-1]==',' || cadena[i-1]==';'))
	      return true;
	    else
	      return false;
	}
    else
        return false;
}

bool es_flotante(const char *cadena){
	int i,conteoFlotantes=0,conteoPuntos=0,conteoPermitidos=0,conteoOtros=0;
		for(i=0;cadena[i]!='\0';i++){
				if(cadena[i]>='0' && cadena[i]<='9')
					conteoFlotantes++;
				else if(cadena[i]=='.')
					conteoPuntos++;
				else if(cadena[i]==',' || cadena[i]==';')
					conteoPermitidos++;	
				else
					conteoOtros++;
		}
		if(conteoOtros==0){
			if(conteoPuntos==1 && conteoPermitidos==0)
				return true;
			else if ((conteoPuntos==1) && (conteoPermitidos==1 && (cadena[i-1]==',' || cadena[i-1]==';')))
				return true;
			else if ((conteoPuntos==2) && (conteoPermitidos==0 && cadena[i-1] == '.'))
				return true;
			else
				return false;
        }
        else
            return false;
        
}
