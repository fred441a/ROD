
void setup(){
    pinMode(13,OUTPUT);
}


int setHighPin(char digPinNo){
    if(digPinNo <= 7){
        PORTD |= B00000001 << digPinNo;
    } else if(digPinNo <= 13){
        PORTB |= B00000001 << (digPinNo-8);
    }

    return -1;
}

int setLowPin(char digPinNo){
    if(digPinNo <= 7){
        PORTD &= ~(B00000001 << digPinNo);
    }else if(digPinNo <= 13){
        PORTB &= ~(B00000001 << (digPinNo-8));
    }
    return -1;

}

void loop(){
    setHighPin(13);
    delay(1000);
    setLowPin(13);
    delay(1000);
}