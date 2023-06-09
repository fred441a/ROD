#include <krnl.h>
//pin output
#define W1 2
#define W2 9
#define Pot A0
#define MotorPWM 10
#define DirectionPin 12

//
double Setpoint, Input, Output;

double Speed;
// True = backwards , False = forward
bool MeasuredDirection = true;
int potValue;
long int count;
k_t *s_sem, *pid_sem, *pot_sem;


//potRead = 112 ms
//Interrupt 1.7 ms
//motorControl 46 ms
//calculateSpeed = 0.74 ms


void testTask(){
        Speed = map(count,0,17000,0,255);
        count = 0;
}


void setup(){
    Serial.begin(115200);
    Serial.println("Running time test");
    k_init(5, 3, 0);
    s_sem = k_crt_sem(1, 1);
    pid_sem = k_crt_sem(1, 1);
    pot_sem = k_crt_sem(1,1);
    count = 5000;
    long int time = micros();
    for(long int i = 0;i < 100001; i ++){
        testTask();
    }
    Serial.print((micros()-time)/100000.0);
    Serial.println(" :Time");
    
    Serial.print(Speed);
    k_start();

}

void loop(){

}