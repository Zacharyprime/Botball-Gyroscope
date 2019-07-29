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

void turn(int angle, int speed){
	int targetAngle = angle*conversion; //Conversion is 1024/250 to convert KIPR Units to degrees
	int currentAngle = 0; 
	int timeInterval = 10;
	
	double newGyro = readGyro();
	while(abs(currentAngle) < targetAngle){
		oldGyro = newGyro;
		
		if(currentAngle<targetAngle){
			motor(0,-speed);
			motor(1,speed);
		}
		else{
			motor(0,speed);
			motor(1,-speed);
		}
		
		msleep(timeInterval);
		newGyro = readGyro();
		
		//Trapezoid Sum to find new angle approximation
		currentAngle += 0.5*(newGyro-oldGyro)*timeInterval/1000 + oldGyro * timeInterval/1000;
	}
}
