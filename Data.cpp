
#include "Data.h"
#include "store3D.h"


Data::int getTemp(){
	return temp*1;
}
Data::int getAccX(){
	return Acc.getX()*1;
}
Data::int getAccY(){
	return Acc.getY()*1;
}
Data::int getAccZ(){
	return Acc.getZ()*1;
}
Data::int getGyroX(){
	return Gyro.getX()*1;
}
Data::int getGyroY(){
	return Gyro.getY()*1;
}
Data::int getGyroZ(){
	return Gyro.getZ()*1;
}
Data::int getH(){
	return GPS.getZ()*1
}
Data::int getDh(){
	return dh*1;
}


