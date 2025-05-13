QueueHandle_t yearQueue;

void setup()
{
    Serial.begin(9600);
    yearQueue = xQueueCreate(5, sizeof(int32_t));

    xTaskCreate(vSenderTask, "Sender Task", 1024, NULL, 1, NULL);
    xTaskCreate(vReceiverTask, "Receiver Task", 1024, NULL, 1, NULL);
}

void vSenderTask(void *pvParameters)
{
    BaseType_t qStatus;
    int32_t valueToSend = 1999;
    while (1)
    {
        qStatus = xQueueSend(yearQueue, &valueToSend, 0);
    }
}

void vReceiverTask(void *pvParameters)
{
    int32_t valueReceived;
    BaseType_t qStatus;
    const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
    while (1)
    {
        xQueueReceive(yearQueue, &valueReceived, xTicksToWait);
        Serial.print("Received value  : ");
        Serial.println(valueReceived);
        vTaskDelay(1);
    }
}
void loop() {}
