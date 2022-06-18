#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funciones.h"
#include "input.h"
/// @brief Pide los datos de un servicio
///
/// @param listaServicio
/// @param sizeServicio
void PedirDatos(Servicio listaServicio[], int sizeServicio)
{
	int estado;
	int idServicio;
	char nameCliente[51];
	int anio;
	int dia;
	int mes;
	int idLocalidad;

	idServicio = ObtenerID();

	PedirCadena(nameCliente,"Ingrese su nombre.\n","Error, ingrese su nombre.\n",1);
	Mayuscula(nameCliente);

	anio = PedirEntero("Ingrese el año.","Error, ingrese un año entre 2022 y 2025.\n",2022,2025);

	dia = PedirEntero("Ingrese el día.","Error, ingrese un día entre 1 y 31.",1,31);


	if(dia==31)
	{
		mes = PedirEntero("Ingrese el mes.","Error, ingrese un mes entre 1 y 12",1,12);
		while(mes == 2 || mes ==4 || mes == 6 || mes == 9 || mes == 11)
		{
			printf("Error, ingrese un mes que no sea 2, 4, 6, 9 u 11.");
			mes = PedirEntero("Ingrese el mes.","Error, ingrese un mes entre 1 y 12",1,12);
		}
	}
	else
	{
		if(dia==30)
		{
			mes = PedirEntero("Ingrese el mes.","Error, ingrese un mes entre 1 y 12",1,12);
			while(mes==2)
					{
						printf("Error, ingrese un mes que no sea 2.");
						mes = PedirEntero("Ingrese el mes.","Error, ingrese un mes entre 1 y 12",1,12);
					}
		}
		else
		{
			mes = PedirEntero("Ingrese el mes.","Error, ingrese un mes entre 1 y 12",1,12);
		}
	}

	idLocalidad = PedirEntero("Ingrese la ID de donde vive\n1-Florencio Varela\n2-Burzaco\n3-Bosques","Ingrese la ID de donde vive\n1-Florencio Varela\n2-Burzaco\n3-Bosques",1,3);

	estado = AddCliente(listaServicio,TAM,idServicio,nameCliente,anio,mes,dia,idLocalidad);

	if(estado == -1)
	{
		printf("Hubo un error en la carga. No hay más espacio.");
	}
	else
	{
		printf("Datos cargados exitósamente.");
	}
}

/// @brief Agrega el servicio a la lista
///
/// @param listaServicio
/// @param sizeServicio
/// @param idServicio
/// @param nameCliente
/// @param anio
/// @param mes
/// @param dia
/// @return Retorna que se haya cargado correctamente
int AddCliente (Servicio listaServicio[],int sizeServicio, int idServicio,char nameCliente[],int anio,int mes,int dia,int idLocalidad)
{
	int index;
	int retornoEstado=-1;

	index = BuscarEspacioLibre(listaServicio,sizeServicio);
	if(index !=-1)
	{
		listaServicio[index].idServicio=idServicio;
		strcpy(listaServicio[index].nameCliente,nameCliente);
		listaServicio[index].fecha.dia=dia;
		listaServicio[index].fecha.mes=mes;
		listaServicio[index].fecha.anio=anio;
		listaServicio[index].precio=0;
		listaServicio[index].idMecanico=0;
		listaServicio[index].idDiagnostico=0;
		listaServicio[index].estado=OCUPADO;
		listaServicio[index].idLocalidad = idLocalidad;
		listaServicio[index].diagnostico=0;
		retornoEstado =0;
	}

	return retornoEstado;
}

/// @brief Asigna el diagnostico al servicio
///
/// @param listaServicio
/// @param sizeServicio
/// @param Diagnostico
/// @param diagnosticoSize
/// @param idMecanico
/// @param idDiagnostico
/// @param precio
/// @param index
void AsignarDiagnostico(Servicio listaServicio[],int sizeServicio,Diagnostico Diagnostico[],int diagnosticoSize,int idMecanico,int idDiagnostico,float precio,int index)
{
		listaServicio[index].idMecanico = idMecanico;
		listaServicio[index].precio = precio;
		listaServicio[index].idDiagnostico=idDiagnostico;
		listaServicio[index].diagnostico=1;
}

/// @brief Busca espacio libre/vacío
///
/// @param listaServicio
/// @param sizeServicio
/// @return Retorna la primera ID libre
int BuscarEspacioLibre(Servicio listaServicio[], int sizeServicio)
{
	int index;
	index = -1;
	for(int i=0; i<sizeServicio; i++)
	{
		if(listaServicio[i].estado != OCUPADO)
		{
			index = i;
			break;
		}
	}
	return index;
}

