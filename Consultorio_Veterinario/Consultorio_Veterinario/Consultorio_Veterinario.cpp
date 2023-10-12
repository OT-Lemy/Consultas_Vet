#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

// Definición de la estructura Cita
struct CITA {
	char fechaHora[50];
	char nombreCliente[50];
	char nombreMascota[50];
	char motivo[50];
	float costo;
	char status[50];
};

// Definición de la estructura NODOCITA para apuntar a una cita
struct NODOCITA {
	CITA* cita;
	NODOCITA* anterior;
	NODOCITA* siguiente;
};

struct CITAS {
	NODOCITA* origen;
	NODOCITA* fin;
}LISTACITAS;

CITA* crearCita(char nombreCliente[50], char fechaHora[50], char nombreMascota[50], char motivo[50], float costo, char status[50]) {
	CITA* nuevo = new CITA;
	nuevo->costo = costo;
	strcpy_s(nuevo->fechaHora, fechaHora);
	strcpy_s(nuevo->motivo, motivo);
	strcpy_s(nuevo->nombreCliente, nombreCliente);
	strcpy_s(nuevo->nombreMascota, nombreMascota);
	strcpy_s(nuevo->status, status);
	return nuevo;
}
NODOCITA* nuevoNodo(CITA* cita) {
	NODOCITA* nodo = new NODOCITA;
	nodo->cita = cita;
	nodo->siguiente = NULL;
	return nodo;
}

NODOCITA* buscarNombre(char* buscarNomCliente) {
	if (LISTACITAS.origen == NULL)
		return NULL;
	NODOCITA* indice = LISTACITAS.origen;
	while (indice != NULL) {
		if (strcmp(indice->cita->nombreCliente, buscarNomCliente) == 0)
			break;
		indice = indice->siguiente;
	}
	return indice;
}
void AgregarCitaInicio(CITA* cita) {
	NODOCITA* nodo = nuevoNodo(cita);
	if (LISTACITAS.origen == NULL) {
		LISTACITAS.origen = nodo;
		LISTACITAS.fin = nodo;
		nodo->siguiente = NULL;
	}
	else {
		nodo->siguiente = LISTACITAS.origen;
		LISTACITAS.origen = nodo;
	}
}

void agregarCitaFinal(CITA* cita) {
	NODOCITA* nodo = nuevoNodo(cita);
	if (LISTACITAS.origen == NULL) {
		LISTACITAS.origen = nodo;
		LISTACITAS.fin = nodo;
		nodo->siguiente = NULL;
	}
	else {
		LISTACITAS.fin->siguiente = nodo;
		LISTACITAS.fin = nodo;
		nodo->siguiente = NULL;
	}
}
void AgregarCitaMedio(char* buscar, CITA* cita) {
	NODOCITA* busqueda = buscarNombre(buscar);
	if (busqueda == NULL)
		return;
	if (busqueda == LISTACITAS.fin)
		return agregarCitaFinal(cita);
	NODOCITA* nodo = nuevoNodo(cita);
	nodo->siguiente = busqueda->siguiente;
	busqueda->siguiente = nodo;
}

CITA* EliminarCitaInicio() {
	if (LISTACITAS.origen == NULL)
		return NULL;
	if (LISTACITAS.origen == LISTACITAS.fin)
		LISTACITAS.fin = NULL;
	NODOCITA* anterior = LISTACITAS.origen;
	LISTACITAS.origen =
		LISTACITAS.origen->siguiente;
	CITA* cita = anterior->cita;
	delete anterior;
	return cita;
}
CITA* EliminarCitaFinal() {
	if (LISTACITAS.origen == NULL)
		return NULL;
	if (LISTACITAS.origen == LISTACITAS.fin)
		return EliminarCitaInicio();
	NODOCITA* indice = LISTACITAS.origen;
	while (indice != NULL) {
		if (indice->siguiente == LISTACITAS.fin) {
			break;
		}
		indice = indice->siguiente;
	}

	CITA* cita = LISTACITAS.fin->cita;
	delete LISTACITAS.fin;
	LISTACITAS.fin = indice;
	if (indice != NULL)
		indice->siguiente = NULL;
	return cita;
}

