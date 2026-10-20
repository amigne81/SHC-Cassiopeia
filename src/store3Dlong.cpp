#include "store3Dlong.h"

void store3Dlong::setX(long a){
	store3Dlong::dx = a-x;
	x = a;
}

void store3Dlong::setY(long a){
	store3Dlong::dy = a-y;
	y = a;
}

void store3Dlong::setZ(long a){
	store3Dlong::dz = a-z;
	z = a;
}

long store3Dlong::getX(){
	return x;
}

long store3Dlong::getY(){
	return y;
}

long store3Dlong::getZ(){
	return z;
}

String store3Dlong::outCSV(){
	return String(x) + ", " + String(y) + ", " + String(z)+ ", ";
}