/// @brief Encuentra al cliente por el ID
///
/// @param listaServicio
/// @param sizeServicio
/// @param id
/// @return
int FindClienteById(Servicio listaServicio[], int sizeServicio,int id)
{
    int index = -1;

    for(int i=0;i<sizeServicio;i++)
    {
        if(listaServicio[i].idServicio == id && listaServicio[i].estado==OCUPADO)
        {
            index = i;
            break;
        }
    }

    return index;
}

/// @brief Carga forzada de los mecánicos
///
/// @param mecanicosLista
/// @param sizeMecanicos
void CargaMecanicos(Mecanico mecanicosLista[], int sizeMecanicos)
{
    int id[]={0,1,2,3,4,5};
    char nameMecanico[][50]={"Vacio","Tomás Hernández", "Ignacio Llopis", "Alan Fernandez", "Sergio Chamorro", "Santiago Galvez"};
    int especialidad[] = {0,1,2,3,4,5};
    int isEmpty[]={OCUPADO,OCUPADO,OCUPADO,OCUPADO,OCUPADO,OCUPADO};


    for(int i=0;i<sizeMecanicos;i++)
    {
        mecanicosLista[i].idMecanico = id[i];
        strcpy(mecanicosLista[i].nameMecanico, nameMecanico[i]);
        mecanicosLista[i].especialidad = especialidad[i];
        mecanicosLista[i].isEmpty = isEmpty[i];
    }
}

/// @brief Muestra un mecánico
///
/// @param UnMecanico
/// @param Especialidad
/// @param especialidadSize
void MostrarUnMecanico(Mecanico UnMecanico, Especialidad Especialidad[],int especialidadSize)
{
	int EspecialidadNombre;

	EspecialidadNombre = NombreEspecialidad(UnMecanico, Especialidad,especialidadSize);

	printf("%-5d ",UnMecanico.idMecanico);
	printf("%-20s",Especialidad[EspecialidadNombre].nameEspecialidad);
	printf("%-25s\n",UnMecanico.nameMecanico);
}

/// @brief Muestra todos los mecánicos
///
/// @param listaMecanico
/// @param size
/// @param Especialidad
/// @param especialidadSize
void MostrarMecanicos(Mecanico listaMecanico[],int size, Especialidad Especialidad[], int especialidadSize)
{
	for(int i=1; i<size;i++)
	{
		if(listaMecanico[i].isEmpty == OCUPADO)
		{
			MostrarUnMecanico(listaMecanico[i],Especialidad,especialidadSize);
		}
	}
}

/// @brief Muestra los mecánicos sin servicio
///
/// @param listaServicio
/// @param sizeServicio
/// @param mecanicos
/// @param sizeMecanico
void MostrarMecanicosSinServicio(Servicio listaServicio[], int sizeServicio, Mecanico mecanicos[], int sizeMecanico)
{
    int validar;

    for(int i = 0; i < sizeMecanico; i++)
    {
        validar = 1;

        for(int j = 0; j < sizeServicio; j++)
        {
            if(listaServicio[j].idMecanico == mecanicos[i].idMecanico)
            {
                validar = 0;
            }
        }

        if(validar == 1)
        {
            printf("%-5d %-20s \n", mecanicos[i].idMecanico, mecanicos[i].nameMecanico);
        }
    }
}

/// @brief Asigna un mecánico a un servicio
///
/// @param UnCliente
/// @param listaMecanicos
/// @param size
/// @return Retorna la posicion del ID
int NombreMecanico(Servicio UnCliente, Mecanico listaMecanicos[], int size)
{
    int index =-1;

    for(int i=0;i<size;i++)
    {
        if(UnCliente.idMecanico==listaMecanicos[i].idMecanico)
        {
            index=i;
            break;
        }
    }
    return index;
}

