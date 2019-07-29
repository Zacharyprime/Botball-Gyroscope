#include <kipr/botball.h>
double bias; //Make bias a global variable so that all functions can see it
double conversion = 1024/250;

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

void arc(int leftSpeed, int rightSpeed, double targetAngle){
	double angle = 0;
	mav(0, rightSpeed);
	mav(1, leftSpeed);
	while(abs(angle) < targetAngle*conversion){
		msleep(timeInterval);
		angle += readGyro() * timeInterval/1000;
	}
	mav(0,0);
	mav(1,0);
}
