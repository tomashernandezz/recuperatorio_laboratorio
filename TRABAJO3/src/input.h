#ifndef INPUT_H_
#define INPUT_H_

int PedirCadena(char* cadena, char* mensaje, char* mensajeError,int validar);

int ValidacionDeCaracteres (char cadena[]);

int ValidarNumero (char numeros[]);

float PedirFloat(char mensaje[],char error[],int minimo,int maximo);

int PedirEntero(char mensaje[],char error[],int minimo,int maximo);

void Mayuscula(char name []);

#endif /* INPUT_H_ */