/// @brief Muestra un servicio
///
/// @param UnCliente
/// @param Diagnostico
/// @param sizeDiagnostico
/// @param listaMecanicos
/// @param sizeMecanicos
/// @param Especialidad
/// @param sizeEspecialidad
void MostrarUnCliente(Servicio UnCliente, Diagnostico Diagnostico[],int sizeDiagnostico,Mecanico listaMecanicos[], int sizeMecanicos, Especialidad Especialidad[],int sizeEspecialidad,Localidad localidad[],int localidadSize)
{
	int NameDiagnostico;
	int NameEspecialidad;
	int NameMecanico;
	int NameLocalidad;

	NameDiagnostico = NombreDiagnostico(UnCliente,Diagnostico,sizeDiagnostico);
	NameMecanico = NombreMecanico(UnCliente,listaMecanicos, sizeMecanicos);
	NameEspecialidad = NombreEspecialidad(listaMecanicos[NameMecanico], Especialidad, sizeEspecialidad);
	NameLocalidad = NombreLocalidad(UnCliente,localidad,localidadSize);

	printf("%-3d",UnCliente.idServicio);
	printf("%-10s",UnCliente.nameCliente);
	printf("%d/",UnCliente.fecha.dia);
	printf("%d/",UnCliente.fecha.mes);
	printf("%d  ",UnCliente.fecha.anio);
	printf("%-23s ",Diagnostico[NameDiagnostico].nameDiagnostico);
	printf("%s     ",listaMecanicos[NameMecanico].nameMecanico);
	printf("%s           ",Especialidad[NameEspecialidad].nameEspecialidad);
	printf("%s         ",localidad[NameLocalidad].nameLocalidad);
	printf("%d     ",localidad[NameLocalidad].CodigoPostal);
	printf("%.2f\n",UnCliente.precio);
}

/// @brief Matchea Id de especialidad
///
/// @param UnMecanico
/// @param especialidad
/// @param size
/// @return
int NombreEspecialidad(Mecanico UnMecanico, Especialidad especialidad[], int size)
{
    int index =-1;

    for(int i=0;i<size;i++)
    {
        if(UnMecanico.especialidad==especialidad[i].idEspecialidad)
        {
            index=i;
            break;
        }
    }
    return index;
}

/// @brief Matchea ID de localidad
///
/// @param UnServicio
/// @param localidad
/// @param size
/// @return
int NombreLocalidad(Servicio UnServicio, Localidad localidad[], int size)
{
    int index =-1;

    for(int i=0;i<size;i++)
    {
        if(UnServicio.idLocalidad==localidad[i].idLocalidad)
        {
            index=i;
            break;
        }
    }
    return index;
}

/// @brief Matchea el ID de diagnostico
///
/// @param listaServicio
/// @param diagnostico
/// @param sizeDiagnostico
/// @return
int NombreDiagnostico(Servicio listaServicio, Diagnostico diagnostico[], int sizeDiagnostico)
{
    int index =-1;

    for(int i=0;i<sizeDiagnostico;i++)
    {
        if(listaServicio.idDiagnostico==diagnostico[i].idDiagnostico)
        {
            index=i;
            break;
        }
    }
    return index;
}

/// @brief Modifica los datos del servicio
///
/// @param listaServicio
/// @param sizeServicio
/// @return
int ModificarDatos(Servicio listaServicio[],int sizeServicio)
{
		int index;
		int opcion;
		int id;
		int retorno =-1;
		char nameCliente[51];
		int anio;
		int dia;
		int mes;
		int idMecanico;
		Servicio aux;

		printf("ingrese el id del servicio: ");
		scanf("%d", &id);

		index = FindClienteById(listaServicio, sizeServicio, id);
		if(index!=-1)
		{
			retorno= 0;
			aux=listaServicio[index];

			printf("CLIENTE: %s\n", listaServicio[index].nameCliente);

			printf("Ingrese la opción que desea modificar:\n"
					"1- Nombre del cliente.\n"
					"2- Fecha \n"
					"3- Mecanico\n"
					"4- No modificar nada.\n"
					"Opcion: ");

				scanf("%d", &opcion);
				while(opcion < 1 || opcion > 7)
					{
						printf("Error, vuelva a ingresar una opción. \n");
						scanf("%d", &opcion);
					}

				switch(opcion)
					{
					case 1:
						PedirCadena(nameCliente,"Ingrese su nombre.\n","Error, ingrese su nombre.\n",1);
						Mayuscula(nameCliente);
						strcpy(aux.nameCliente,nameCliente);
					break;

					case 2:
						anio = PedirEntero("Ingrese el año.","Error, ingrese un año entre 2022 y 2025.\n",2022,2025);

						dia = PedirEntero("Ingrese el día.","Error, ingrese un día entre 1 y 31.",1,31);

						if(dia==31)
						{
							mes = PedirEntero("Ingrese el mes.","Error, ingrese un mes entre 1 y 12",1,12);
							while(mes == 2 || mes ==4 || mes == 6 || mes == 9 || mes == 11)
							{
								printf("Error, ingrese un mes que no sea 2, 4, 6, 9 u 11.");
								mes = PedirEntero("Ingrese el mes.","Error, ingrese un mes entre 1 y 12",1,12);
							}
						}
						else
						{
							if(dia==30)
							{
								mes = PedirEntero("Ingrese el mes.","Error, ingrese un mes entre 1 y 12",1,12);
								while(mes==2)
										{
											printf("Error, ingrese un mes que no sea 2.");
											mes = PedirEntero("Ingrese el mes.","Error, ingrese un mes entre 1 y 12",1,12);
										}
							}
							else
							{
								mes = PedirEntero("Ingrese el mes.","Error, ingrese un mes entre 1 y 12",1,12);
							}
						}
						aux.fecha.anio=anio;
						aux.fecha.dia=dia;
						aux.fecha.mes=mes;
					break;

					case 3:
						idMecanico = PedirEntero("Ingrese el id de un mecanico","Error, elija un número entre 1 y 5",1,5);
						aux.idMecanico=idMecanico;
					break;
					}
				if(retorno == 0)
				{
					listaServicio[index] = aux;
				}
				else
				{
					retorno = -1;
				}
		}
		else
		{
			printf("No se ha encontrado el id\n");
			retorno = -1;
		}


		return retorno;
}

