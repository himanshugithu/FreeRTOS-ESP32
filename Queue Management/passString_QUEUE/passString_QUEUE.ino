#define RED 5
#define YELLOW 4
#define BLUE 15

QueueHandle_t fruitBasket;
const char* fruit_1 = "MANGO";
const char* fruit_2 = "APPLE";


void setup() {
  Serial.begin(115200);
  fruitBasket = xQueueCreate(10, sizeof(char*));
  xTaskCreate(xSenderTask,"Sender1",1024,(void*)fruit_1,1,NULL);
  xTaskCreate(xSenderTask,"sender2",1024,(void*)fruit_2,1,NULL);
  xTaskCreate(xReceiverTask,"Receiver",1024,(void*)NULL,1,NULL);
}

void xSenderTask(void* pvParameter)
{
  pinMode(BLUE,OUTPUT);
  pinMode(RED,OUTPUT);
  BaseType_t qStatus;
  const char* data = (char*)pvParameter;
  while(1)
  {
    qStatus  = xQueueSend(fruitBasket,&data,portMAX_DELAY);
    if(qStatus == pdPASS)
    {
      Serial.println("Send data: " + String(data));
      digitalWrite(BLUE,!digitalRead(BLUE));
    }
    else{
      digitalWrite(RED,!digitalRead(RED));
    }
  }
}


void xReceiverTask(void* pv)
{
  const char* receiveData;
  pinMode(YELLOW,OUTPUT);
  pinMode(RED,OUTPUT);
  while(1)
  {
    if(xQueueReceive(fruitBasket,&receiveData,portMAX_DELAY)==pdPASS)
    {
      Serial.println("Receive data: " + String(receiveData));
      digitalWrite(YELLOW,!digitalRead(YELLOW));
    }
    else{
      digitalWrite(RED,!digitalRead(RED));
    }
  }
}








void loop() {
  // put your main code here, to run repeatedly:
}
