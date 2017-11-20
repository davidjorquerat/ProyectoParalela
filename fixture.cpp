#include <iostream>
#include <stdlib.h>
#include <math.h>
//#include <mpi.h>

using namespace std;

double distancia_long_lat(float lat1, float long1, float lat2, float long2)//los calculos son en km
{
	float radio_tierra = 6378.7;

	return radio_tierra*acos(((sin(lat1))*(sin(lat2)))+(((cos(lat1))*(cos(lat2))*(cos(long2 - long1)))));
}

int main(int argc, char *argv[])
{

}