#include <freeRTOS-Arduino>
#define LED1 10;
#define LED2 11;

void BlinkLED1(){
    while(1){
        static bool flip = true;
        digitalWrite(LED1, flip);
        flip = !flip;
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void BlinkLED2(){
    while(1){
        static bool flip = true;
        digitalWrite(LED2, flip);
        flip = !flip;
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}

char LEDmem[100];
char LED2mem[100];

void setup(){
    PinMode(LED1, OUTPUT);
    PinMode(LED2, OUTPUT);
    xTaskCreate(BlinkLED1,"LED1",1024,NULL,1,NULL);
    xTaskCreate(BlinkLED2,"LED2",1024,NULL,2,NULL);
}

void loop(){

}