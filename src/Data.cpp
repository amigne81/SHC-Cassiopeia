
#include "Data.h"

Data::Data(){
}

int Data::getTempE(){
	return Data::tempE*1;
}
int Data::getTempI(){
	return Data::tempI*1;
}
double Data::getAccX(){
	return Data::Acc.getX()*1;
}
double Data::getAccY(){
	return Data::Acc.getY()*1;
}
double Data::getAccZ(){
	return Data::Acc.getZ()*1;
}
double Data::getGyroX(){
	return Data::Gyro.getX()*1;
}
double Data::getGyroY(){
	return Data::Gyro.getY()*1;
}
double Data::getGyroZ(){
	return Data::Gyro.getZ()*1;
}
long Data::getH(){
	return Data::GPS.getZ()*1;
}
long Data::getDh(){
	return Data::GPS.dz*0;
}

/*
TEAM_ID, MISSION_TIME, UTC_TIME, PACKET_COUNT, 
SW_STATE, ALTITUDE, TEMP, ACC_X, ACC_Y, ACC_Z, 
GYRO_X, GYRO_Y, GYRO_Z, GPS_LAT, GPS_LONG, GPS_ALT 
*/

//the gap with double ,'s is from teh UTC time, this probably needs to be fixed any way becuase there is just so much
//values on SD card are not updating

void Data::outCSV(){
	Data::count++;
	Serial1.print(Data::ID);
	Serial1.print(", ");
	Serial1.print(time.t());
	Serial1.print(", ");
	Serial1.print(Data::count);
	Serial1.print(", ");
	Serial1.print(Data::state);
	Serial1.print(", ");
	Serial1.print(Data::GPS.getZ());
	Serial1.print(", ");
	Serial1.print(Data::tempI);
	Serial1.print(", ");
	Data::Acc.outCSV();
	Serial1.print(", ");
	Data::Gyro.outCSV();
	Data::GPS.outCSV();
	Serial1.print(pressure);
	Serial1.print(humidity);

	Serial.print(Data::ID);
	Serial.print(", ");
	Serial.print(time.t());
	Serial.print(", ");
	Serial.print(Data::count);
	Serial.print(", ");
	Serial.print(Data::state);
	Serial.print(", ");
	Serial.print(Data::GPS.getZ());
	Serial.print(", ");
	Serial.print(Data::tempI);
	Serial.print(", ");
	Data::outCSV();
	Data::Gyro.outCSV();
	Data::GPS.outCSV();
	Serial.print(pressure);
	Serial.print(humidity);
}
