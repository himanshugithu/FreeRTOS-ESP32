# Memory Address Passing in FreeRTOS Tasks (Arduino/ESP32 Example)

This code demonstrates how to pass **memory addresses** between FreeRTOS tasks on Arduino or ESP32. It shows the proper way to handle pointer casting and memory access in a multi-task environment.

---

## 📋 Key Concept: Pointer Passing

The code focuses on passing **memory addresses** of variables (rather than just values) to tasks. This approach is useful because:

* It **reduces memory usage** by passing just the address instead of copying the value.
* It **enables shared memory access** between tasks, allowing tasks to share the same data.
* It **supports dynamic parameter handling**, making the code more flexible.

---

## 📂 Code Breakdown

### 1. Pin Constants Declaration

```
const int RED = 2;
const int BLUE = 4;
const int GREEN = 5;
```

* These are constants representing the GPIO pins for the RED, BLUE, and GREEN LEDs.
* **const int** means the values **cannot** be changed after initialization.
* These constants are stored in specific memory locations (e.g., **0x20001F00** for **RED**).

---

### 2. Task Creation (Address Passing)

```cpp
void setup()
{
  Serial.begin(9600);
  
  // Create tasks for each LED
  xTaskCreate(ledController, "led", 1024, (void*)&RED, 1, NULL);
  xTaskCreate(ledController, "led", 1024, (void*)&BLUE, 1, NULL);
  xTaskCreate(ledController, "led", 1024, (void*)&GREEN, 1, NULL);
}
```

* **Serial.begin(9600)**: Initializes serial communication.
* **xTaskCreate()**: Creates three separate FreeRTOS tasks, one for each LED.
* `(void*)&RED`: The **&** operator retrieves the **memory address** of the **RED** variable, which is then cast to a **void**\* to match the task function parameter type.

### 🔄 How Address Passing Works:

| LED   | Constant Value | Memory Address (Example) |
| ----- | -------------- | ------------------------ |
| RED   | 2              | 0x20001F00               |
| BLUE  | 4              | 0x20001F04               |
| GREEN | 5              | 0x20001F08               |

---

### 3. Task Function (Address Handling)

```cpp
void ledController(void* pv)
{
  // Extract the actual value from the address
  int pin = *((int*)pv);  // Cast and dereference
  while (1)
  {
    Serial.println(pin);
  }
}
```

* `void* pv`: The task receives a **void pointer**, which is a generic pointer type that can point to any data type.
* `(int*)pv`: Casts the **void**\* back to an **int**\*, allowing us to work with the original data type.
* `*`  Dereferences the pointer to get the **actual pin number** stored at the address.

### 🔍 Memory Access Process:

1. **Receive the address:** The function receives a **void**\* containing the memory address of the pin.
2. **Cast the pointer:** `(int*)pv` converts the **void**\* back to an **int**\*, matching the data type of the original variable.
3. **Dereference the pointer:** `*` is used to **read the actual value** stored at the memory address.

---

### 4. Infinite Loop (`while(1)`)

```
while (1)
{
  Serial.println(pin);
}
```

* The task continuously prints the **pin number** to the Serial Monitor.
* Without a delay, this can **flood** the Serial Monitor, making it hard to read.

---

### 5. Main Loop (`loop()`)

```
void loop(){}
```

* The main Arduino loop is empty because all the work is being handled by FreeRTOS tasks.

---

## 📋 Key Takeaways:

* **Memory Efficiency:** Passing addresses instead of copying values saves memory.
* **Pointer Casting:** Use `(int*)` to cast a **void**\* back to the original data type.
* **Dereferencing:** Use `*` to access the value at a given memory address.

---

## 📈 Expected Output:

The Serial Monitor will continuously print:

```
2
4
5
2
4
5
...
```

Each number corresponds to the **pin** number of the **RED**, **BLUE**, and **GREEN** LEDs.

---

## 💡 Potential Improvements:

* Add **delays** to make the output more readable.
* Blink led instead of printing the pin number
---

## 🧑‍💻 Author
**Himanshu Fanibhare**  
---
