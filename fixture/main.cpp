#include "fixture.h"
#include <QApplication>
#include <math.h>
#include <fstream>
#include <QLabel>
#include <string>
#include <QDebug>
#include <QString>


using namespace std;
typedef char cadena[80];
char *ptr;
int cont=0;

//int largo = 60;

typedef struct
{
  float latitud;
  float longitud;
}punto;

int numero_estadios;
double distancias[16][16];//distancia entre estadio

QString nombre[16];//nombre del equipo
QString estadio[16];//nombre del estadio
punto puntos[16];// longitud y latitud del estadio

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

void llena_matriz_dis()
{
  for(int i=0; i<numero_estadios-1; i++)
  {
    for(int j=0; j<numero_estadios-1; j++)
    {
      distancias[i][j] = distancia_long_lat(puntos[i].latitud, puntos[i].longitud, puntos[j].latitud, puntos[j].longitud);
    }
  }
}

int leer_equipo(cadena archivo){
  ifstream fs;
  int cont=0;
        fs.open(archivo);
        if (!fs){

        qDebug() << "hOLA2" << archivo;
         }
        else {

            cadena palabra;


            while(!fs.eof())
          {


              int cont2=0;
              fs.getline(palabra,80,'\n');

              ptr = strtok(palabra,";");
              while(ptr != NULL)
                   {

                    if (cont2==0){
                    nombre[cont] = ptr;
                      }

                    if (cont2==1){
                    estadio[cont] = ptr;
                     }

                    if (cont2==2){
                    puntos[cont].latitud = atof(ptr);
                     }

                     if (cont2==3){
                    puntos[cont].longitud = atof(ptr);
                     }

                    ptr = strtok(NULL, ";");
                    cont2++;
                   }

                   cont++;
        }



 }
        return cont;
}



int prueba(int numero){
    numero=numero+1;
    return numero;
}






int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    fixture w;



    //QLabel hw("Hola mundo");
    //hw.show();




   //int prueba1 = prueba(2);

   numero_estadios = leer_equipo(argv[1]);

   QString act=nombre[5];



   qDebug() << "hOLA" << puntos[2].latitud;
   llena_matriz_dis();

   qDebug() <<"La distancia entre: "<<estadio[0]<<" y "<<estadio[1]<<" es: "<<distancias[0][1]<<" KM";



    //w.show();

    return a.exec();
}
