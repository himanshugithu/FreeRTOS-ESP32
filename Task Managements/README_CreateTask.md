
# Create Task Example (FreeRTOS on ESP32)

This example demonstrates how to create tasks in FreeRTOS using the `xTaskCreate()` API. Tasks are the basic units of execution in FreeRTOS, similar to threads.

---

## 📁 File: `2_Creating_tasks.ino`

### ✅ What This Code Does

It creates two tasks named `Task1` and `Task2`, each running a loop that prints its identity every second. This example is great for understanding basic multitasking.

---

## 🧠 Key Concepts

- **Task**: A function that runs independently and concurrently with other tasks.
- **xTaskCreate()**: Function to create a new task.
- **vTaskDelay()**: Causes a task to sleep for a specified time.

---

## 🧾 Code Explanation (Line by Line)

```cpp
void Task1code( void * parameter ) {
```
- **Function Signature** for Task1. It must return `void` and accept a single `void *` parameter.

```cpp
  for(;;) {
    Serial.println("Task1 is running");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
```
- `for(;;)` is an infinite loop.
- `Serial.println(...)`: Prints to the serial monitor.
- `vTaskDelay(...)`: Delays the task for 1000 ms (1 second).
- `portTICK_PERIOD_MS` converts milliseconds to ticks.

```cpp
void Task2code( void * parameter ) {
  for(;;) {
    Serial.println("Task2 is running");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
```
- Same structure as `Task1code`, but for the second task.

---

### 🛠️ `setup()` Function

```cpp
void setup() {
  Serial.begin(115200);
```
- Initializes the serial communication at 115200 baud rate.

```cpp
  xTaskCreate(
    Task1code,         // Function to be called
    "Task1",           // Name of the task (for debugging)
    10000,             // Stack size (in words)
    NULL,              // Parameter to pass
    1,                 // Task priority
    NULL               // Task handle (not used here)
  );
```
- Creates the first task with medium priority.

```cpp
  xTaskCreate(
    Task2code, "Task2", 10000, NULL, 1, NULL);
```
- Creates the second task with the same priority.

```cpp
}
```
- Closes `setup()` function.

```cpp
void loop() {
  // Nothing here; everything is handled by tasks.
}
```
- `loop()` is empty because FreeRTOS handles the execution now.

---

## 📤 Expected Output

On the Serial Monitor, you should see alternating prints:
```
Task1 is running
Task2 is running
Task1 is running
Task2 is running
...
```

Both tasks share the CPU time equally since they have the same priority.

---

## 📝 Notes

- Tasks with the same priority share CPU time using time-slicing.
- Use `vTaskDelay` to yield the CPU, or else higher-priority tasks may starve lower ones.
- Make sure you allocate enough stack size (e.g., 10000 words here).

---

## 📚 References

- [FreeRTOS Task Creation](https://www.freertos.org/a00125.html)
- [ESP32 Arduino + FreeRTOS](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/freertos.html)
