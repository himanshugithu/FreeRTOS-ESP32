#define RED 5
#define YELLOW 4
#define BLUE 15
#define VIPGREEN 2

#define senderButton 18
#define receiverButton 19
#define VIPreceiverButton 21
#define peekButton 22

int8_t count = 1;
int8_t VIPcount = 10;
QueueHandle_t queue;

void setup() {
  Serial.begin(115200);
  delay(1000);  // Give some time for Serial to initialize

  pinMode(senderButton, INPUT_PULLUP);
  pinMode(receiverButton, INPUT_PULLUP);
  pinMode(VIPreceiverButton,INPUT_PULLUP);
  pinMode(peekButton,INPUT_PULLUP);
  pinMode(BLUE, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(VIPGREEN,OUTPUT);

  // Create a queue with space for 5 int8_t values
  queue = xQueueCreate(5, sizeof(int8_t));
  if (queue == NULL) {
    Serial.println("Queue creation failed!");
    while (1);  // Stop if queue creation fails
  }

  // Create the sender and receiver tasks
  xTaskCreate(xTaskSender, "SENDER", 1024, NULL, 1, NULL);
  xTaskCreate(xTaskReceiver, "RECEIVER", 1024, NULL, 1, NULL);
  xTaskCreate(xTaskSenderVIP, "VIP", 1024, NULL, 1, NULL);
  xTaskCreate(xTaskPeek,"PEEK",1024,NULL,1,NULL);
}

void xTaskPeek(void* pvParameter)
{
  int receivedData;
  while(1)
  {
    if(digitalRead(peekButton) == LOW)
    {
      if (xQueuePeek(queue, &receivedData, 0) == pdPASS) 
        {
        Serial.println("Peeked (not removed): " + String(receivedData));
        } 
      else
        {
          Serial.println("QUEUE EMPTY");
        }
      while (digitalRead(peekButton) == LOW) 
        { // Debounce delay
          vTaskDelay(20 / portTICK_PERIOD_MS);
        }
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void xTaskSenderVIP(void* pvParameter)
{ 
  BaseType_t qStatus;
  while(1)
  {
    if(digitalRead(VIPreceiverButton)==LOW)
    {
      qStatus = xQueueSendToFront(queue, &VIPcount,0);
      if(qStatus ==pdPASS)
      {
        Serial.println("VIP COUNT : " + String(VIPcount));
        digitalWrite(VIPGREEN, HIGH);  
        vTaskDelay(50 / portTICK_PERIOD_MS);
        digitalWrite(VIPGREEN, LOW);  // Toggle BLUE LED
        vTaskDelay(50 / portTICK_PERIOD_MS);
      }
      else if(qStatus == errQUEUE_FULL)
      {
        Serial.println("Queue is full");
        digitalWrite(RED, HIGH);  
        vTaskDelay(50 / portTICK_PERIOD_MS);
        digitalWrite(RED, LOW);
        vTaskDelay(50 / portTICK_PERIOD_MS);
      }
      while (digitalRead(senderButton) == LOW) 
      { // Debounce delay
        vTaskDelay(20 / portTICK_PERIOD_MS);
      }
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void xTaskSender(void* pvParameter) {
  BaseType_t qStatus;
  while (1) {
    if (digitalRead(senderButton) == LOW) {
      qStatus = xQueueSend(queue, &count, 0);  // Don't block, just check
      if (qStatus == pdPASS) {
        Serial.println("Sent to queue: " + String(count));
        count++;
        digitalWrite(BLUE, HIGH);  
        vTaskDelay(50 / portTICK_PERIOD_MS);
        digitalWrite(BLUE, LOW);  // Toggle BLUE LED
        vTaskDelay(50 / portTICK_PERIOD_MS);
      } 
      else if (qStatus == errQUEUE_FULL) {
        Serial.println("Queue is full");
        digitalWrite(RED, HIGH);  
        vTaskDelay(50 / portTICK_PERIOD_MS);
        digitalWrite(RED, LOW);
        vTaskDelay(50 / portTICK_PERIOD_MS);
      }
      while (digitalRead(senderButton) == LOW) { // Debounce delay
        vTaskDelay(20 / portTICK_PERIOD_MS);
      }
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void xTaskReceiver(void* pvParameter) {
  int8_t receivedValue;
  while (1) {
    if (digitalRead(receiverButton) == LOW) {
      // Check if there is data in the queue
      if (xQueueReceive(queue, &receivedValue, 0) == pdPASS) {
        Serial.println("Received from queue: " + String(receivedValue));
        digitalWrite(YELLOW, HIGH);  
        vTaskDelay(50 / portTICK_PERIOD_MS);
        digitalWrite(YELLOW, LOW);
        vTaskDelay(50 / portTICK_PERIOD_MS);
      } 
      else {
        Serial.println("Queue is empty");
        digitalWrite(RED, HIGH);  
        vTaskDelay(50 / portTICK_PERIOD_MS);
        digitalWrite(RED, LOW);
        vTaskDelay(50 / portTICK_PERIOD_MS);
        count = 1;
      }

      // Debounce delay
      while (digitalRead(receiverButton) == LOW) {
        vTaskDelay(20 / portTICK_PERIOD_MS);
      }
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void loop() {
  // Main loop does nothing
}
