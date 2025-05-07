# LED Task Controller with FreeRTOS (ESP32)

This project demonstrates how to use FreeRTOS tasks on the ESP32 to control multiple LEDs independently using task handlers. Each LED is configured with its own pin and delay through a structure, making it easy to add or modify LED behaviors.

## **📝 Code Overview**

### **1. Structure Definition (`basicLedConfig`)**

```cpp
struct basicLedConfig {
  uint16_t pin;       // GPIO pin number
  uint16_t delayMS;   // Blink delay in milliseconds
};
```

* **`pin:`** The GPIO pin number to which the LED is connected.
* **`delayMS:`** The delay time for blinking the LED.

### **2. Creating LED Configurations**

```cpp
basicLedConfig redConfig = {2, 100};   // RED LED on GPIO 2, 100ms delay
basicLedConfig blueConfig = {4, 1000};  // BLUE LED on GPIO 4, 1000ms delay
```

* Here, two LED configurations are created:

  * **`redConfig:`** Controls the red LED on GPIO 2 with a 100ms delay.
  * **`blueConfig:`** Controls the blue LED on GPIO 4 with a 1000ms delay.

### **3. FreeRTOS Task Creation (`xTaskCreate`)**

```cpp
void setup() {
  Serial.begin(115200);
  xTaskCreate(ledController, "LED Control 1", 1024, &redConfig, 1, NULL);
  xTaskCreate(ledController, "LED Control 2", 1024, &blueConfig, 1, NULL);
}
```

* **`xTaskCreate()`** is used to create tasks:

  * **Task Function:** `ledController`
  * **Task Name:** "LED Control 1" and "LED Control 2"
  * **Stack Size:** 1024 bytes
  * **Task Parameter:** Address of the LED configuration structure (e.g., **`&redConfig`**)
  * **Priority:** 1 (Low priority)
  * **Task Handle:** `NULL` (not used here)

### **4. LED Control Task Function (`ledController`)**

```cpp
void ledController(void* pv) {
  basicLedConfig* config = (basicLedConfig*)pv;
  pinMode(config->pin, OUTPUT);
  while (1) {
    Serial.println(config->pin);
    vTaskDelay(config->delayMS / portTICK_PERIOD_MS);
  }
}
```

* **Parameter Casting:** The generic **`void* pv`** is cast to a **`basicLedConfig*`** to access the LED pin and delay values.
* **Pin Configuration:** Sets the GPIO pin as an **output**.
* **Infinite Loop:** Prints the **pin number** to the Serial Monitor and delays the task using **`vTaskDelay()`**.

### **5. Empty Loop Function (`loop`)**

```cpp
void loop() {}
```

* Required for the Arduino framework but not used here as the task logic is handled by FreeRTOS.

## **🔗 Key FreeRTOS Functions Used**

* **`xTaskCreate()`** - Creates a new FreeRTOS task.
* **`vTaskDelay()`** - Suspends the task for a specified number of ticks.

## **📋 Output (Expected)**

* The Serial Monitor will print the GPIO pin numbers (2 and 4) repeatedly at the specified delay intervals (100ms each).

## **🚀 Next Steps**

* Add more LEDs by creating additional **`basicLedConfig`** structures and corresponding tasks.
* Implement a task to dynamically change LED blink rates.

## 🧑‍💻 Author
**Himanshu Fanibhare**  (fanibharehimanshu@gmail.com)
---
