#include <conio.h>
#include <stdlib.h>
#include <windows.h> 
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>

using namespace std;
typedef unsigned short USHORT;
HANDLE g_handle;

static int orden = 0; //valor estatico para el numero de orden y se hará de forma automatica, de esa forma el numero de cita no podra repetirse
struct Citasinfo //struct con variables que seran usadas para agregar a personas
{
	int numord = orden; //este es el número de la cita, se iguala al valor static de orden, el cual vale 0, por lo que las citas comenzaran vailendo desde 0 hasta las que se ingresen
	int codigoprodu;
	char nombrepaciente[40];
	int horas;
	int minutos;
	char nombretratamiento[25];
	char descripcion[200];
	float precio = 0;
	int cantidad = 0;
	float subtotal = 0;
	float total = 0;
	float iv = 0;
	char quicksort[1];
	char cloudname;
	int nummy;
	Citasinfo* sigi;
	Citasinfo* ante;
}*primis, * ultim;

Citasinfo* buch = NULL;

void RegCitas(Citasinfo* nuevo) //lista doblemente ligada.
{
	if (primis == NULL)
	{
		primis = nuevo;
		primis->sigi = NULL;
		primis->ante = NULL;
		ultim = primis;
	}
	else
	{
		ultim->sigi = nuevo;
		nuevo->sigi = NULL;
		nuevo->ante = ultim;
		ultim = nuevo;
	}
}

int arrnomb[25];
int nobu = 0;
char nob[1];

bool isnumeric(char texto[100]) //funcion para verificar que no se haya digitado ningún caracter en el codigo del produtcto
{                               // utiliza el codigo ascii para verificarlo 
	int val, cont=0, comp;

	string suplente;

	char letra;


	suplente = texto;

	comp = suplente.length();


	int i, j;

	int ini = 48;
	int fin = 57;

	for (i = 0; i <= comp; i++)
	{
		letra = texto[i];
		val = letra;

		for (j = ini; j <= fin; j++)
		{
			if (val == j)
			{
				cont++;
			}
		}

	}


	if (comp == cont)
	{
		return true;
	}
	else
	{
		return false;
	}

}

int partition(int arr[], int start, int end)
{

	int pivot = arr[start];

	int count = 0;
	for (int i = start + 1; i <= end; i++) {
		if (arr[i] <= pivot)
			count++;
	}

	// Giving pivot element its correct position
	int pivotIndex = start + count;
	swap(arr[pivotIndex], arr[start]);

	// Sorting left and right parts of the pivot element
	int i = start, j = end;

	while (i < pivotIndex && j > pivotIndex) {

		while (arr[i] <= pivot) {
			i++;
		}

		while (arr[j] > pivot) {
			j--;
		}

		if (i < pivotIndex && j > pivotIndex) {
			swap(arr[i++], arr[j--]);
		}
	}

	return pivotIndex;
}

void quickSort(int arr[], int start, int end)
{

	// base case
	if (start >= end)
		return;

	// partitioning the array
	int p = partition(arr, start, end);

	// Sorting the left part
	quickSort(arr, start, p - 1);

	// Sorting the right part
	quickSort(arr, p + 1, end);
}

void gotoxy(USHORT x, USHORT y)
{
	g_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cp = { x,y };
	SetConsoleCursorPosition(g_handle, cp);
}; //la función gotoxy se usa para mover la posición de lo que aparece en pantalla, de esta forma se puede jugar con el diseño para hacerlo mas vistoso.

