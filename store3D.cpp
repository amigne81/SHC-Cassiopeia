
#include "store3D.h"
#include "strings"

store3D::int setX(int a){
	dx = a-x;
	x = a;
}

store3D::int setY(int a){
	dy = a-y;
	y = a;
}

store3D::int setZ(int a){
	dz = a-z;
	z = a;
}

store3D:: string outCSV(){
	return x+", "+y+", "+z+", ";
}

store3D:: string outdCSV(){
	return dx+", "+dy+", "+dz+", ";
}