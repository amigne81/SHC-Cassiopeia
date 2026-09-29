
#include "store3D.h"
#include "string"

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
	return store3D::x;
}

int store3D::getY(){
	return store3D::y;
}

int store3D::getZ(){
	return store3D::z;
}

std::string store3D::outCSV(){
	return std::to_string(store3D::x) + ", " + std::to_string(store3D::y) + ", " + std::to_string(store3D::z) + ", ";
}

std::string store3D::outDCSV(){
	return std::to_string(store3D::dx) + ", " + std::to_string(store3D::dy) + ", " + std::to_string(store3D::dz) + ", ";
}