int main()
{
	fstream archivo("Citas.txt");
	int dato, opcion;
	char a = 163; // esta variable es para el acento en la u, meramente usada para diseño. Manda a llamar a ú por medio del codigo ascii
	char s = 36; // esta variable es para el signo $, meramente usada para diseño. Manda a llamar a $ por medio del codigo ascii
	char o = 162; // esta variable es para el acento en la o, meramente usada para diseño. Manda a llamar a ó por medio del codigo ascii
	char nombres[25];// esta variable fue creada con el proposito de acomodar los nombres de forma alfabetica.

	do {
		gotoxy(28, 3); printf("M E N U   P R I N C I P A L");
		gotoxy(30, 5); cout << "[1].- Agendar Cita. " << endl;
		gotoxy(30, 6); cout << "[2].- Modificar Cita." << endl;
		gotoxy(30, 7); cout << "[3].- Eliminar Cita." << endl;
		gotoxy(30, 8); cout << "[4].- Lista de Citas Vijentes.(ordenada por Numero de Cita)" << endl;
		gotoxy(30, 9); cout << "[5].- Lista de Citas Vijentes.(ordenada por Nombre del producto)" << endl;
		gotoxy(30, 10); cout << "[6].- Salir." << endl;
		gotoxy(30, 11); cout << "Opcion: ";
		cin >> opcion;

		switch (opcion)
		{
		case 1:	
		   {
			   system("cls");
			   char digitos[100];
			   string espacio;
			   Citasinfo* regcit = new Citasinfo; // se crea un puntero para apuntar a las variables del struct
			   cout << "\nN" << a << "mero de Cita : " << regcit->numord << endl; 
			   cout << endl << "Digitar el codigo del producto : ";
			   cin >> digitos;

			   if (isnumeric(digitos))
			   {
				   regcit->codigoprodu = atoi(digitos); //se convierte el char digitos a un valor int con la funcion atoi.

				   if (regcit->codigoprodu >= 100000 || regcit->codigoprodu < 10000) // este if esta presente para evitar que se escriban mas de 5 digitos en el codigo del producto
				   {
					   cout << "\nSolo se permiten 5 digitos" << endl;
					   break;
				   }
			   }
			   else
			   {
				   cout << "\nIngresar solo N" << a << "meros.\n \n";
				   break;
			   }
			   
			   cout << endl;
			   printf("Nombre del paciente : ");
               cin.ignore();
			   cin.getline(regcit->nombrepaciente, 40, '\n');

			   cout << endl << "Digitar Hora del tratamiento (24 horas) : ";
			   cin >> regcit->horas;
			   gotoxy(45, 7); cout << ": "; // el gotoxy hace que los " : " aparezcan al lado de las horas, se uso debido a que el cin salta de linea automaticamente.
			   cin >> regcit->minutos;
			   if (regcit->horas >= 24 || regcit->minutos >= 60)  //este if es para asegurarse de que no se escriba horas que no existen dentro del reloj de 24 horas
			   {
				   cout << "\nEscribir una hora valida" << endl;
				   break;
			   }
			   cout << endl;
			   printf("Nombre del tratamiento : ");
			   cin.ignore();
			   cin.getline(regcit->nombretratamiento, 25, '\n');

			   cout << endl;
			   printf("Descripcion : ");
			   cin.ignore();
			   cin.getline(regcit->descripcion, 400, '\n');

			   cout << endl << "Cantidad a vender : ";
			   cin >> regcit->cantidad;

			   cout << endl << "Precio unitario : " << s;
			   cin >> regcit->precio;

			   regcit->subtotal = regcit->precio * regcit->cantidad;
			   cout << endl << "Subtotal : " << s << regcit->subtotal << endl;

			   float iva = regcit->subtotal * 0.16; // en este apartado se calcula el iva por medio del subtotal
			   regcit->iv = iva;
			   regcit->total= regcit->subtotal + iva; // se suma el subtotal + el resultado del iva y se da el total
			   cout << "Total : " << s << regcit->total << endl;

			   regcit->cloudname = regcit->nombretratamiento[0];
			   arrnomb[orden] = regcit->nombretratamiento[0];
			   orden++;
			   RegCitas(regcit);
			   cout << "\n Los datos se han guardado con exito." << endl;
			   break;
		   }
		case 2:
		{
			system("cls");	
			   Citasinfo* mostrar = new Citasinfo;
			   cout << "Ingresar el N" <<a <<"mero de cita a editar : ";
			   cin >> mostrar->numord;

			   Citasinfo* editar = new Citasinfo;
			   editar = primis;
			   bool edit = false;
	           if (primis != NULL)
	           {
		          while (editar != NULL && edit != true)
		          {
			          if (editar->numord ==mostrar->numord)
			          {
					      			   char digitos[100];
			              string espacio;
			               cout << "\nN" << a << "mero de Cita : " << editar->numord << endl; 
			               cout << endl << "Digitar el codigo del producto : ";
			               cin >> digitos;

			              if (isnumeric(digitos))
			              {
				            editar->codigoprodu = atoi(digitos); 
				               if (editar->codigoprodu >= 100000 || editar->codigoprodu < 10000) 
				               {
					            cout << "\nSolo se permiten 5 digitos" << endl;
					             break;
				               }
			              }
			             else
			             {
				            cout << "\nIngresar solo N" << a << "meros.\n \n";
				             break;
			             }
			   
		        	       cout << endl;
		    	           printf("Nombre del paciente : ");
                           cin.ignore();
	     		           cin.getline(editar->nombrepaciente, 40, '\n');
 
	    		           cout << endl << "Digitar Hora del tratamiento (24 horas) : ";
	    		           cin >> editar->horas;
	    		           gotoxy(45, 8); cout << ": "; 
	    		           cin >> editar->minutos;
	    		          if (editar->horas >= 24 || editar->minutos >= 60)  
			              {
				             cout << "\nEscribir una hora valida" << endl;
				               break;
			              }
			              cout << endl;
	     		          printf("Nombre del tratamiento : ");
	    		          cin.ignore();
	    		          cin.getline(editar->nombretratamiento, 25, '\n');

		    	         cout << endl;
			             printf("Descripcion : ");
			             cin.ignore();
			             cin.getline(editar->descripcion, 400, '\n');

			             cout << endl << "Cantidad a vender : ";
			             cin >> editar->cantidad;

			             cout << endl << "Precio unitario : " << s;
			             cin >> editar->precio;

			             editar->subtotal = editar->precio * editar->cantidad;
			             cout << endl << "Subtotal : " << s << editar->subtotal << endl;

			             float iva = editar->subtotal * 0.16; 
			             editar->iv = iva;
			             editar->total= editar->subtotal + iva; 
			             cout << "Total : " << s << editar->total << endl;

			             editar->cloudname = editar->nombretratamiento[0];
			             arrnomb[editar->numord] = editar->nombretratamiento[0];

			             cout << "\n Los datos se han guardado con exito." << endl;
				         edit = true; 
			          }
			         editar = editar->sigi;
		          }
		         if (edit == false)
		         {
					 cout << "No se ha encontrado la cita ingresada" << endl;
			        break;
		         }
	           }
	           else
	           {
				   cout << "Aun no se ha registrado una cita" << endl;
		         break;
               }
	
			
			break;
		}
		case 3:
		{
			    system("cls");
			    Citasinfo* aElim = new Citasinfo;
			    cout << "Ingresar el N" <<a <<"mero de cita a eliminar : ";
			    cin >> aElim->numord;
		        Citasinfo* actual = new Citasinfo;
		        actual = primis;
	          	Citasinfo* anterior = new Citasinfo;
		        anterior = NULL;
		        bool encontrado = false;
		       if (primis != NULL)
		       {
			      while (actual != NULL && encontrado != true)
			      {
		              if (actual->numord == aElim->numord)
				      {
					      if (actual == primis)
					      {
							  primis = primis->sigi;
						    anterior = primis;
					      }
					     else if (actual == ultim)
					     {
						    anterior->sigi = NULL;
						    ultim = anterior;
					     }
					    else
					    {
						   anterior->sigi = actual->sigi;
						   actual->sigi->ante = anterior;
					    }
					      cout << "Se ha eliminado los datos correctamente" << endl;
					      encontrado = true;

					//break;
				      }
				anterior = actual;
				actual = actual->sigi;
			      }
			         if (encontrado == false)
			         {
						 cout << "No se ha encontrado la orden a eliminar" << endl;
				         break;
			         }
		       }
		       else
		       { 
		          cout << "Aun no se ha ingresado una orden" << endl;
			      break;
		       }
			
			break;
		}
		case 4:
		{		
			system("cls");
			Citasinfo* actual = new Citasinfo;
			actual = primis;
			bool encontrado = false;

			  
			while (actual != NULL && encontrado != true)
		    {
				cout << "\nN" << a << "mero de Cita : " << actual->numord << endl;
			    cout << endl << "Codigo del Producto : " << actual->codigoprodu;
				cout << endl << "Nombre del paciente : " << actual->nombrepaciente;
				cout << endl << "Hora del tratamiento (24 horas) : " << actual->horas << " : " << actual->minutos;
				cout << endl << "Nombre del tratamiento : " << actual->nombretratamiento;
				cout << endl << "Descripci" << o << "n : " << actual->descripcion;
				cout << endl << "Cantidad a vender : " << actual->cantidad;
				cout << endl << "Precio unitario : " << s << actual->precio;
				cout << endl << "Subtotal : " << s << actual->subtotal;
				cout << endl << "IVA : " << s << actual->iv;
				cout << endl << "Total : " << s << actual->total << endl <<endl;

				actual = actual->sigi;
				if (actual== NULL) 
				{
					encontrado = true;
				}
			}
			if (encontrado == false)
			{
				cout << "\nNo se ha ingresado una cita" << endl;
				break;
			}
		    
			break;
		}
		case 5:
		{
			system("cls");
			quickSort(arrnomb, 0, orden - 1);
			for (int b = 0; b < orden; b++)
			{
				arrnomb[b];
				char nmb = arrnomb[b];
				Citasinfo* nuevo = new Citasinfo;
				nuevo = primis;
				bool encontrado = false;

				if (primis != NULL)
				{
					while (nuevo != NULL && encontrado != true)
					{
						if (nuevo->cloudname == nmb)
						{
							cout << "\nN" << a << "mero de Cita : " << nuevo->numord << endl;
							cout << endl << "Codigo del Producto : " << nuevo->codigoprodu;
							cout << endl << "Nombre del paciente : " << nuevo->nombrepaciente;
							cout << endl << "Hora del tratamiento (24 horas) : " << nuevo->horas << " : " << nuevo->minutos;
							cout << endl << "Nombre del tratamiento : " << nuevo->nombretratamiento;
							cout << endl << "Descripci" << o << "n : " << nuevo->descripcion;
							cout << endl << "Cantidad a vender : " << nuevo->cantidad;
							cout << endl << "Precio unitario : " << s << nuevo->precio;
							cout << endl << "Subtotal : " << s << nuevo->subtotal;
							cout << endl << "IVA : " << s << nuevo->iv;
							cout << endl << "Total : " << s << nuevo->total << endl << endl;
							encontrado = true;
						}
						nuevo = nuevo->sigi;
					}
					if (encontrado == false)
					{
						cout << "El nombre no existe" << endl;
						break;
					}
				}
				else
				{
					cout << "Aun no se ha registrado una cita" << endl;
					break;
				}

			}

			break;
		}
		case 6:
		   {
			//aqui debe guardar el txt
			Citasinfo* actual = new Citasinfo;
			actual = primis;
			bool encontrado = false;

			archivo.open("Citas.txt", ios::out);
			while (actual != NULL && encontrado != true)
			{
				archivo << "\nNumero de Cita : " << actual->numord << endl;
				archivo << endl << "Codigo del Producto : " << actual->codigoprodu;
				archivo << endl << "Nombre del paciente : " << actual->nombrepaciente;
				archivo << endl << "Hora del tratamiento (24 horas) : " << actual->horas << " : " << actual->minutos;
				archivo << endl << "Nombre del tratamiento : " << actual->nombretratamiento;
				archivo << endl << "Descripcion : " << actual->descripcion;
				archivo << endl << "Cantidad a vender : " << actual->cantidad;
				archivo << endl << "Precio unitario : " << s << actual->precio;
				archivo << endl << "Subtotal : " << s << actual->subtotal;
				archivo << endl << "IVA : " << s << actual->iv;
				archivo << endl << "Total : " << s << actual->total << endl << endl;

				actual = actual->sigi;
				if (actual == NULL)
				{
					encontrado = true;
				}
			}
			if (encontrado == false)
			{
				cout << "\nNo se ha ingresado una cita" << endl;
				break;
			}
			archivo.close();

			  return 0;
		   }
			
		}
		system("pause");
		system("cls");
	} while (opcion != 6);
	return 0;
}

