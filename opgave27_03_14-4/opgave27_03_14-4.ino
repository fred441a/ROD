SemaphoreHandle_t buttonSem;

bool buttonsPressed[12];

enum runningStatus
{
    up,
    down,
    still
};

struct elevatorStatus
{
    int floor;
    runningStatus running;
};

elevatorStatus floorStatus()
{
    return elevatorStatus{4, up};
}

void monitorButtons()
{
    //checks what button was pressed;
    xSemaphoreTake(buttonSem,1 / portTICK_PERIOD_MS);
    //sets the floor button that is pressed to true
    buttonsPressed[6] = true;
    xSemaphoreGive(buttonSem);
}

void floorScheduler(void *)
{
    for(;;){
        //schedules which floor is next
    }
}

void setup()
{
    attachInterrupt(digitalPinToInterrupt(2), monitorButtons, RISING);
    buttonSem = xSemaphoreCreateBinary();
    xSemaphoreGive(buttonSem);
    xTaskCreate(floorScheduler,"gulvBestemmer",1024,NULL,1,NULL);
    
}

void loop()
{
}