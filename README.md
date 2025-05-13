# Introduction to FreeRTOS

## 1. What is FreeRTOS?

FreeRTOS is a real-time operating system (RTOS) for embedded devices that provides multitasking, scheduling, and real-time capabilities. It is lightweight, open-source, and designed to run on microcontrollers and small microprocessors. FreeRTOS is widely used in industrial, automotive, IoT, and consumer electronics due to its reliability, low overhead, and ease of integration.

### Key Characteristics:

* **Real-time Performance:** Provides deterministic response times.
* **Portability:** Supports a wide range of microcontroller architectures.
* **Modularity:** Small footprint, allowing selective inclusion of features.
* **Free and Open Source:** Distributed under the MIT license.
* **Community and Commercial Support:** Large community with commercial backing from AWS.

## 2. Features of FreeRTOS

FreeRTOS provides several powerful features, including:

### a. Task Management

* **Task Creation and Deletion:** Create tasks to perform independent operations.
* **Task Prioritization:** Assign different priority levels to tasks for better CPU utilization.
* **Task Scheduling:** Preemptive and cooperative scheduling.
* **Task Delays and Timeouts:** Control task execution timing using functions like `vTaskDelay()`.

### b. Inter-task Communication

* **Queues:** Exchange data safely between tasks.
* **Semaphores:** Synchronize tasks and manage shared resources.
* **Mutexes:** Prevent data corruption by ensuring exclusive access.

### c. Memory Management

* **Dynamic Memory Allocation:** Use multiple memory allocation schemes.
* **Static Memory Allocation:** Allocate memory at compile-time to reduce runtime overhead.

### d. Software Timers

* **Timers:** Run functions at regular intervals without creating separate tasks.

### e. Event Management

* **Event Groups:** Set and wait for event flags, providing lightweight synchronization.

### f. Real-time Control

* **Tickless Idle Mode:** Reduce power consumption by halting the system when idle.

## 3. FreeRTOS Variable Names

FreeRTOS follows specific naming conventions for variables to ensure consistency and readability:

* **x** - Variables of general type (e.g., `xTaskHandle` for task handles).
* **pv** - Pointers to void (e.g., `pvParameters` for task parameters).
* **pc** - Pointers to characters (e.g., `pcTaskName` for task names).
* **ux** - Unsigned integers (e.g., `uxPriority` for task priority).
* **v** - Void function return types (e.g., `vTaskDelete()` for task deletion).
* **b** - Boolean values (e.g., `bTaskRunning` for task state).
* **c** - Characters.
* **ul** - Unsigned long variables.

* **us** - Unsigned short variables.

FreeRTOS uses a specific naming convention to differentiate between various data types and scopes:

- Global Variables: Typically prefixed with a lowercase letter indicating the type, like xTaskHandle, pxQueueHandle, or ulCounter.
- Local Variables: Often start with a lowercase letter without a prefix, like count, index.
- Constants: Use uppercase letters and underscores, like pdMS_TO_TICKS, configTICK_RATE_HZ.

Example:

```cpp 
TaskHandle_t xTaskHandle;
QueueHandle_t xQueueHandle;
const TickType_t xDelay = pdMS_TO_TICK(1000);
BaseType_t xStatus;
UBaseType_t uxCount;
TaskHandle_t pxTaskHandle;
void *pvParameters;
char *pcMessage;
```

## 4. FreeRTOS Function Names

FreeRTOS function names are designed to be descriptive and intuitive. The naming convention generally follows this structure:

```
vFunctionTypeAction()
```

### Common Function Prefixes:

* **v** - Void functions (e.g., `vTaskStartScheduler()`).
* **x** - Functions returning a status or handle (e.g., `xTaskCreate()`).
* **pv** - Functions returning a pointer to void (e.g., `pvPortMalloc()`).
* **ux** - Functions returning unsigned values (e.g., `uxTaskPriorityGet()`).

### Functions in FreeRTOS follow a clear and consistent naming pattern:

- Task Functions: Start with v, x, or pv depending on the return type:
    - `vTaskDelay()` - void return type
    - `xTaskCreate()` - returns a status (success or failure)
    - `pvPortMalloc()` - returns a pointer (void*)

- Queue Functions:
    - `xQueueCreate()` - Create a queue
    - `xQueueSend()` - Send data to a queue
    - `xQueueReceive()` - Receive data from a queue

- Semaphore Functions:
    - `xSemaphoreCreateMutex()` - Create a mutex
    - `xSemaphoreTake()` - Acquire a semaphore
    - `xSemaphoreGive()` - Release a semaphore


```cpp
TaskHandle_t xHandle;

void vTaskFunction(void *pvParameters) {
    while (1) {
        // Task code
    }
}

void setup() {
    xTaskCreate(vTaskFunction, "Task1", 1024, NULL, 1, &xHandle);
    vTaskStartScheduler();
    vTaskStartScheduler();    // Starts the FreeRTOS scheduler
    xTaskCreate();            // Creates a new task
    uxTaskPriorityGet();      // Returns the priority of a task
    pvPortMalloc();           // Allocates memory from the heap
}
```
## 5. FreeRTOS Macro Names

Macros in FreeRTOS are used to simplify code, improve readability, and reduce errors. They typically use uppercase letters and underscores:

### Common Macros:

* **pdMS\_TO\_TICKS(ms)** - Convert milliseconds to ticks.
* **portTICK\_PERIOD\_MS** - Tick period in milliseconds.
* **pdTRUE / pdFALSE** - Boolean values for FreeRTOS functions.
* **configTICK\_RATE\_HZ** - System tick frequency.
* **pdPASS / pdFAIL** - Function success or failure status.

### Example:

```c
// Delay a task for 500ms
const TickType_t delayTime = pdMS_TO_TICKS(500);  // 500 ms delay
vTaskDelay(delayTime);
```

### Why Use Macros?

* Reduce code size and increase efficiency.
* Provide a level of abstraction for hardware-specific operations.
* Simplify complex operations.


## 6. Task State Diagram

#### Below is a task state diagram showing the lifecycle of a FreeRTOS task:

- Ready: Task is ready to run but waiting for CPU time.
- Running: Task is currently executing.
- Blocked: Task is waiting for a delay to expire or a resource to become available.
- Suspended: Task is inactive until explicitly resumed.
- Deleted: Task is terminated and its memory is released.

![Task States](./Images/tskstate.gif)


## 7. Common Pitfalls and Best Practices

- Stack Overflow: Ensure each task has enough stack space.
- Priority Inversion: Use mutexes with priority inheritance if needed.
- Starvation: Balance task priorities to avoid lower-priority tasks being starved.
- Efficient Memory Usage: Avoid frequent dynamic memory allocation.
- Avoid Blocking Delays: Use vTaskDelay() wisely to prevent task starvation.