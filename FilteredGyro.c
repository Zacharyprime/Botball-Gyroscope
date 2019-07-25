#include <kipr/botball.h>
double findBias(){
	//Stop the motors (make bot stand still)
    ao();
    msleep(300);
    
    //Find the average noise
    int i = 0;
    double avg = 0;
    while(i<50){
     	avg += gyro_z();
        msleep(1);
        i++;
    }
    double bias = avg/50.0;   
    return bias;
}

int main()
{
    double bias = findBias();
    int raw = gyro_z();
    int filtered = raw - bias;
    
    printf("Bias: %f \n Raw Value: %d \n Filtered for Noise: %d \n", bias, raw, filtered);
    return 0;
}
