
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

// outputs all required
std::string Data::outCSV(){
	Data::count++;
	return std::to_string(Data::ID) + ", " + std::to_string(time.t()) + ", " + std::to_string(time.tUTC()) + ", " +
	std::to_string(Data::GPS.getZ()) + "," + std::to_string(Data::temp) + "," + Data::Acc.outCSV() + 
	std::to_string(t) +std::to_string(Data::state)+ ", "+ std::to_string(Data::count) + ", " + 
	std::to_string(Data::temp) + ", " + Data::Gyro.outCSV() + Data::GPS.outCSV();
}
