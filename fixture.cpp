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

string* nombre=NULL;//nombre del equipo
string* estadio=NULL;//nombre del estadio
punto* puntos=NULL;// longitud y latitud del estadio
double** distancias=NULL;//distancia entre estadios

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

void llena_matriz_dis(punto p[])
{
  for(int i=0; i<numero_estadios; i++)
  {
    for(int j=0; j<numero_estadios; j++)
    {
      distancias[i][j] = distancia_long_lat(p[i].latitud, p[i].longitud, p[j].latitud, p[j].longitud);
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
              nombre = (string*)realloc(nombre,sizeof(string)*(cont+1));//asignacion de memoria al nombre (vector de largo posiciones
              estadio = (string*)realloc(estadio,sizeof(string)*(cont+1));
              puntos = (punto*)realloc(puntos,sizeof(punto)*(cont+1));
              // Fin asignacion
              int cont2=0;
              fs.getline(palabra,80,'\n');
              //cout<<"Dato sin separar: "<<string<<endl;
              ptr = strtok(palabra,";");
              while(ptr != NULL)
                   {
                    if (cont2==0){
                    //COLUMNA 1 - NOMBRE EQUIPO
                    nombre[cont] = ptr;

                      }
                    if (cont2==1){
                    //COLUMNA 2 - NOMBRE ESTADIO
                    estadio[cont] = ptr;

                     }
                    if (cont2==2){
                    //COLUMNA 3 -  COORDENADA X
                    puntos[cont].latitud = atof(ptr);

                     }
                     if (cont2==3){
                    //COLUMNA 4 - COORDENADA Y
                    puntos[cont].longitud = atof(ptr);

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

  for(int i=0; i<4; i++)
  {
    cout<<nombre[i]<<";"<<estadio[i]<<";"<<puntos[i].latitud<<";"<<puntos[i].longitud<<endl;
  }

  llena_matriz_dis(puntos);

  cout<<"La distancia entre: "<<estadio[0]<<" y "<<estadio[1]<<" es: "<<distancias[0][1]<<" KM"<<endl;
	return 0;

}