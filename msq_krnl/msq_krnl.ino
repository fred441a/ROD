#include <krnl.h>
struct k_msg_t *pMsg;
char messages [10*2];

void send(){
    while(1){
        char message = 'p';
        k_send(pMsg,(void *)&message);

        k_sleep(10);
    }
}

void Recive(){
    while (1)
    {
        char recieved;
        int lostMsg;
        if(0 <= k_receive(pMsg,&recieved,10,&lostMsg)){
            Serial.println(recieved);
        }
        k_sleep(100);
    }
    
}

char sendHeap[300];
char receiveHeap[300];

void setup(){
    Serial.begin(115200);
    k_init(2,0,1);
    pMsg = k_crt_send_Q(10,2,messages);
    k_crt_task(send,1,sendHeap,300);
    k_crt_task(Recive,2,receiveHeap,300);
    k_start();
}

void loop(){

}
