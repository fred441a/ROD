SemaphoreHandle_t Sem1;

void task1(void*) {
  for(;;){
    xSemaphoreTake(Sem1, 10/ portTICK_PERIOD_MS);
    delay(10);
    xSemaphoreGive(Sem1);
    vTaskDelay(30/ portTICK_PERIOD_MS);
  }

}

void task2(void*) {
  for(;;){
    xSemaphoreTake(Sem1, 10/ portTICK_PERIOD_MS);
    delay(10);
    xSemaphoreGive(Sem1);
    delay(10);
    vTaskDelay(40/ portTICK_PERIOD_MS);
  }
}

void task3( void *) {
  for(;;){
    delay(20);
    vTaskDelay(60/ portTICK_PERIOD_MS);
  }
}


void setup() {
  xTaskCreate(task1, "task1", 1024, NULL, 1, NULL);
  xTaskCreate(task2, "task2", 1024, NULL, 2, NULL);
  xTaskCreate(task3, "task3", 1024, NULL, 3, NULL);
  Sem1 = xSemaphoreCreateBinary();
  xSemaphoreGive(Sem1);


}

void loop() {

}
