#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <cstring>
//#include <mpi.h>

using namespace std;
typedef char cadena[80];
char *ptr;

double distancia_long_lat(float lat1, float long1, float lat2, float long2)//los calculos son en km
{
	float radio_tierra = 6378.7;

	return radio_tierra*acos(((sin(lat1))*(sin(lat2)))+(((cos(lat1))*(cos(lat2))*(cos(long2 - long1)))));
}

int leer_equipo(cadena archivo){
  ifstream fs;
        fs.open(archivo);
        if (!fs) cout<<"El fichero no existe o no se puede leer.\n";
        else {
          long long cont=0;
            cadena string;
      
            cout<<"Leyendo el fichero de equipos..."<<endl;

            while(!fs.eof())
          {
              int cont2=0;
              fs.getline(string,80,'\n');
              cout<<"Dato sin separar: "<<string<<endl; 
              ptr = strtok(string,";");
              while(ptr != NULL)
                   {
                    if (cont2==0){
                    //COLUMNA 1 - NOMBRE EQUIPO  
                    //equipos[cont].a = ptr;
                      
                      }
                    if (cont2==1){
                    //COLUMNA 2 - NOMBRE ESTADIO
                    //equipos[cont].b = ptr;
                      
                     }
                    if (cont2==2){
                    //COLUMNA 3 -  COORDENADA X
                    //equipos[cont].c = ptr;
                      
                     }
                     if (cont2==3){
                    //COLUMNA 4 - COORDENADA Y
                    //equipos[cont].d = ptr;
                      
                     }
                    cont2++;
                    cout <<"Dato separado:"<< ptr << endl;
                    
                    ptr = strtok(NULL, ";");
                   }
                   cont++;
            }

            int lineas= cont;
            
            
            return lineas;


 }
}



int main(int argc, char *argv[])
{
	int valor=leer_equipo(argv[1]);
	cout<<"Lineas en el fichero: "<<valor<<endl; 
	return 0;

}