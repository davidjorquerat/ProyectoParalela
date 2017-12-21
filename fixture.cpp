#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <fstream>
#include <cstring>
#include <vector>
#include <xlsxwriter.h>
//#include <mpi.h>
#define INFINITO 99999

using namespace std;
typedef char cadena[80];
char *ptr;

//int largo = 60;

int hi;
int jota;

double distancias_copia[16][16];
double distancias_bloqueo[16][16];
//vector<int> ubicacion;
int ubicacion[16];
//vector<int> ubicacion2;
//int local[16][16];


struct punto
{
  float latitud;
  float longitud;
};

struct equipo{
  string nombre;
  string estadio;
  punto coordenada;
};

struct partido
{
  string local;
  string visita;
  int fecha;
};

struct indices{
  int i,j;
};

int numero_estadios;

vector<equipo> equipos;

vector<partido> partidos;

bool habilitado[16];
//distancia dinamica

double **distancias;

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

void llena_matriz_dis() //FUNCION QUE LLENA 2 MATRICES IGUALES CON LAS DISTANCIAS
{
  for(int i=0; i<numero_estadios; i++)
  {
    for(int j=0; j<numero_estadios; j++)
    {
      if(i==j){
        distancias[i][j] = INFINITO;
        distancias_copia[i][j] = INFINITO;

      }

      else{
      distancias[i][j] = distancia_long_lat(equipos[i].coordenada.latitud, equipos[i].coordenada.longitud, equipos[j].coordenada.latitud, equipos[j].coordenada.longitud);
      distancias_copia[i][j] = distancia_long_lat(equipos[i].coordenada.latitud, equipos[i].coordenada.longitud, equipos[j].coordenada.latitud, equipos[j].coordenada.longitud);
       }


    }
  }
}



int find(vector<int> vec, int t) //FUNCION QUE BUSCA DENTRO DE UN VECTOR UN NUMERO, SI ESTA RETORNA LA POSICION, SI NO ESTA RETORNA -1
{
  int i = 0;
  while (i < vec.size())
  {
    if (vec[i] == t)
      return i;
      else
        i++;

  }
  return -1;
}

/*
void llena_matriz_dis2(vector<int> vec) // FUNCION QUE COPIA FILAS DESDE MATRIZ ORGINAL SIN CAMBIAR LA DIAGONAL NI LOS -1
{
  int i=0;
  for(int j=0; j<numero_estadios; j++)
  {
    for(int i=0; i<numero_estadios; i++)
    {
      if(find(ubicacion,j)%2!=0)// SI la POSICION EL NUMERO(J) CONTENIDO EN EL VECTOR ES IMPAR(VISITA) ENTRA
      {
    	  if(i==j){
      		distancias_copia[i][j] = INFINITO;
        }
  	    if(distancias_copia[i][j]!=INFINITO)
        {
          distancias_copia[i][j] = distancias[i][ubicacion[find(ubicacion,j)-1]];
        }
      }
      else if(distancias_copia[i][j]!=INFINITO) //SI ES PAR ENTRA
      {
        distancias_copia[i][j] = distancias[i][ubicacion[find(ubicacion,j)]];
      }
	   }
   }
}*/

