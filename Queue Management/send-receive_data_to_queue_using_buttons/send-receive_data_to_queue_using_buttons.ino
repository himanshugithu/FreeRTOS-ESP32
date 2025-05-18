#define RED 5
#define YELLOW 4
#define BLUE 15

#define senderButton 18
#define receiverButton 19
int8_t count = 1;

QueueHandle_t queue;

void setup() {
  Serial.begin(115200);
  delay(1000);  // Give some time for Serial to initialize

  pinMode(senderButton, INPUT_PULLUP);
  pinMode(receiverButton, INPUT_PULLUP);
  pinMode(BLUE, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);

  // Create a queue with space for 5 int8_t values
  queue = xQueueCreate(5, sizeof(int8_t));
  if (queue == NULL) {
    Serial.println("Queue creation failed!");
    while (1);  // Stop if queue creation fails
  }

  // Create the sender and receiver tasks
  xTaskCreate(xTaskSender, "SENDER", 1024, NULL, 1, NULL);
  xTaskCreate(xTaskReceiver, "RECEIVER", 1024, NULL, 1, NULL);
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

      // Debounce delay
      while (digitalRead(senderButton) == LOW) {
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