/// @brief Remueve los datos de un cliente
///
/// @param listaServicio
/// @param sizeServicio
/// @param id
/// @return
int RemoverDatos(Servicio listaServicio[], int sizeServicio, int id)
{
	int index;
	int retornoEstado=-1;
	index=FindClienteById(listaServicio,sizeServicio,id);
	if (index != -1)
	{
		printf("El cliente %s ha sido eliminado.\n",listaServicio[index].nameCliente);
		listaServicio[index].estado = VACIO;
	}
	else
	{
		printf("Cliente no encontrado \n");
		retornoEstado = 0;
	}

	return retornoEstado;
}

/// @brief Inicializa los servicios
///
/// @param listaServicio
/// @param sizeServicios
/// @return
int InitServicios (Servicio listaServicio[],int sizeServicios)
{
	int resultado;

	if (sizeServicios < 0 && sizeServicios > 100)
	{
		resultado =-1;
	}
	else
	{
		resultado=0;
	}
	for(int i=0;i<sizeServicios;i++)
	{
		listaServicio[i].estado=VACIO;
		listaServicio[i].idMecanico=0;
		listaServicio[i].diagnostico=0;
	}

	return resultado;
}

/// @brief Muestra los servicios no diagnosticados
///
/// @param listaServicio
/// @param sizeServicio
/// @param Diagnostico
/// @param diagnosticoSize
/// @param Especialidad
/// @param sizeEspecialidad
/// @param listaMecanicos
/// @param sizeMecanicos
void MostrarClientesNoDiagnosticados(Servicio listaServicio[],int sizeServicio,Diagnostico Diagnostico[],int diagnosticoSize, Especialidad Especialidad[],int sizeEspecialidad,Mecanico listaMecanicos[],int sizeMecanicos,Localidad localidad[],int localidadSize)
{
	for(int i=0; i<sizeServicio; i++)
	{
		if(listaServicio[i].estado == OCUPADO && listaServicio[i].diagnostico == 0)
		{
			MostrarUnCliente(listaServicio[i],Diagnostico,diagnosticoSize,listaMecanicos,sizeMecanicos,Especialidad,sizeEspecialidad,localidad,localidadSize);
		}
	}
}

/// @brief Muestra todos los servicios
///
/// @param listaServicio
/// @param sizeServicio
/// @param Diagnostico
/// @param diagnosticoSize
/// @param Especialidad
/// @param sizeEspecialidad
/// @param listaMecanicos
/// @param sizeMecanicos
void MostrarClientes(Servicio listaServicio[],int sizeServicio,Diagnostico Diagnostico[],int diagnosticoSize, Especialidad Especialidad[],int sizeEspecialidad,Mecanico listaMecanicos[],int sizeMecanicos,Localidad localidad[],int localidadSize)
{
	for(int i=0; i<sizeServicio; i++)
	{
			if(listaServicio[i].estado == OCUPADO)
			{
				MostrarUnCliente(listaServicio[i],Diagnostico,diagnosticoSize,listaMecanicos,sizeMecanicos,Especialidad,sizeEspecialidad,localidad,localidadSize);
			}
	}
}

