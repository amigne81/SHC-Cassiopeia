#include "store3D.h"

void store3D::setX(int a){
	store3D::dx = a-x;
	x = a;
}

void store3D::setY(int a){
	store3D::dy = a-y;
	y = a;
}

void store3D::setZ(int a){
	store3D::dz = a-z;
	z = a;
}

int store3D::getX(){
	return x;
}

int store3D::getY(){
	return y;
}

int store3D::getZ(){
	return z;
}

String store3D::outCSV(){
	return String(x) + ", " + String(y) + ", " + String(z)+ ", ";
}

