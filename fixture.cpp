#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <cstring>
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

int numero_estadios;


//dinamico

typedef struct{
  string nombre; //Nombre del equipo
  string estadio; //Nombre del estadio
  punto puntos; //Latitud y longitud del estadio
}equipo;

equipo* equipos=NULL; //Arreglo dinamico de equipos

double** distancias=NULL;//Matriz distancia entre estadios

/*
//estatico
string nombre[4];//nombre del equipo
string estadio[4];//nombre del estadio
punto puntos[4];// longitud y latitud del estadio
*/

double distancia_long_lat(float lat1, float long1, float lat2, float long2)//los calculos son en km
{
	float radio_tierra = 6378.7;
  float const pi = 3.14159265359;

  //conversion a radianes
  lat1 = lat1*(pi/180);
  lat2 = lat2*(pi/180);
  long1 = long1*(pi/180);
  long2 = long2*(pi/180);

	return radio_tierra*acos(((sin(lat1))*(sin(lat2)))+(((cos(lat1))*(cos(lat2))*(cos(long2 - long1)))));
}

void llena_matriz_dis(equipo e[])
{
  for(int i=0; i<numero_estadios; i++)
  {
    for(int j=0; j<numero_estadios; j++)
    {
      distancias[i][j] = distancia_long_lat(e[i].puntos.latitud, e[i].puntos.longitud, e[j].puntos.latitud, e[j].puntos.longitud);
    }
  }
}

int leer_equipo(cadena archivo){
  ifstream fs;
        fs.open(archivo);
        if (!fs) cout<<"El fichero no existe o no se puede leer.\n";
        else {
          long long cont=0;
            cadena palabra;

            cout<<"Leyendo el fichero de equipos..."<<endl;

            while(!fs.eof())
          {
              // Asignacion de memoria a
              equipos = (equipo*)realloc(equipos,sizeof(equipo)*(cont+1));
              // Fin asignacion
              int cont2=0;
              fs.getline(palabra,80,'\n');
              //cout<<"Dato sin separar: "<<string<<endl;
              ptr = strtok(palabra,";");
              while(ptr != NULL)
                   {
                    if (cont2==0){
                    //COLUMNA 1 - NOMBRE EQUIPO
                    equipos[cont].nombre = ptr;

                      }
                    if (cont2==1){
                    //COLUMNA 2 - NOMBRE ESTADIO
                    equipos[cont].estadio = ptr;

                     }
                    if (cont2==2){
                    //COLUMNA 3 -  COORDENADA X
                    equipos[cont].puntos.latitud = atof(ptr);

                     }
                     if (cont2==3){
                    //COLUMNA 4 - COORDENADA Y
                    equipos[cont].puntos.longitud = atof(ptr);

                     }
                    //cout <<"Dato separado:"<< ptr << endl;

                    ptr = strtok(NULL, ";");
                    cont2++;
                   }
                   cont++;
            }
            return cont;
 }
}

void mostrarEquipo(equipo e){
  cout<<e.nombre<<";"<<e.estadio<<";"<<e.puntos.latitud<<";"<<e.puntos.longitud<<endl;
}

int main(int argc, char *argv[])
{
	numero_estadios = leer_equipo(argv[1]);

	cout<<"Lineas en el fichero: "<<numero_estadios<<endl;

  // Asignacion de memoria a matriz distancias
  distancias = new double*[numero_estadios];
  for(int i=0;i<numero_estadios;i++){
    distancias[i]=new double[numero_estadios];
  }
  // Fin Asignacion
  //Muestra la lista de los equipos almacenados
  for(int i=0; i<numero_estadios; i++) mostrarEquipo(equipos[i]);
  //Calcula y guarda las distancias en la matriz de distancia
  llena_matriz_dis(equipos);

  cout<<"La distancia entre: "<<equipos[0].nombre<<" y "<<equipos[1].nombre<<" es: "<<distancias[0][1]<<" KM"<<endl;
	return 0;

}
