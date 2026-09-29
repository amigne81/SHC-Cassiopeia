
#include "Data.h"
#include "store3D.h"


int Data::getTemp(){
	return Data::temp*1;
}
int Data::getAccX(){
	return Data::Acc.getX()*1;
}
int Data::getAccY(){
	return Data::Acc.getY()*1;
}
int Data::getAccZ(){
	return Data::Acc.getZ()*1;
}
int Data::getGyroX(){
	return Data::Gyro.getX()*1;
}
int Data::getGyroY(){
	return Data::Gyro.getY()*1;
}
int Data::getGyroZ(){
	return Data::Gyro.getZ()*1;
}
int Data::getH(){
	return Data::GPS.getZ()*1;
}
int Data::getDh(){
	return Data::GPS.dz*1;
}


