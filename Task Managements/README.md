# 🧠 FreeRTOS Multi-Tasking: Red, Blue, and Yellow LED Controller

This example demonstrates how to create multiple tasks in FreeRTOS on an ESP32 (or any compatible board) to simulate controlling different LEDs — Red, Blue, and Yellow — each handled by its own task.

---

## 📋 Description

Using `xTaskCreate()`, we launch **three concurrent tasks**:
- `redLedControllerTask`
- `blueLedControllerTask`
- `yellowLedControllerTask`

Each task is responsible for printing a message to the serial monitor, mimicking separate LED control logic.


---

## 🧠 `xTaskCreate()` Function Signature

```c
BaseType_t xTaskCreate(
    TaskFunction_t pxTaskCode,
    const char *const pcName,
    const uint32_t usStackDepth,
    void *const pvParameters,
    UBaseType_t uxPriority,
    TaskHandle_t *const pxCreatedTask
);
```

### 📌 Parameters Explained:

| Parameter           | Description |
|---------------------|-------------|
| `pxTaskCode`        | Pointer to the function that implements the task logic. |
| `pcName`            | A short name for the task (used for debugging and tracing). |
| `usStackDepth`      | The stack size allocated to the task in **words**, not bytes. On ESP32 (32-bit), 1 word = 4 bytes. So `100` = 400 bytes. |
| `pvParameters`      | Optional parameter to pass to the task. Use `NULL` if not needed. |
| `uxPriority`        | Task priority. Higher number = higher priority. Use `1` for basic tasks. |
| `pxCreatedTask`     | Optional pointer to store the task handle. Use `NULL` if not needed. |

### 🔁 Return Value:
- Returns `pdPASS` (`1`) if task creation is successful.
- Returns `errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY` if stack or memory could not be allocated.

---

## 📘 What is `BaseType_t`?

```c
typedef int BaseType_t;
```

- `BaseType_t` is a **FreeRTOS-defined signed integer type** used for **function return values** and general logic.
- It ensures **portability across platforms** by abstracting away platform-specific integer sizes.
- On most platforms like the **ESP32**, it is simply defined as `int`.

### ✅ Why use `BaseType_t` instead of `int`?

Using `BaseType_t` makes your code portable and consistent with FreeRTOS API standards, especially when switching to other microcontrollers.

### 🧪 Common Return Values Using `BaseType_t`

| Value                          | Meaning                                      |
|-------------------------------|----------------------------------------------|
| `pdPASS` (usually `1`)        | Function succeeded                           |
| `pdFAIL` or error codes       | Function failed (e.g., insufficient memory)  |

### 🧠 Example

```c
BaseType_t result;
result = xTaskCreate(...);

if (result == pdPASS) {
    Serial.println("Task created successfully!");
} else {
    Serial.println("Task creation failed.");
}
```

## 🧠 `xTaskCreate()`  Explanation

```c
xTaskCreate(
    taskFunction,   // Function the task will execute
    "Task Name",    // Human-readable name (for debugging)
    1024,           // Stack size in words (1024 x 4 = 4096 bytes on ESP32)
    NULL,           // Parameters passed to task (none in this case)
    1,              // Priority (1 = low, can be raised if needed)
    NULL            // Task handle (not used here)
);
```

This function creates a new task and adds it to the scheduler. FreeRTOS will handle when and how each task gets CPU time based on its priority.

---

## 🖨️ Output (Expected)

```
This is RED
This is BLUE
This is YELLOW
This is RED
This is BLUE
This is YELLOW
...
```

Each message is printed every 1000 milliseconds (1 second) by its corresponding task.

---

## ✅ Requirements

- ESP32 or compatible board
- Arduino IDE or PlatformIO
- FreeRTOS support (already included in ESP32 Arduino core)

---

## 🧩 Enhancements You Can Try

- Actually control real LEDs using `digitalWrite(RED, HIGH)` instead of just `Serial.println()`.
---

## 🧼 Cleanup Note

- `vTaskDelay()` allows the current task to yield CPU time, giving other tasks a chance to execute.  
It takes delay in ticks, so to delay in milliseconds, use:

```
vTaskDelay(delay_in_ms / portTICK_PERIOD_MS);
```
- Priority ranges from 0 (lowest) to configMAX_PRIORITIES-1. 
- Default value for configMAX_PRIORITIES is usually 25 on ESP32.
- Always check return values from xTaskCreate() to ensure the task was created successfully.
---

## 📌 Summary

- Demonstrates **multi-tasking** with FreeRTOS using `xTaskCreate()`
- Three independent tasks run in parallel
- Messages printed every second from each task
- Includes deep dive into `xTaskCreate()` function and parameters
---

📚 More info: [FreeRTOS xTaskCreate() official documentation](https://www.freertos.org/a00125.html)


---

## 👤 Author
Developed by **Himanshu Fanibhare**.
---

📌 *Feel free to contribute or raise an issue if you encounter any problems!* 🚀

---