CITA* EliminarCitaMedio(char* nombre) {
	NODOCITA* busqueda = buscarNombre(nombre);
	if (busqueda == NULL)
		return NULL;
	if (busqueda == LISTACITAS.origen)
		return EliminarCitaInicio();
	else if (busqueda == LISTACITAS.fin)
		return EliminarCitaFinal();
	NODOCITA* indice = LISTACITAS.origen;
	while (indice != NULL) {
		if (indice->siguiente == busqueda)
			break;
		indice = indice->siguiente;
	}

	CITA* cita = busqueda->cita;
	if (indice != NULL)
		indice->siguiente = busqueda->siguiente;
	delete busqueda;
	return cita;
}
void ImprimirListaCita() {
	NODOCITA* indice = LISTACITAS.origen;
	while (indice != NULL) {
		cout << "("
			<< indice->cita->nombreCliente << ","
			<< indice->cita->costo << ","
			<< indice->cita->fechaHora << ","
			<< indice->cita->motivo << ","
			<< indice->cita->nombreMascota << ","
			<< indice->cita->status << "," ")->"
			<< endl;
		indice = indice->siguiente;
	}
	cout << "No hay citas registradas." << endl;
}

void EliminarListaCita() {
	while (LISTACITAS.origen != NULL) {
		NODOCITA* temporal = LISTACITAS.origen;
		LISTACITAS.origen = LISTACITAS.origen->siguiente;
		if (temporal->cita != NULL)
			delete temporal->cita;
		delete temporal;
	}
}

void EditarCita(char* bNombre) {

	NODOCITA* cita = buscarNombre(bNombre);

	if (cita == NULL) {
		cout << "El cliente no existe." << endl;
		return;
	}

	char nombreCliente[50];
	char nombreMascota[50];
	char fechaHora[50];
	char motivo[100];
	float costo;
	char status[50];

	cout << "Ingrese el nombre del cliente: " << endl;
	cin.ignore();
	cin.getline(nombreCliente, 50);
	cout << "Ingrese el nombre de la mascota: " << endl;
	cin.ignore();
	cin.getline(nombreMascota, 50);
	cout << "Ingrese la nueva fecha y hora de la consulta: " << endl;
	cin.ignore();
	cin.getline(fechaHora, 50);
	cout << "Ingrese el nuevo motivo de la consulta: " << endl;
	cin.ignore();
	cin.getline(motivo, 100);
	cout << "Ingrese el nuevo costo de la consulta: ";
	cin >> costo;
	cout << "Ingrese el nuevo estatus de la consulta: ";
	cin.ignore();
	cin.getline(status, 100);

}

void EliminarCita(char* bNombre) {

	CITA* cita = EliminarCitaMedio(bNombre);
	if (cita == NULL) {
		cout << "El cliente no existe." << endl;
		return;
	}
	delete cita;
	cout << "Se elimino la cita exitosamente" << endl;
}

int main()
{
	CITA citas;

	while (true)
	{
		cout << "\nOpciones:" << endl;
		cout << "1. Agregar cita" << endl;
		cout << "2. Mostrar citas" << endl;
		cout << "3. Modificar cita" << endl;
		cout << "4. Eliminar cita" << endl;
		cout << "5. Salir" << endl;
		cout << "Seleccione una opción: ";

		int opcion;
		cin >> opcion;

		if (opcion == 1)
		{
			char nombreCliente[50];
			char nombreMascota[50];
			char fechaHora[50];
			char motivo[100];
			float costo;
			char status[50];
			cout << "Ingrese el nombre del cliente: " << endl;
			cin.ignore();
			cin.getline(nombreCliente, 50);
			cout << "Ingrese el nombre de la mascota: " << endl;
			cin.ignore();
			cin.getline(nombreMascota, 50);
			cout << "Ingrese la fecha y hora de la consulta: " << endl;
			cin.ignore();
			cin.getline(fechaHora, 50);
			cout << "Ingrese el motivo de la consulta: " << endl;
			cin.ignore();
			cin.getline(motivo, 100);
			cout << "Ingrese el costo de la consulta: ";
			cin >> costo;
			cout << "Ingrese el estatus de la consulta: ";
			cin.ignore();
			cin.getline(status, 100);


			LISTACITAS.origen = NULL;
			LISTACITAS.fin = NULL;
			agregarCitaFinal(crearCita(nombreCliente, fechaHora, nombreMascota, motivo, costo, status));
			cout << "Cita agregada a la agenda." << endl;
		}


		else if (opcion == 2)
		{
			ImprimirListaCita();
		}
		else if (opcion == 3)
		{
			char nombreCliente[50];

			cout << "Ingrese el nombre del cliente a editar";
			cin.ignore();
			cin.getline(nombreCliente, 50);

			EditarCita(nombreCliente);
		}

		else if (opcion == 4)
		{
			char nombreCliente[50];
			cout << "Ingrese el nombre del cliente cuya cita desea eliminar: ";
			cin.ignore();
			cin.getline(nombreCliente, 50);

			EliminarCita(nombreCliente);
		}
		else if (opcion == 5)
		{
			break; // Salir del programa
		}
		else
		{
			cout << "Opción no válida. Intente de nuevo." << endl;
		}
	}

	return 0;
}