/// @brief Muestra los diagnosticos disponibles
///
/// @param Diagnostico
/// @param diagnosticoSize
void MostrarDiagnosticos(Diagnostico Diagnostico[],int diagnosticoSize)
{
	for(int i=1;i < diagnosticoSize;i++)
	{
		printf("%d ",Diagnostico[i].idDiagnostico);
		printf("%s\n",Diagnostico[i].nameDiagnostico);
	}
}

/// @brief Ordena los servicios por fecha
///
/// @param listaServicio
/// @param sizeServicio
void OrdenarServicios(Servicio listaServicio[],int sizeServicio)
{
	Servicio auxiliar;

	for(int i=0; i<sizeServicio-1; i++)
	{
		for(int j =1; j<sizeServicio;j++)
		{
			if(listaServicio[i].fecha.anio > listaServicio[j].fecha.anio)
			{
				auxiliar = listaServicio[i];
				listaServicio[i] = listaServicio[j];
				listaServicio[j] = auxiliar;
			}
			else
			{
				if(listaServicio[i].fecha.anio == listaServicio[j].fecha.anio)
				{
					if(listaServicio[i].fecha.mes > listaServicio[j].fecha.mes)
					{
						auxiliar = listaServicio[i];
						listaServicio[i] = listaServicio[j];
						listaServicio[j] = auxiliar;
					}
					else
					{
						if(listaServicio[i].fecha.mes == listaServicio[j].fecha.mes)
						{
							if(listaServicio[i].fecha.dia > listaServicio[j].fecha.dia)
							{
								auxiliar = listaServicio[i];
								listaServicio[i] = listaServicio[j];
								listaServicio[j] = auxiliar;
							}
						}
					}
				}
			}
		}
	}
}

/// @brief Suma de cotizaciones en relación a cambio de aceite por fecha.
///
/// @param listaServicio
/// @param sizeServicio
void AceiteFecha(Servicio listaServicio[], int sizeServicio)
{
    float total=0;
    int anio,mes,dia;

    anio = PedirEntero("Ingrese el año. ","Error, ingrese un año entre 2022 y 2025.\n",2022,2025);

    dia = PedirEntero("Ingrese el día. ","Error, ingrese un día entre 1 y 31.",1,31);

    	if(dia==31)
    	{
    		mes = PedirEntero("Ingrese el mes. ","Error, ingrese un mes entre 1 y 12",1,12);
    		while(mes == 2 || mes ==4 || mes == 6 || mes == 9 || mes == 11)
    		{
    			printf("Error, ingrese un mes que no sea 2, 4, 6, 9 u 11. ");
    			mes = PedirEntero("Ingrese el mes. ","Error, ingrese un mes entre 1 y 12 ",1,12);
    		}
    	}
    	else
    	{
    		if(dia==30)
    		{
    			mes = PedirEntero("Ingrese el mes. ","Error, ingrese un mes entre 1 y 12 ",1,12);
    			while(mes==2)
    					{
    						printf("Error, ingrese un mes que no sea 2.");
    						mes = PedirEntero("Ingrese el mes. ","Error, ingrese un mes entre 1 y 12 ",1,12);
    					}
    		}
    		else
    		{
    			mes = PedirEntero("Ingrese el mes. ","Error, ingrese un mes entre 1 y 12 ",1,12);
    		}
    	}

    for(int i=0;i<sizeServicio;i++)
    {
        if(listaServicio[i].diagnostico == 1 && listaServicio[i].estado == OCUPADO && listaServicio[i].fecha.anio == anio && listaServicio[i].fecha.mes == mes && listaServicio[i].fecha.dia == dia)
        {
            total = total + listaServicio[i].precio;
        }
    }

    printf("En el día %d/%d/%d hubo un total de $%.2f",dia,mes,anio,total);
}

/// @brief Cotizacion total de los mecánicos.
///
/// @param Servicios
/// @param sizeServicios
/// @param Mecanicos
/// @param sizeMecanicos
void CotizacionDeMecanicos(Servicio Servicios[],int sizeServicios,Mecanico Mecanicos[],int sizeMecanicos)
{
	float total;
	float promedio;
	int contador;

	for(int i=1;i<sizeMecanicos;i++)
	{
		contador = 0;
		total = 0;
		for(int j=0;j<sizeServicios;j++)
		{
			if(Servicios[j].idMecanico == Mecanicos[i].idMecanico)
			{
				contador++;
				total=Servicios[j].precio+total;
			}
		}

		if(contador > 0)
		{
			promedio = total/contador;
		}
		else
		{
			promedio = 0;
		}
		printf("%s   %f             %f\n",Mecanicos[i].nameMecanico,total,promedio);
	}
}

