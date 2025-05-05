#include <Arduino_FreeRTOS.h>

#define RED    6
#define YELLOW 7
#define BLUE   8

typedef int TaskProfiler;

TaskProfiler  RedLEDProfiler;
TaskProfiler  YellowLEDProfiler;
TaskProfiler  BlueLEDProfiler;

void setup()
{
  Serial.begin(9600);
  xTaskCreate(redLedControllerTask,
              "Red LED Task",
              100,
              NULL,
              1,
              NULL
              );
 xTaskCreate(blueLedControllerTask,
             "Blue LED Task",
             100,
             NULL,
             1,
             NULL);
 xTaskCreate(yellowLedControllerTask,
             "Yellow LED Task",
             100,
             NULL,
             1,
             NULL
             );
}

void redLedControllerTask(void *pvParameters)
{
  pinMode(RED,OUTPUT);

  while(1)
  {
   // Serial.println("This is RED");
  }
}

void blueLedControllerTask(void *pvParameters)
{
    pinMode(BLUE,OUTPUT);
    while(1)
    {
    //  Serial.print("This is BLUE");
    }
}

void yellowLedControllerTask(void *pvParameters)
{
   pinMode(YELLOW,OUTPUT);
  while(1)
  {
  //  Serial.println("This is YELLOW");
  }
}

void loop()
{}

