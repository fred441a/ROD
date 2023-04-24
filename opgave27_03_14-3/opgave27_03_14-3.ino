#define WheelRadius 25.0
#define CalibrationConstant 2.0 * 3.14 * WheelRadius

unsigned long AccumulatedDistance = 0;

int RotationSinceLast()
{
    return 20;
}

void CumulativeDistance(void *)
{
    for (;;)
    {
        AccumulatedDistance += RotationSinceLast() * CalibrationConstant;
        vTaskDelay(100);
    }
}

void setup()
{
    xTaskCreate(CumulativeDistance, "CUMDIST", 1024, NULL, 1, NULL);
}

void loop()
{
}