/// @brief Ordena las especialidad alfabeticamente
///
/// @param especialidad
/// @param sizeEspecialidad
void OrdenarEspecialidades(Especialidad especialidad[],int sizeEspecialidad)
{
	Especialidad aux;

	for(int i=0;i<sizeEspecialidad-1;i++)
	{
		for(int j=i+1;j<sizeEspecialidad;j++)
		{
			if(strcmp(especialidad[i].nameEspecialidad,especialidad[j].nameEspecialidad)>0)
			{
				aux = especialidad[i];
				especialidad[i] = especialidad[j];
				especialidad[j] = aux;
			}
		}
	}
}

/// @brief Muestra al mecanico con más servicios
///
/// @param listaServicio
/// @param size
/// @param listaMecanicos
/// @param sizeMecanicos
void MecanicoConMasServicio(Servicio listaServicio[], int size, Mecanico listaMecanicos[], int sizeMecanicos)
{
    int contador;
    int bandera = 1;
    int maximos;

    for(int i = 1; i < sizeMecanicos; i++)
    {
        contador = 0;
        for(int j = 0; j < size; j++)
        {
            if(listaMecanicos[i].idMecanico == listaServicio[j].idMecanico && listaServicio[j].estado == OCUPADO)
            {
                contador++;
            }
        }

        if(bandera == 1)
        {
            maximos = contador;
            bandera = 0;
        }
        else
        {
            if(contador > maximos)
            {
                maximos = contador;
            }
        }
    }

    for(int i = 1; i < sizeMecanicos; i++)
    {
        contador = 0;
        for(int j = 0; j < size; j++)
        {
            if(listaMecanicos[i].idMecanico == listaServicio[j].idMecanico && listaServicio[j].estado == OCUPADO)
            {
                contador++;
            }
        }
        if(contador == maximos)
        {
            printf("%d           %s %d\n", listaMecanicos[i].idMecanico, listaMecanicos[i].nameMecanico,contador);
        }
    }
}

/// @brief Muestra el porcentaje de cada mecanico
///
/// @param servicioLista
/// @param sizeServicio
/// @param mecanicosLista
/// @param sizeMecanicos
/// @param Diagnostico
/// @param sizeDiagnostico
void PorcentajeDeServicio(Servicio servicioLista[], int sizeServicio, Mecanico mecanicosLista[], int sizeMecanicos, Diagnostico Diagnostico[], int sizeDiagnostico)
{
		float contadorD = 0;
		float contadorM = 0;
		float porcentaje;
		int flag=1;

		for(int i=0;i<sizeServicio;i++)
		{
			if(servicioLista[i].idDiagnostico > 0 && servicioLista[i].estado == OCUPADO)
			{
				contadorD++;
			}
		}

		printf("Hay %.2f diagnosticos.\n", contadorD);

		for(int j=1; j<sizeMecanicos; j++)
		{
			contadorM = 0;
			for(int k=0; k<sizeServicio; k++)
			{
				if(servicioLista[k].estado == OCUPADO && mecanicosLista[j].idMecanico == servicioLista[k].idMecanico)
				{
					contadorM++;
				}
			}

			if(contadorM > 0)
			{
				porcentaje = (contadorM/contadorD)*100;
		  }
			else
			{
				porcentaje = 0;
			}

			if(flag==1)
			{
				printf("                                                                \n"
					     "    ID              MECANICO                 PORCENTAJE         \n");
				flag = 0;
			}
			printf(" %4d | %25s | %15.2f%c      \n", mecanicosLista[j].idMecanico, mecanicosLista[j].nameMecanico, porcentaje,'%');

		}
}

/// @brief Muestra las especialidades
///
/// @param Especialidad
/// @param especialidadSize
void MostrarEspecialidad(Especialidad Especialidad[],int especialidadSize)
{
	for(int i=1;i < especialidadSize;i++)
	{
		printf("%d ",Especialidad[i].idEspecialidad);
		printf("%s\n",Especialidad[i].nameEspecialidad);
	}
}

