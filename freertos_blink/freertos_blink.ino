#include <krnl.h>

    char msgBuff[10*2];

    k_msg_t* pMsg = k_crt_send_Q(10,2,msgBuff);

void task1 (){
    while (1)
    {
        int value = 10;
        k_send(pMsg,&value);
        Serial.println("task 1");
        //PORTB |= B00010000;
        k_sleep(100);
    }
}

void task2(){
    while (1)
    {
        int value = 0;
        k_receive(pMsg,&value,10,NULL);
        Serial.println(value);
        //PORTB |= B00100000;
        k_sleep(100);
    }
}

char task1Mem[100];
char task2Mem[100];


void setup(){
    Serial.begin(9600);
    Serial.println("Jeg er tændt nu!");
    
    k_crt_task(task1,1,task1Mem,100);
    k_crt_task(task2,2,task2Mem,100);
    k_init(2,0,1);
    k_start();
}

void loop (){


}