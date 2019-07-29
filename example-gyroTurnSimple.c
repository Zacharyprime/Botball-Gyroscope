#include <kipr/botball.h>
double bias; //Make bias a global variable so that all functions can see it

int findBias(){
	//Stop the motors to make bot stand still
	ao();
	msleep(300);
	
	//Find the average noise
	int i = 0;
	double avg = 0;
	while(i < 50){
		avg += gyro_z();
		msleep(1);
		i++;
	}
	bias = avg / 50.0
	return bias;
}

int readGyro(){
	return gyro_z() - bias;
}

int main(){
	//(369 KIPR Units = 90 degree)
	int targetAngle = 369;
	findBias();
	int timeInterval = 10;
	
	while( abs(currentAngle) < targetAngle) {
		motor(0,30);
		motor(1,-30);
		msleep(timeInterval);
		
		//Calculate how ar we drove in that time
		currentAngle += readGyro() * timeInterval/1000;
	}
}