/// @brief Listado de todos los servicios entre marzo y mayo de 2022 para una especialidad determinada
///
/// @param listaServicio
/// @param sizeServicio
/// @param mecanicos
/// @param sizeMecanico
/// @param especialidadParametro
/// @param sizeEspecialidad
/// @param mecanico
void ServiciosDeterminadosPorFecha(Servicio listaServicio[], int sizeServicio, Mecanico mecanicos[], int sizeMecanico, Especialidad especialidadParametro[], int sizeEspecialidad, Mecanico mecanico)
{
	char especialidadObtenida[20];
	int indiceEspecialidad = 0;

	printf("Especialidades: Mantenimiento -- Manipulacion -- Autopartes -- Ruedas -- Paragolpes\n");

	PedirCadena(especialidadObtenida, "\nIngrese la especialidad que usará para ver los servicios: \n","\nSOLO LETRAS\nIngrese la especialidad que usará para ver los servicios: \n",0);
	strlwr(especialidadObtenida);
	Mayuscula(especialidadObtenida);

	while(strcmp(especialidadObtenida, "Mantenimiento") != 0 && strcmp(especialidadObtenida, "Manipulacion") != 0 && strcmp(especialidadObtenida, "Autopartes") != 0 && strcmp(especialidadObtenida,"Ruedas") != 0 && strcmp(especialidadObtenida,"Paragolpes") != 0 )
	{
		PedirCadena(especialidadObtenida, "\nIngrese la especialidad que usará para ver los servicios: \n","\nSOLO LETRAS\nIngrese la especialidad que usará para ver los servicios: \n",0);
		strlwr(especialidadObtenida);
		Mayuscula(especialidadObtenida);
	}

	for(int i = 0; i < sizeMecanico; i++)
	{
		indiceEspecialidad = NombreEspecialidad(mecanicos[i], especialidadParametro, sizeEspecialidad);
		for(int j = 0; j < sizeServicio; j++)
		{
			if((listaServicio[j].fecha.mes > 2 && listaServicio[j].fecha.mes < 6 && listaServicio[j].fecha.anio == 2022) && (listaServicio[j].estado == OCUPADO) && (mecanicos[i].idMecanico == listaServicio[j].idMecanico))
			{
				if(strcmp(especialidadObtenida, especialidadParametro[indiceEspecialidad].nameEspecialidad) == 0)
				{
					printf("ID: %d -- Nombre: %s -- Fecha: %d/%d/%d -- Mecánico: %s -- Especialidad: %s\n", listaServicio[j].idServicio, listaServicio[i].nameCliente,
					listaServicio[j].fecha.dia, listaServicio[j].fecha.mes, listaServicio[j].fecha.anio, mecanicos[i].nameMecanico, especialidadParametro[indiceEspecialidad].nameEspecialidad);
				}
			}
		}
	}
}

/// @brief Printea el top de desperfectos
///
/// @param listaServicio
/// @param sizeServicio
/// @param Diagnostico
/// @param diagnosticoSize
void TopDesperfectos(Servicio listaServicio[],int sizeServicio,Diagnostico Diagnostico[],int diagnosticoSize)
{
	int contadorDiagnostico;
	int mayorDiagnostico;
	int flag = 0;

	for(int i=0;i<diagnosticoSize;i++)
	{
		contadorDiagnostico = ContadorDiagnosticos(listaServicio,Diagnostico[i],sizeServicio);
		if(contadorDiagnostico > mayorDiagnostico || flag == 0)
		{
			mayorDiagnostico = contadorDiagnostico;
			flag = 1;
		}
	}
	printf("ID      DIAGNOSTICO     CANTIDAD DIAGNOSTICADA \n");
	MostrarTopDesperfectos(listaServicio,sizeServicio,Diagnostico,diagnosticoSize,mayorDiagnostico);

}

/// @brief Contador de cada diagnostico
///
/// @param listaServicio
/// @param Diagnostico
/// @param sizeServicio
/// @return Devuelve el valor del contador
int ContadorDiagnosticos(Servicio listaServicio[],Diagnostico Diagnostico,int sizeServicio)
{
	int contador1 = 0;

	for(int i=0;i<sizeServicio;i++)
	{
		if(listaServicio[i].idDiagnostico == Diagnostico.idDiagnostico && Diagnostico.idDiagnostico > 0 && listaServicio[i].estado == OCUPADO)
		{
			contador1++;
		}
	}
	return contador1;
}

