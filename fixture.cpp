#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <xlsxwriter.h>
//#include <mpi.h>

using namespace std;
typedef char cadena[80];
char *ptr;

//int largo = 60;

typedef struct
{
  float latitud;
  float longitud;
}punto;

typedef struct{
  string nombre;
  string estadio;
  punto coordenada;
}equipo;

//estructura que almacena los partidos que se mostraran en la planilla excel
typedef struct
{
  string local;
  string visita;
  int fecha;
}partido;

int numero_estadios;

//vector de estructura de equipos
vector<equipo> equipos;

//vector de estructura de partidos
vector<partido> partidos;

//distancia dinamica

double **distancias;

//distancia estatica
//double distancias[16][16];//distancia entre estadios

//string* nombre=NULL;//nombre del equipo
//string* estadio=NULL;//nombre del estadio
//punto* puntos=NULL;// longitud y latitud del estadio


//estatico
/*
string nombre[16];//nombre del equipo
string estadio[16];//nombre del estadio
punto puntos[16];// longitud y latitud del estadio
*/

//funcion para agregar partidos que se mostraran en la planilla excel
void agrega_partido(string eq_local, string eq_visita, int fecha_partido)
{
  partido p;

  p.local = eq_local;
  p.visita = eq_visita;
  p.fecha = fecha_partido;

  partidos.push_back(p);
}

double en_radianes(double dato)
{
  float const pi = 3.14159265359;
  return dato = dato*(pi/180);
}


double distancia_long_lat(float lat1, float long1, float lat2, float long2)//los calculos son en km
{
  float radio_tierra = 6378.7;


  //conversion a radianes
  lat1 = en_radianes(lat1);
  lat2 = en_radianes(lat2);
  long1 = en_radianes(long1);
  long2 = en_radianes(long2);

  return radio_tierra*acos(((sin(lat1))*(sin(lat2)))+(((cos(lat1))*(cos(lat2))*(cos(long2 - long1)))));
}

void llena_matriz_dis()
{
  for(int i=0; i<numero_estadios; i++)
  {
    for(int j=0; j<numero_estadios; j++)
    {
      distancias[i][j] = distancia_long_lat(equipos[i].coordenada.latitud, equipos[i].coordenada.longitud, equipos[j].coordenada.latitud, equipos[j].coordenada.longitud);
    }
  }
}

int leer_equipo(cadena archivo){
  ifstream fs;
        fs.open(archivo);
        if (!fs) cout<<"El fichero no existe o no se puede leer.\n";
        else {
            int cont=0;
            cadena palabra;

            cout<<"Leyendo el fichero de equipos..."<<endl;

            while(!fs.eof())
          {

              int cont2=0;
              fs.getline(palabra,80,'\n');
              equipo aux;
              //cout<<"Dato sin separar: "<<palabra<<endl;
              ptr = strtok(palabra,";");
              while(ptr != NULL)
                   {
                    if (cont2==0){
                    //COLUMNA 1 - NOMBRE EQUIPO
                    aux.nombre = ptr;
                    //cout <<"Dato separado:"<< ptr << endl;

                      }
                    if (cont2==1){
                    //COLUMNA 2 - NOMBRE ESTADIO
                    aux.estadio = ptr;
                    //cout <<"Dato separado:"<< ptr << endl;

                     }
                    if (cont2==2){
                    //COLUMNA 3 -  COORDENADA X
                    aux.coordenada.latitud = atof(ptr);
                    //cout <<"Dato separado:"<< ptr << endl;

                     }
                     if (cont2==3){
                    //COLUMNA 4 - COORDENADA Y
                    aux.coordenada.longitud = atof(ptr);
                    //cout <<"Dato separado:"<< ptr << endl;
                    equipos.insert(equipos.begin()+cont,aux);
                    cont++;
                    }
                    ptr = strtok(NULL, ";");
                    cont2++;
                   }

            }
            return cont;
 }
}

void mostrarDistancia(int i, int j){
  cout<<"La distancia entre "<<equipos[i].nombre<<" y "<<equipos[j].nombre<<" es: "<<distancias[i][j]<<endl;
}

void mostrarEquipo(equipo e){
  cout<<e.nombre<<";"<<e.estadio<<";"<<e.coordenada.latitud<<";"<<e.coordenada.longitud<<endl;
}

bool crearExcel(){
  cout<<"Creando excel de prueba"<<endl;
  lxw_workbook  *workbook  = workbook_new("prueba.xlsx");
  lxw_worksheet *worksheet = workbook_add_worksheet(workbook, NULL);
  lxw_format *format = workbook_add_format(workbook);
  format_set_bold(format);
  int cont=0;
  for(int i=0; i<partidos.size(); i++)
  {
      char cadena[30];
      sprintf(cadena,"%s",partidos[i].local);
      worksheet_write_string(worksheet, cont, 0, cadena, NULL);

      sprintf(cadena,"%d",partidos[i].fecha);
      worksheet_write_string(worksheet, cont, 1, cadena, format);

      sprintf(cadena,"%s",partidos[i].visita);
      worksheet_write_string(worksheet, cont, 2, cadena, NULL);
      cont++;
  }
  cout<<"Excel creado."<<endl;
  return workbook_close(workbook);
}

int main(int argc, char *argv[])
{
  numero_estadios = leer_equipo(argv[1]);

  //asignacion de memoria a la matriz dinamica distancias
  distancias = new double*[numero_estadios];
  for(int i=0; i<numero_estadios; i++)
  {
    distancias[i] = new double[numero_estadios];
  }
  //fin de asignacion de memoria

  cout<<"Lineas en el fichero: "<<numero_estadios<<endl;

  //Muestra la lista de los equipos almacenados
  for(int i=0; i<numero_estadios; i++)
  {
    mostrarEquipo(equipos[i]);
  }

  //agrega partidos de prueba

  for(int i=0;i<numero_estadios-1;i++)
  {
    agrega_partido(equipos[i].nombre, equipos[i+1].nombre, i);
  }

  cout<<partidos[0].local<<" juega con "<<partidos[0].visita<<" en la fecha "<<partidos[0].fecha<<endl;

  //Calcula y guarda las distancias en la matriz de distancia
  llena_matriz_dis();

  for(int i=0;i<16;i++)
    mostrarDistancia(15,i);

  crearExcel();

  //se libera la memoria usada por la matriz dinamica
  for(int i = 0; i < numero_estadios; i++) 
  {
    delete[] distancias[i];
  }
  delete[] distancias;

  return 0;

}
