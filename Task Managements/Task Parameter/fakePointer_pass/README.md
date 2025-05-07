# 🔀 FreeRTOS Multi-Tasking LED Controller with `pvParameters`

This example demonstrates using **FreeRTOS** to control multiple LEDs (Red, Blue, Yellow) in **parallel tasks**, where each task is responsible for toggling one LED using the `pvParameters` feature of `xTaskCreate()`.

---

## 📋 Description

- The program uses **three tasks**, each controlling a separate LED (Red on pin 6, Blue on pin 7, Yellow on pin 8).
- It uses `xTaskCreate()` to spawn each task and pass the **pin number as a parameter** using `pvParameters`.
- Inside the task, the passed pin number is used to toggle the LED.
- Blinks Red, Blue, and Yellow LEDs using **independent FreeRTOS tasks**.
- Demonstrates a **common pointer-casting trick** to send integers through `void*`.
---

## ⚙️ Setup Overview

### LED Pin Definitions:

```cpp
#define RED     2
#define BLUE    4
#define YELLOW  5
```

### ✅ Pointer Setup for Task Parameters

```cpp
const uint16_t *blueLed =(uint16_t *) BLUE; 
const uint16_t *redLed  =(uint16_t *)RED;
const uint16_t *yellowLed = (uint16_t)YELLOW;
```
- Converts LED pin numbers to pointers so they can be passed as `void*` to `xTaskCreate()`.
---


### ✅ Setup Function — Task Creation

```cpp
void setup()
{
  xTaskCreate(ledControllerTask, "RED LED Task", 1024, (void *)redLed, 1, NULL);
  xTaskCreate(ledControllerTask, "BLUE LED Task", 1024, (void *)blueLed, 1, NULL);
  xTaskCreate(ledControllerTask, "YELLOW LED Task", 1024, (void *)yellowLed, 1, NULL);
}
```
- Creates three tasks using `xTaskCreate()`.
- Each task shares the same function `ledControllerTask`, but receives a **different LED pin** via `pvParameters`.
---

## 🧠 Key Concept: Passing Integers as `void*`

In FreeRTOS, `xTaskCreate()` accepts a generic pointer (`void *pvParameters`) to pass user data to a task. But **you can't pass an integer directly**, like this:

```cpp
xTaskCreate(taskFunction, "Blue", 100, 7, 1, NULL);  // ❌ WRONG
```

So we trick the system:

```cpp
const uint16_t *blueLed = (uint16_t *)BLUE;  // Treat 7 as if it's a pointer
xTaskCreate(taskFunction, "Blue", 100, (void *)blueLed, 1, NULL);  // ✅ OK
```

### 🧩 Breakdown of This Line:

```cpp
const uint16_t *blueLed = (uint16_t *) BLUE;
```

| Part                        | Meaning                                                                 |
|----------------------------|-------------------------------------------------------------------------|
| `BLUE`                     | A macro for pin number 7 (an int)                                       |
| `(uint16_t *) BLUE`        | Casts the number 7 into a pointer (pretending 7 is a memory address)     |
| `const uint16_t *blueLed`  | Declares a pointer to a constant 16-bit value                           |

### 🧠 Why This Works

You're not actually using this as a real pointer — you’re just using it to **pass the number** through a `void*`. Later, inside the task, you reverse the trick:

```cpp
void ledControllerTask(void *pvParameters) {
  int pin = (int)pvParameters;  // Get back the original pin number
}
```

So:
- The cast to pointer is just a workaround.
- No memory is read or dereferenced.
- You're only **packaging an integer inside a pointer**.

---

## 🔄 Inside the Task Function

```cpp
void ledControllerTask(void *pvParameters) {
  int pin = (int)pvParameters;     // Extract the pin number
  pinMode(pin, OUTPUT);           // Set it as output

  while(1) {
    digitalWrite(pin, digitalRead(pin) ^ 1);  // Toggle LED ,(digitalWrite(pin, !digitalRead(pin))
    vTaskDelay(500 / portTICK_PERIOD_MS);     // Delay to make blinking visible
  }
}
```

- The XOR (`^ 1`) toggles the LED state.
- **⚠️ Important**: If there is **no delay**, so the task runs infinitely fast and toggles the LED too rapidly for the eye to detect. A `vTaskDelay()` is strongly recommended.

---

### ✅ Loop Function

```cpp
void loop() {}
```

- Empty because FreeRTOS takes over the main scheduling.
---

## 🖨️ Expected Behavior

With the recommended delay added:
- All three LEDs will **blink independently** at 0.5-second intervals.
- FreeRTOS scheduler ensures fair CPU time distribution between tasks.

---

✅ Requirements

- ESP32 or compatible board
- Arduino IDE or PlatformIO
- FreeRTOS support (already included in ESP32 Arduino core)

---

## 🧑‍💻 Author
**Himanshu Fanibhare**  
---

## 📌 Summary

- Demonstrates **FreeRTOS multi-tasking** on ESP32.
- Uses `pvParameters` to control task behavior dynamically.