/// @brief Muestra el diagnostico y hace el burbujeo
///
/// @param listaServicio
/// @param sizeServicio
/// @param Diagnostico
/// @param diagnosticoSize
/// @param mayorDiagnostico
void MostrarTopDesperfectos(Servicio listaServicio[],int sizeServicio,Diagnostico Diagnostico[],int diagnosticoSize,int mayorDiagnostico)
{
	int contadorDiagnostico;

	for(int i=0;i<diagnosticoSize;i++)
	{
		contadorDiagnostico = ContadorDiagnosticos(listaServicio,Diagnostico[i],sizeServicio);
		if(contadorDiagnostico != 0)
		{
			if(contadorDiagnostico <= mayorDiagnostico)
			{
				burbujeoTopTres(Diagnostico, diagnosticoSize, mayorDiagnostico,contadorDiagnostico);
				MostrarUnDiagnostico(Diagnostico[i],diagnosticoSize,contadorDiagnostico);
			}
		}
	}
}

/// @brief Muestra un diagnostico
///
/// @param Diagnostico
/// @param diagnosticoSize
/// @param contadorDiagnostico
void MostrarUnDiagnostico(Diagnostico Diagnostico,int diagnosticoSize,int contadorDiagnostico)
{

	printf("%d       %-17s       %d\n",Diagnostico.idDiagnostico,Diagnostico.nameDiagnostico,contadorDiagnostico);
}

/// @brief Hardcodea los servicios
///
/// @param list
/// @param sizeServicio
void HardCodeoServicios(Servicio list[],int sizeServicio)
{
    int id[] = {1,2,3,4,5,6};
    char name[][51] = {"Christian","Matias","Juliana","Leo","Alejandro","Roberto"};
    sFecha fechas[] = {{2022,4,2},{2022,4,2},{2022,6,3},{2022,1,2},{20223,4,2},{2025,10,20}};
    float price[] = {50000,25000,60000,30000,25000,1500};
    int idDiagnostico[] = {1,1,3,1,3,2};
    int idMecanico[] = {5,1,1,3,2,2};
    int idLocalidad[] = {1,2,2,3,3,2};
    int isEmpty[]={1,1,1,1,1,1};

    for(int i=0;i<6;i++)
    {
        list[i].idServicio = id[i];
        strcpy(list[i].nameCliente, name[i]);
        list[i].fecha = fechas[i];
        list[i].precio = price[i];
        list[i].idDiagnostico = idDiagnostico[i];
        list[i].idMecanico = idMecanico[i];
        list[i].idLocalidad = idLocalidad[i];
        list[i].estado = isEmpty[i];
    }
}

/// @brief Burbujeo del TOP 3
///
/// @param diagnostico
/// @param sizeDiagnostico
/// @param mayorDiagnostico
/// @param contadorDiagnostico
void burbujeoTopTres(Diagnostico diagnostico[], int sizeDiagnostico, int mayorDiagnostico, int contadorDiagnostico)
{
		Diagnostico auxiliar;

    for(int i = 0; i<sizeDiagnostico-1; i++)
    {
        for(int j = i+1; j<sizeDiagnostico; j++)
        {
            if(contadorDiagnostico > mayorDiagnostico)
            {
                auxiliar = diagnostico[i];
                diagnostico[i] = diagnostico[j];
                diagnostico[j] = auxiliar;
            }
            else
            {
                if(contadorDiagnostico < mayorDiagnostico)
                {
                    auxiliar = diagnostico[i];
                    diagnostico[i] = diagnostico[j];
                    diagnostico[j] = auxiliar;
                }else
                {
                    if(contadorDiagnostico == mayorDiagnostico)
                    {
                        auxiliar = diagnostico[i];
                        diagnostico[i] = diagnostico[j];
                        diagnostico[j] = auxiliar;
                    }
                }
            }
        }
    }
}
/// @brief Muestra la cotización por localidad
///
/// @param listaServicio
/// @param sizeServicio
/// @param localidad
/// @param localidadSize
void CotizacionPorLocalidad(Servicio listaServicio[],int sizeServicio,Localidad localidad[],int localidadSize)
{
	float acumulador;
	int banderaHeader = 0;

	for(int i=0;i<localidadSize;i++)
	{
		acumulador = 0;
		for(int j=0;j<sizeServicio;j++)
		{
			if(localidad[i].idLocalidad == listaServicio[j].idLocalidad)
			{
				acumulador = acumulador + listaServicio[j].precio;
			}
		}
		if(banderaHeader == 0)
		{
		printf("CODIGO POSTAL     LOCALIDAD                     COTIZACION TOTAL\n");
		banderaHeader = 1;
		}
		printf("%d              %-19s           %f\n",localidad[i].CodigoPostal,localidad[i].nameLocalidad,acumulador);
	}
}
