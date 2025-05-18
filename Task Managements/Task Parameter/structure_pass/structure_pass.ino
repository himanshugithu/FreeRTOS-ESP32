#include <Arduino_FreeRTOS.h>

// Structure for task parameters
typedef struct {
    int pin;
    int delayMS;
} LedConfig;

// Creating two different LED configurations
LedConfig redConfig = {6, 500};   // Pin 6, 500ms delay
LedConfig blueConfig = {7, 300};  // Pin 7, 300ms delay

void setup() {
    Serial.begin(9600);
    // Creating tasks with structured parameters
    xTaskCreate(ledTask, "Red LED", 100, &redConfig, 1, NULL);
    xTaskCreate(ledTask, "Blue LED", 100, &blueConfig, 1, NULL);
}

void ledTask(void *pvParameters) {
    // Accessing the passed structure
    LedConfig *config = (LedConfig *)pvParameters;
    pinMode(config->pin, OUTPUT);
    
    while (1) {
        digitalWrite(config->pin, HIGH);
        vTaskDelay(config->delayMS / portTICK_PERIOD_MS);
        digitalWrite(config->pin, LOW);
        vTaskDelay(config->delayMS / portTICK_PERIOD_MS);
    }
}

void loop() {}
