#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funciones.h"
#include "input.h"

int main(void) {
	setbuf(stdout,NULL);
	Servicio listaServicio[TAM];
	Mecanico mecanicosLista[TAMM];
	Mecanico UnMecanico;
	int opcion;
	int opcionLista;
	int id;
	int idMecanico;
	int idServicio;
	int idDiagnostico;
	float precio;
	int indice;
	int contadorClientes = 0;
	int banderaDiagnostico = 0;

	Diagnostico DiagnosticoList[TAMD] = {{0,"Vacio"},{1, "CAMBIO DE ACEITE"} , {2, "REPARACION DE MOTOR"} , {3, "SUSPENSION"},{4,"BUJIAS"},{5,"CORREA"},{6,"VALVULAS"}};
	Especialidad EspecialidadList[TAME] = {{0,"Vacio"},{1,"Mantenimiento"},{2,"Manipulacion"},{3,"Autopartes"},{4,"Ruedas"},{5,"Paragolpes"}};
	Localidad LocalidadList[TAMLOC] = {{1,1888,"Florencio Varela"},{2,1852,"Burzaco"},{3,1889,"Bosques"}};
	InitServicios (listaServicio,TAM);
	CargaMecanicos(mecanicosLista,TAMM);

	do{
		printf("\n=================================================\n"
				"1- ALTA\n2- MODIFICACION\n3- CANCELAR\n4- DIAGNOSTICAR\n5- LISTADO\n6- HARDCODEAR\n7- SALIR\n"
				"=================================================\n");

		opcion = PedirEntero("Opcion: \n","Error, ingrese de nuevo una opción",1,6);

		switch(opcion)
		{
		case 1:
			PedirDatos(listaServicio,TAM);
			contadorClientes++;
		break;

		case 2:
			if(contadorClientes>0)
			{
				ModificarDatos(listaServicio,TAM);
			}
			else
			{
				printf("Error. Tiene que cargar los datos de al menos un cliente.");
			}
		break;

		case 3:
			if(contadorClientes>0)
			{
				id = printf("\nIngresar id:");
				scanf("%d",&id);
				RemoverDatos(listaServicio,TAM,id);
				contadorClientes--;
			}
			else
			{
				printf("Error. Tiene que cargar los datos de al menos un cliente.\n");
			}
		break;

		case 4:
			if(contadorClientes > 0)
			{
				printf("\n===========================================\n");
				printf("ID    ESPECIALIDAD         NOMBRE\n");
				MostrarMecanicos(mecanicosLista, TAMM,EspecialidadList,6);
				printf("\n===========================================\n");
				idMecanico = PedirEntero("Ingrese el ID de un mecánico.","Error, ingrese el ID de un mecánico",1,5);
				printf("\n===========================================\n");
				MostrarClientesNoDiagnosticados(listaServicio,TAM,DiagnosticoList,TAMD,EspecialidadList,TAME,mecanicosLista,TAMM,LocalidadList,TAMLOC);
				printf("\n===========================================\n");
				idServicio = PedirEntero("Ingrese el ID del servicio.","Error, ingrese el ID del servicio.\n",1,TAM);
				indice = FindClienteById(listaServicio,TAM,idServicio);
				while(indice == -1)
				{
					printf("Error, no se encontró el ID del servicio ingresado.\n");
					idServicio = PedirEntero("Ingrese el ID del servicio.\n","Error, ingrese el ID del servicio.\n",1,TAM);
					indice = FindClienteById(listaServicio,TAM,idServicio);
				}
				printf("ID ENCONTRADA CON ÉXITO.\n\n");
				MostrarDiagnosticos(DiagnosticoList,TAMD);
				idDiagnostico = PedirEntero("Ingrese el ID del diagnostico.\n","Error, ingrese el ID del diagnostico",1,TAMD);
				precio = PedirFloat("Ingrese la cotización.\n","Error, ingrese un precio entre 1000 y 100.000",1000,100000);
				AsignarDiagnostico(listaServicio,TAM,DiagnosticoList,TAMD,idMecanico,idDiagnostico,precio,indice);
				banderaDiagnostico = 1;
			}
			else
			{
				printf("\nError. Tiene que cargar los datos de al menos un cliente.\n");
			}
		break;

		case 5:
			if(banderaDiagnostico == 1 && contadorClientes != 0)
			{
				printf("\n===========================================\n"
				"1- Todos los mecánicos.\n"
				"2- Todos los servicios.\n"
				"3- Mecanicos sin servicio.\n"
				"4- Listado de servicios por fecha.\n"
				"5- Suma de cotizaciones en relación a cambio de aceite por fecha.\n"
				"6- Cotizacion promedio de los mecanicos.\n"
				"7- Mecanicos con más servicios.\n"
				"8- Listado de servicios ordenados por especialidad de mecanico alfabéticamente.\n"
				"9- Listado de todos los servicios entre marzo y mayo de 2022 para una especialidad determinada.\n"
				"10- Porcentaje de servicios de cada mecánico.\n"
				"11- Top 3 desperfectos.\n"
				"12- Cotizacion por localidad\n"
				"===========================================\n");
				scanf("%d",&opcionLista);

				switch(opcionLista)
				{
					case 1:
						printf("\n=========================================================\n");
						printf("ID    ESPECIALIDAD         NOMBRE\n");
						MostrarMecanicos(mecanicosLista, TAMM,EspecialidadList,TAME);
						printf("\n=========================================================\n");
					break;

					case 2:
						printf("\n=========================================================\n");
						printf("ID NOMBRE    FECHA     DIAGNOSTICO             MECANICO            ESPECIALIDAD      LOCALIDAD               CODIGO POSTAL  PRECIO\n");
						MostrarClientes(listaServicio,TAM,DiagnosticoList,TAMD,EspecialidadList,TAME,mecanicosLista,TAMM,LocalidadList,TAMLOC);
						printf("\n=========================================================\n");
					break;

					case 3:
						printf("\nMecanicos sin servicios:\n");
						printf("\n=========================================================\n");
						printf("ID    NOMBRE\n");
						MostrarMecanicosSinServicio(listaServicio, TAM, mecanicosLista, TAMM);
					break;

					case 4:
						printf("\n=========================================================\n");
						printf("ID NOMBRE    FECHA     DIAGNOSTICO             MECANICO            ESPECIALIDAD      LOCALIDAD               CODIGO POSTAL  PRECIO\n");
						OrdenarServicios(listaServicio,TAM);
						MostrarClientes(listaServicio,TAM,DiagnosticoList,TAMD,EspecialidadList,TAME,mecanicosLista,TAMM,LocalidadList,TAMLOC);
					break;

					case 5:
						AceiteFecha(listaServicio,TAM);
					break;

					case 6:
						printf("MECANICO         TOTAL          PROMEDIO\n");
						CotizacionDeMecanicos(listaServicio,TAM,mecanicosLista,TAMM);
					break;

					case 7:
						printf("ID          MECANICO        SERVICIOS\n");
						MecanicoConMasServicio(listaServicio,TAM,mecanicosLista,TAMM);
					break;

					case 8:
						OrdenarEspecialidades(EspecialidadList,6);
						MostrarClientes(listaServicio,TAM,DiagnosticoList,TAMD,EspecialidadList,TAME,mecanicosLista,TAMM,LocalidadList,TAMLOC);
					break;

					case 9:
						ServiciosDeterminadosPorFecha(listaServicio, TAM, mecanicosLista,TAMM, EspecialidadList,TAME, UnMecanico);
					break;

					case 10:
						PorcentajeDeServicio(listaServicio,TAM,mecanicosLista,TAMM,DiagnosticoList,TAMD);
					break;

					case 11:
						TopDesperfectos(listaServicio,TAM,DiagnosticoList,TAMD);
					break;

					case 12:
						CotizacionPorLocalidad(listaServicio,TAM,LocalidadList,TAMLOC);
					break;
				}

			}
			else
			{
				printf("Debe diagnosticar al menos un servicio.");
			}
		break;

		case 6:
			HardCodeoServicios(listaServicio,TAM);
			contadorClientes++;
			banderaDiagnostico = 1;
		break;
		}
	}while(opcion !=7);
}
