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

int rightSpeed, leftSpeed; //Initialize Variables
double fixedAngle;
void drive(int speed, int time){
	int currentTime = 0;
	double currentAngle = 0;
	double newGyro = readGyro();
	
	while(currentTime<time){
		fixedAngle = currentAngle/conversion;
		rightSpeed = speed - (3.27 + 4.15*fixedAngle + 0.139 * pow(fixedAngle,2))/2;
		leftSpeed = speed + (3.27 + 4.15*fixedAngle + 0.139 * pow(fixedAngle,2))/2;
		
		oldGyro = newGyro;
		newGyro = readGyro(); //Update Gyro values for integration
		
		mav(1,rightSpeed);
		mav(0,leftSpeed);
		
		msleep(timeInterval);
		currentTime+=timeInterval;
		
		//Trapazoid Sum
		currentAngle += 0.5*(newGyro-oldGyro)*timeInterval/1000 + oldGyro * timeInterval/1000;
	}
}
