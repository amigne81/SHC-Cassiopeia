
#include "Data.h"



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

/*
TEAM_ID, MISSION_TIME, UTC_TIME, PACKET_COUNT, 
SW_STATE, ALTITUDE, TEMP, ACC_X, ACC_Y, ACC_Z, 
GYRO_X, GYRO_Y, GYRO_Z, GPS_LAT, GPS_LONG, GPS_ALT 
*/

String Data::outCSV(){
	Data::count++;
	return String(Data::ID) + ", " + String(time.t()) + ", " + String(time.tUTC()) + ", " +
	String(Data::count) + ", " + String(Data::GPS.getZ()) + "," + String(Data::temp) + "," +
	String(Data::state)+ ", " + String(Data::temp) + Data::Acc.outCSV() + ", " + 
	Data::Gyro.outCSV() + Data::GPS.outCSV();
}
