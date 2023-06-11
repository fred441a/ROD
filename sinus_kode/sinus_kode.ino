#include "sinTab.h"

void setup(){
    Serial.begin(115200);
    Serial.println("Standart time to beat: ");
    testTimeAndError(sinDEG);
    Serial.println("Personal Sin Function: ");
    testTimeAndError(SINUS);
}

double SINUS(double degrees){
    degrees = degrees-(360*(int)(degrees/360));
    return sinTab[(int)degrees];
}

double sinDEG(double degrees){
    return sin(degrees*PI/180);
}

void testTimeAndError(double (*sinfunc)(double)){
    Serial.print("Time in microSeconds: ");
    Serial.println(testTime(sinfunc));
    Serial.print("Realtive error: ");
    Serial.println(testError(sinfunc),10);
}

int testTime(double (*sinfunc)(double)){
    unsigned long int time = micros();
    double dummy = 0;
    for (int i = 0; i < 1000; i++){
        //Serial.println(sinfunc(i));
        dummy += sinfunc(i);
    }
    return (micros()-time)/1000;
}

double testError(double (*sinfunc)(double)){
    double avrRelativErr = 0;
    for(int i = 1; i <= 3600; i++){
        if(sinDEG(i/10.0) == 0){
            continue;
        }
        avrRelativErr += (sinfunc(i/10.0)-sinDEG(i/10.0))/sinDEG(i/10.0);
    }
    return avrRelativErr / 3600;
}

void loop(){

}