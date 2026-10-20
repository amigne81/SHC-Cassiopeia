#include "store3Ddouble.h"


void store3Ddouble::setX(double a){
	store3Ddouble::dx = a-x;
	x = a;
}

void store3Ddouble::setY(double a){
	store3Ddouble::dy = a-y;
	y = a;
}

void store3Ddouble::setZ(double a){
	store3Ddouble::dz = a-z;
	z = a;
}

double store3Ddouble::getX(){
	return x;
}

double store3Ddouble::getY(){
	return y;
}

double store3Ddouble::getZ(){
	return z;
}

String store3Ddouble::outCSV(){
	return String(x) + ", " + String(y) + ", " + String(z)+ ", ";
}

