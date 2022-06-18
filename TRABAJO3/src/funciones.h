#ifndef FUNCIONES_H_
#define FUNCIONES_H_

struct{
	int anio;
	int mes;
	int dia;
}typedef sFecha;


struct{
	int idServicio;
	char nameCliente[51];
	sFecha fecha;
	int diagnostico;
	int idDiagnostico;
	float precio;
	int idMecanico;
	int idLocalidad;
	int estado;
}typedef Servicio;

struct{
	int idMecanico;
	char nameMecanico[50];
	int especialidad;
	int isEmpty;
}typedef Mecanico;

struct{
	int idEspecialidad;
	char nameEspecialidad[26];
}typedef Especialidad;

struct{
	int idDiagnostico;
	char nameDiagnostico[26];
}typedef Diagnostico;

struct{
	int idLocalidad;
	int CodigoPostal;
	char nameLocalidad[50];
}typedef Localidad;

#define TAMLOC 3
#define VACIO 0
#define OCUPADO 1
#define TAM 100
#define TAMM 6
#define TAME 6
#define TAMD 7

void PedirDatos(Servicio listaServicio[], int sizeServicio);

int ObtenerID();

int AddCliente (Servicio listaServicio[],int sizeServicio, int idServicio,char nameCliente[],int anio,int mes,int dia,int idLocalidad);

void AsignarDiagnostico(Servicio listaServicio[],int sizeServicio,Diagnostico Diagnostico[],int diagnosticoSize,int idMecanico,int idDiagnostico,float precio,int index);

int InitServicios (Servicio listaServicio[],int sizeServicios);

int FindClienteById(Servicio listaServicio[], int sizeServicio,int id);

void CargaMecanicos(Mecanico mecanicoLista[], int size);

void MostrarUnMecanico(Mecanico UnMecanico, Especialidad Especialidad[],int especialidadSize);

void MostrarMecanicos(Mecanico listaMecanico[],int size, Especialidad Especialidad[], int especialidadSize);

int ModificarDatos(Servicio listaServicio[],int sizeServicio);

int RemoverDatos(Servicio listaServicio[], int sizeServicio, int id);

int BuscarEspacioLibre(Servicio listaServicio[], int sizeServicio);

int NombreDiagnostico(Servicio listaServicio, Diagnostico diagnostico[], int sizeServicios);

int NombreEspecialidad(Mecanico mecanicosLista, Especialidad especialidad[], int size);

void MostrarUnCliente(Servicio UnCliente, Diagnostico Diagnostico[],int sizeDiagnostico,Mecanico listaMecanicos[], int sizeMecanicos, Especialidad Especialidad[],int sizeEspecialidad,Localidad localidad[],int localidadSize);

void MostrarClientes(Servicio listaServicio[],int sizeServicio,Diagnostico Diagnostico[],int diagnosticoSize, Especialidad Especialidad[],int sizeEspecialidad,Mecanico listaMecanicos[],int sizeMecanicos,Localidad localidad[],int localidadSize);

int NombreLocalidad(Servicio UnServicio, Localidad localidad[], int size);

int NombreMecanico(Servicio UnCliente, Mecanico listaMecanicos[], int size);

void MostrarClientesNoDiagnosticados(Servicio listaServicio[],int sizeServicio,Diagnostico Diagnostico[],int diagnosticoSize, Especialidad Especialidad[],int sizeEspecialidad,Mecanico listaMecanicos[],int sizeMecanicos,Localidad localidad[],int localidadSize);

void MostrarDiagnosticos(Diagnostico Diagnostico[],int diagnosticoSize);

void MostrarMecanicosSinServicio(Servicio listaServicio[], int sizeServicio, Mecanico mecanicos[], int sizeMecanico);

void OrdenarServicios(Servicio listaServicio[],int sizeServicio);

void AceiteFecha(Servicio listaServicio[], int sizeServicio);

void CotizacionDeMecanicos(Servicio Servicios[],int sizeServicios,Mecanico Mecanicos[],int sizeMecanicos);

void OrdenarEspecialidades(Especialidad especialidad[],int sizeEspecialidad);

void MecanicoConMasServicio(Servicio listaServicio[],int sizeServicio,Mecanico listaMecanicos[],int sizeMecanicos);

void PorcentajeDeServicio(Servicio servicioLista[], int sizeServicio, Mecanico mecanicosLista[], int sizeMecanicos, Diagnostico Diagnostico[], int sizeDiagnostico);

void MostrarEspecialidad(Especialidad Especialidad[],int especialidadSize);

void MarzoYMayo(Servicio UnCliente,Servicio listaServicio[], int sizeServ, Diagnostico diagnosticoLista[], int sizeDiagnostico, Mecanico mecanicoLista[], int sizeMeca, Especialidad especialidadLista[], int sizeEspecialidad);

void ServiciosDeterminadosPorFecha(Servicio listaServicio[], int sizeServicio, Mecanico mecanicos[], int sizeMecanico, Especialidad especialidadParametro[], int sizeEspecialidad, Mecanico UnMecanico);

int ContadorDiagnosticos(Servicio listaServicio[],Diagnostico Diagnostico,int sizeServicio);

void TopDesperfectos(Servicio listaServicio[],int sizeServicio,Diagnostico Diagnostico[],int diagnosticoSize);

void MostrarTopDesperfectos(Servicio listaServicio[],int sizeServicio,Diagnostico Diagnostico[],int diagnosticoSize,int mayorDiagnostico);

void MostrarUnDiagnostico(Diagnostico Diagnostico,int diagnosticoSize,int contadorDiagnostico);

void HardCodeoServicios(Servicio list[],int sizeServicio);

void burbujeoTopTres(Diagnostico diagnostico[], int sizeDiagnostico, int mayorDiagnostico, int contadorDiagnostico);

void CotizacionPorLocalidad(Servicio listaServicio[],int sizeServicio,Localidad localidad[],int localidadSize);

#endif /* FUNCIONES_H_ */
