#include <kipr/botball.h>

int main()
{
    //Stop the mtoors (make bot stand still)
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
    
    //Print our bias
   	printf("New Bias: %f \n", bias);
    return 0;
}