void llena_matriz_dis2() // FUNCION QUE COPIA FILAS DESDE MATRIZ ORGINAL SIN CAMBIAR LA DIAGONAL NI LOS -1
{
  int i=0;
  for(int i=0; i<numero_estadios; i++)
  {
    for(int j=0; j<numero_estadios; j++)
    {
      if(i!=ubicacion[i])// SI la POSICION EL NUMERO(J) CONTENIDO EN EL VECTOR ES IMPAR(VISITA) ENTRA
      {
        if(i==j){
          distancias_copia[i][j] = INFINITO;
        }
        if(distancias_copia[i][j]!=INFINITO)
        {
          distancias_copia[i][j] = distancias[ubicacion[i]][j];
        }
      }
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

bool crearExcel(cadena argumento){
  cout<<"Creando excel de prueba"<<endl;
  string ruta;
  //crea ruta para guardar el archivo
  if (argumento!=NULL)
    ruta = strcat(argumento,"/prueba.xlsx");
  else
    ruta = "prueba.xlsx";

  lxw_workbook  *workbook  = workbook_new(ruta.c_str()); //Se crea el fichero excel
  lxw_worksheet *worksheet = workbook_add_worksheet(workbook, NULL); //Se agrega una hoja al fichero
  //formatos que se aplicaran en la hoja
  lxw_format *bold = workbook_add_format(workbook);
  lxw_format *bold_local = workbook_add_format(workbook);
  lxw_format *bold_fecha = workbook_add_format(workbook);
  lxw_format *local = workbook_add_format(workbook);
  lxw_format *fecha = workbook_add_format(workbook);
  format_set_bold(bold);
  format_set_bold(bold_local);
  format_set_bold(bold_fecha);
  format_set_align(local,LXW_ALIGN_RIGHT);
  format_set_align(fecha,LXW_ALIGN_CENTER);
  format_set_align(bold_local,LXW_ALIGN_RIGHT);
  format_set_align(bold_fecha,LXW_ALIGN_CENTER);
  int cont=1;
  //formato de columnas
  worksheet_set_column(worksheet, 0, 0, 30, local);
  worksheet_set_column(worksheet, 1, 1, 20, fecha);
  worksheet_set_column(worksheet, 2, 2, 30, NULL);
  //nombres de columnas
  worksheet_write_string(worksheet, 0, 0, "LOCAL", bold_local);
  worksheet_write_string(worksheet, 0, 1, "FECHA", bold_fecha);
  worksheet_write_string(worksheet, 0, 2, "VISITA", bold);

  for(int i=0; i<partidos.size(); i++)
  {
      char cadena[4];

      worksheet_write_string(worksheet, cont, 0, partidos[i].local.c_str(), NULL);

      sprintf(cadena,"%d",partidos[i].fecha);//entero a string
      worksheet_write_string(worksheet, cont, 1, cadena, NULL);

      worksheet_write_string(worksheet, cont, 2, partidos[i].visita.c_str(), NULL);
      cont++;
  }
  cout<<"Excel creado."<<endl;
  return workbook_close(workbook);
}
void mostrarFecha(int i,int j){
  cout<<equipos[i].nombre<<" V/S "<<equipos[j].nombre<<endl;
}

/*
indices minimoPorFila(){
  int menor=INFINITO,cont=0,menor_cont=INFINITO,indice_menor,menores[16];
  indices indice;
  indice.i=-1;
  indice.j=-1;
  for(int i=0;i<numero_estadios;i++) menores[i]=0;
  for(int i=0;i<numero_estadios;i++){
    for(int j=0;j<numero_estadios;j++){
      if(distancias_copia[i][j]<=menor) menores[i]++;
    }
  }
  for(int i=0;i<numero_estadios;i++){
    for(int j=0;j<numero_estadios;j++){
      if(habilitado[i] && habilitado[j] && menores[i]<=menor_cont){
        menor_cont=menores[i];
        indice_menor=i;
      }
    }
  }
  for(int i=0;i<numero_estadios;i++){
    if(distancias_copia[indice_menor][i]<=menor){
      menor=distancias_copia[indice_menor][i];
      indice.i=indice_menor;
      indice.j=i;
    }
  }
  distancias_copia[indice.i][indice.j]=INFINITO;
  habilitado[indice.i]=false;
  habilitado[indice.j]=false;
  // for(int i=0;i<numero_estadios-1;i++){
  //   for(int j=1;j<numero_estadios;j++){
  //     if(habilitado[i] && habilitado[j]){
  //       if(distancias_copia[i][j]<menor){
  //         cont++;
  //         menor=distancias_copia[i][j];
  //         indice.i=i;
  //         indice.j=j;
  //       }
  //     }
  //   }
  //   if(menor<INFINITO){
  //     habilitado[indice.i]=false;
  //     habilitado[indice.j]=false;
  //     distancias_copia[indice.i][indice.j]=INFINITO;
  //     break;
  //   }
  // }
  return indice;
}*/

indices minimoPorFila(){


  indices indice;

  for(int i=0;i<numero_estadios;i++)
  {
    for(int j=0;j<numero_estadios;j++)
    {
      if(habilitado[i] && habilitado[j])
      {
        if(distancias_copia[i][j]!=INFINITO)
        {
          //cout<<endl<<endl<<endl<<"***************************  ENTRE   ***************************"<<endl<<endl<<endl;
          indice.i = i;
          indice.j = j;
          //cout<<endl<<endl<<"***********   i: "<<indice.i<<"   *************"<<endl;
          //cout<<endl<<endl<<"***********   j: "<<indice.j<<"   *************"<<endl;
          distancias_copia[indice.i][indice.j]=INFINITO;
          habilitado[indice.i]=false;
          habilitado[indice.j]=false;
  
          return indice;
        }
      }
    }
  }
  
  distancias_copia[indice.i][indice.j]=INFINITO;
  habilitado[indice.i]=false;
  habilitado[indice.j]=false;
  
  return indice;
}

void habilitarEquipos(){
  for(int i=0;i<numero_estadios;i++) habilitado[i]=true;
}

indices minimoPorMatriz(){
  int menor=INFINITO;
  indices indice;
  indice.i=-1;
  indice.j=-1;
  for(int i=0;i<numero_estadios;i++){
    for(int j=0;j<numero_estadios;j++){
      if(habilitado[i] && habilitado[j]){
        //cout<<"Distancia reccorida: "<<distancias_copia[i][j]<<endl<<endl;
        if(distancias_copia[i][j]<=menor){
          menor=distancias_copia[i][j];
          indice.i=i;
          indice.j=j;
        }
      }
    }
  }
  if(indice.i != -1 && indice.j != -1)
  {
    habilitado[indice.i]=false;
    habilitado[indice.j]=false;
    distancias_copia[indice.i][indice.j]=INFINITO;
  }
  cout<<endl<<"Distancia entre equipos: "<<distancias_copia[indice.i][indice.j]<<endl;
  
  cout<<endl<<"Partido seleccionado: "<<equipos[indice.i].nombre<<"("<<indice.i+1<<") - "<<equipos[indice.j].nombre<<"("<<indice.j+1<<")"<<endl<<endl;
  return indice;
}

indices randomIndices(){
  indices indice;
  srand(time(NULL));
  indice.i=rand()%numero_estadios;
  indice.j=rand()%numero_estadios;
  while(indice.i==indice.j)
  {
    indice.j=rand()%numero_estadios;
  }
  cout<<indice.i<<" "<<indice.j<<endl;
  return indice;
}

void copiarMatriz(double original[][16], double copia[][16]){
  for(int i=0;i<numero_estadios;i++){
    for(int j=0;j<numero_estadios;j++){
      copia[i][j]=original[i][j];
    }
  }
}

void kernel()
{
  indices indice;
  for(int k=0;k<(2*(numero_estadios-1));k++){ // RECORRIDO DE CADA FECHA
    //bool bloqueado=false;
    int bloqueado = 0, deshabilita = 0;
     habilitarEquipos();
    //std::vector<int>().swap(ubicacion);
    for(int i=0; i<numero_estadios;i++)
    {
      ubicacion[i]=i;
    }
    cout<<"FECHA "<<k+1<<endl;
    copiarMatriz(distancias_copia,distancias_bloqueo);
    cout<<"MATRIZ QUE SE ANALIZA"<<endl;

    for (int j=0;j<numero_estadios;j++)
    {
      for (int i=0;i<numero_estadios;i++)
      {
        printf("| %f |",distancias_copia[j][i]);
      }
    printf("\n");
    }
    
    INICIO:
    for(int y=0;y<(numero_estadios/2);y++) // PARTIDOS POR FECHA
    {
      deshabilita++;
      if(bloqueado==1)
      {
        habilitarEquipos();
      }
      // for(int j=0; j<numero_estadios; j++)
      // {
      //   if(find(ubicacion,j)==-1)
      //   {
      //     for(int i=0; i<numero_estadios; i++){
      //       if(i!=j && distancias_copia[i][j]<=menor && find(ubicacion,i)==-1 && distancias_copia[i][j]!=INFINITO){
      //       //cout<<"entro con i y j :"<<i<<" - "<<j<<endl;
      //       menor=distancias_copia[i][j];
      //       hi = i;
      //       jota = j;
      //       }
      //     }
      //   }
      // }
        if(bloqueado == 0)
        { 
          indice=minimoPorMatriz();
        }

        else 
        {
          indice=minimoPorFila();
        }

      if(distancias[indice.i][indice.j]==INFINITO)
      {
        cout<<endl<<endl<<endl<<"FALLA BLOQUEO"<<endl<<"*********************************************************************************************"<<endl<<endl<<endl;
        copiarMatriz(distancias_bloqueo,distancias_copia);

        //indice=minimoPorFila();
        bloqueado++;
        cout<<endl<<endl<<"************************ bloqueado = "<<bloqueado<<" ****************"<<endl<<endl;
        if(deshabilita == 1)
        {
          goto INICIO;
        }
      }
      //ubicacion.push_back(indice.i);
      //ubicacion.push_back(indice.j);
      ubicacion[indice.i]=indice.j;
      distancias_copia[indice.i][indice.j]=INFINITO;
      cout<<equipos[indice.i].nombre<<" V/S "<<equipos[indice.j].nombre<<endl;
      agrega_partido(equipos[indice.i].nombre, equipos[indice.j].nombre, k+1);
    }
    cout<<"MATRIZ SIN COPIAR"<<endl;
    for (int j=0;j<numero_estadios;j++)
    {
      for (int i=0;i<numero_estadios;i++)
      {
        printf("| %f |",distancias_copia[j][i]);
      }
    printf("\n");
    }
    llena_matriz_dis2();
    cout<<"MATRIZ CON FILAS COPIADAS "<<endl;
    for (int j=0;j<numero_estadios;j++)
    {
      for (int i=0;i<numero_estadios;i++)
      {
        printf("| %f |",distancias_copia[j][i]);
      }
    printf("\n");
    }
  }
}







int main(int argc, char *argv[])
{
  switch(argc){ //Revisa la cantidad de argumentos ingresados al ejecutar el programa
    case 1:
      cout<<"No se ha indicado fichero de equipos."<<endl;
      break;
    case 2:
      cout<<"No se ha indicado ruta de salida para el fichero Excel."<<endl;
      cout<<"Se utilizara la misma ruta del programa."<<endl;
    case 3:
      {
        habilitarEquipos();
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
       
        //Calcula y guarda las distancias en la matriz de distancia
        llena_matriz_dis();



        kernel();


        randomIndices();

        crearExcel(argv[2]);

        //se libera la memoria usada por la matriz dinamica
        for(int i = 0; i < numero_estadios; i++)
        {
          delete[] distancias[i];
        }
        delete[] distancias;
      }
      break;
      default:
      cout<<"Demasiados argumentos."<<endl;
      break;
  }
  return 0;
}
