# Understanding `vTaskDelay`, `portTICK_PERIOD_MS`, and Tick Calculations in FreeRTOS

## 📚 Table of Contents

1. Introduction to FreeRTOS Ticks
2. The Role of `vTaskDelay`
3. Understanding `portTICK_PERIOD_MS`
4. Using `pdMS_TO_TICKS()`
5. Why Use `pdMS_TO_TICKS()` Instead of Manual Division?
6. Practical Examples
7. Conclusion

---

## 1. Introduction to FreeRTOS Ticks

FreeRTOS uses a **tick-based** scheduling system to manage the execution of tasks. The frequency of these ticks is defined by the configuration parameter `configTICK_RATE_HZ`, which is set in the `FreeRTOSConfig.h` file. This parameter defines the number of ticks per second, effectively setting the smallest unit of time FreeRTOS can measure.

### Key Terms:

* **Tick:** The smallest time unit in FreeRTOS.
* **Tick Rate:** The number of ticks that occur in one second.
* **Tick Period:** The duration of each tick in milliseconds.

### Example Tick Rates:

| Tick Rate (Hz) | Tick Period (ms) |
| -------------- | ---------------- |
| 1000           | 1 ms             |
| 100            | 10 ms            |
| 50             | 20 ms            |

---

## 2. The Role of `vTaskDelay`

The `vTaskDelay()` function is used to put a task in the **Blocked** state for a specific number of ticks. This allows the FreeRTOS scheduler to switch to other tasks during this period, improving overall system responsiveness.

### Basic Syntax:

```c
void vTaskDelay(const TickType_t xTicksToDelay);
```

* **`xTicksToDelay`**: Number of ticks to delay the task.

### Example:

If the tick rate is **1000 Hz** (1 ms per tick):

```c
vTaskDelay(500);  // 500 ms delay (500 ticks)
```

---

## 3. Understanding `portTICK_PERIOD_MS`

* `portTICK_PERIOD_MS` is a macro that converts milliseconds to ticks.
* It is calculated as:

```c
#define portTICK_PERIOD_MS (1000 / configTICK_RATE_HZ)
```

### Why Use It?

It ensures your delay code is portable across different FreeRTOS configurations. If the tick rate changes, your code remains accurate without modification.

### Example:

```c
// If configTICK_RATE_HZ = 1000
portTICK_PERIOD_MS = (1000 / 1000) = 1 ms per tick

// If configTICK_RATE_HZ = 100
portTICK_PERIOD_MS = (1000 / 100) = 10 ms per tick
```

---

## 4. Using `pdMS_TO_TICKS()`

FreeRTOS provides a safer, more flexible way to convert milliseconds to ticks:

```c
TickType_t pdMS_TO_TICKS(uint32_t ms);
```

### Benefits:

* Handles overflow and rounding correctly.
* Makes code cleaner and more readable.

### Example:

```c
const TickType_t delay500ms = pdMS_TO_TICKS(500);
vTaskDelay(delay500ms);
```

---

## 5. Why Use `pdMS_TO_TICKS()` Instead of Manual Division?

* **Safety:** Properly handles overflow.
* **Portability:** Works correctly across different tick rates.
* **Readability:** Clearly indicates the intention to delay for a specific time in milliseconds.

---

## 6. Practical Examples

### Basic Delay

```c
#include <Arduino_FreeRTOS.h>

void Task1(void *pvParameters) {
    while (1) {
        Serial.println("Task 1 Running");
        vTaskDelay(pdMS_TO_TICKS(1000));  // 1 second delay
    }
}

void setup() {
    Serial.begin(9600);
    xTaskCreate(Task1, "Task1", 128, NULL, 1, NULL);
}

void loop() {}
```

### Using `portTICK_PERIOD_MS`

```c
void Task2(void *pvParameters) {
    while (1) {
        Serial.println("Task 2 Running");
        vTaskDelay(1000 / portTICK_PERIOD_MS);  // 1 second delay
    }
}
```

---

## 7. Conclusion

Understanding ticks and how to convert milliseconds to ticks is crucial for precise task timing in FreeRTOS. Using `pdMS_TO_TICKS()` is a best practice for maintaining portable and reliable task timing.
