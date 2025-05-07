# 📄 FreeRTOS String Task Example

This example demonstrates how to create FreeRTOS tasks to print strings from multiple tasks on an ESP32 (or compatible board). It uses **`String`** objects and task parameter passing to keep the code clean and flexible.

---

## 📋 Description

In this code:

* **Two tasks** are created to print two different strings (`str1` and `str2`).
* The **string pointers** are passed as task parameters using the `pvParameters` argument.
* The **string data** is then accessed inside the task using proper pcaointer sting.
* The tasks print the strings to the **Serial Monitor** every **100 milliseconds**.

---

## ⚙️ Code Breakdown

### 📐 String Definitions

```cpp
String str1 = "HELLOW";
String str2 = "WORLD";
```

* **`String`** is an Arduino class for handling text data.
* Two string objects, **`str1`** and **`str2`**, are created to hold the messages.

### 🏁 Setup Function

```cpp
void setup()
{
  Serial.begin(115200);
  xTaskCreate(printString, "String 1", 1024, &str1, 1, NULL);
  xTaskCreate(printString, "String 2", 1024, &str2, 1, NULL);
}
```

* **`Serial.begin(115200);`** starts the serial communication at **115200 baud**.
* **`xTaskCreate()`** is used to create the tasks:

### ✅ Task Creation (xTaskCreate)

```cpp
xTaskCreate(
  printString,     // Task function to run
  "String 1",     // Task name (used for debugging)
  1024,            // Stack size in bytes
  &str1,           // Pass address of str1 as parameter
  1,               // Priority (higher means more priority)
  NULL             // Task handle (not used here)
);
```

| Parameter         | Description                                                      |
| ----------------- | ---------------------------------------------------------------- |
| **`printString`** | Function that the task will execute.                             |
| **`"String 1"`**  | Human-readable task name (useful for debugging).                 |
| **`1024`**        | Stack size in bytes. **1KB** is sufficient for this simple task. |
| **`&str1`**       | Address of the string to pass as the parameter.                  |
| **`1`**           | Task priority (higher number = higher priority).                 |
| **`NULL`**        | Not using a task handle, so this is set to `NULL`.               |

### 📦 Passing the String Parameter

```cpp
String* data = (String*)pv;
```

* The **`pvParameters`** argument is a **void pointer** (generic pointer).
* To **use** the passed **`String`** data, we need to **cast** it back:

  * **`String*`** means a **pointer to a ****`String`**** object**.
  * **`(String*)pv`** casts the generic pointer **`pv`** to a **`String*`**.
* This line extracts the **address** of the original **`String`** object, allowing direct access to its contents.

### 🖨️ Task Function - `printString`

```cpp
void printString(void* pv)
{
  String* data = (String*)pv;  // Get the actual String object
  while (1)
  {
    Serial.println(*data);     // Print the string data
    vTaskDelay(100 / portTICK_PERIOD_MS); // Delay to prevent flooding
  }
}
```

* The **`String* data`** pointer is **dereferenced** with **`*data`** to get the actual string content.
* **`vTaskDelay(100 / portTICK_PERIOD_MS);`** delays the task by **100 milliseconds**, allowing other tasks to run.

### 🕛 Loop Function

```cpp
void loop() {}
```

* **Empty** because FreeRTOS takes control of the task scheduling.

---

## 🖨️ Expected Output

```
HELLOW
WORLD
HELLOW
WORLD
...
```

* Both strings will print to the **Serial Monitor** in an **alternating** fashion every 100 milliseconds.

---

## ✅ Key Concepts Covered

* **Task creation** with `xTaskCreate()`
* **Pointer casting** for task parameters
* **FreeRTOS task scheduling**
* **Efficient use of stack memory** for small tasks

---

## 👨‍💻 Author

**Himanshu Fanibhare**


---
