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

std::string store3D::outCSV(){
	return std::to_string(x) + ", " + std::to_string(y) +", " + std::to_string(z)+ ", ";
}

std::string store3D::outdCSV(){
	return std::to_string(store3D::dx) + ", " + std::to_string(store3D::dy) + ", " + std::to_string(store3D::dz) +", ";
} 
