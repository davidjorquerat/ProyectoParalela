# ProyectoParalela
proyecto final de paralela


1- Instalar la libreria "libxlsxwriter"(https://libxlsxwriter.github.io/getting_started.html)

2-Ejecutar estos comandos en la consola:
	LD_LIBRARY_PATH=/usr/local/lib
	export LD_LIBRARY_PATH

3-Para compilar usar "g++ fixture.cpp -o fixt -lxlsxwriter"

4- Ejecución por parámetros: "./fixt Equipos.csv Ruta_destino" (Si no especifica ruta de destino se guarda donde esta el ejecutable)
 
   Ejecución por QT: Compilar y generar el ejecutable, después colocar el archivo fixt en la ubicación del archivo ejecutable QT. 
