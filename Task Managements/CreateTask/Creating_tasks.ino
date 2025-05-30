#define RED 2
#define YELLOW 4
#define BLUE 15
#define GREEN 5


void setup()
{
  Serial.begin(9600);
  xTaskCreate(redLedControllerTask,
              "Red LED Task",
              1024,
              NULL,
              1,
              NULL);
  xTaskCreate(blueLedControllerTask,
              "Blue LED Task",
              1024,
              NULL,
              1,
              NULL);
  xTaskCreate(yellowLedControllerTask,
              "Yellow LED Task",
              1024,
              NULL,
              1,
              NULL);
    xTaskCreate(greenLedControllerTask,
              "green LED Task",
              1024,
              NULL,
              1,
              NULL);            
}

void redLedControllerTask(void *pvParameters)
{
  pinMode(RED, OUTPUT);

  while (1)
  {
    Serial.println("This is RED");
  }
}

void blueLedControllerTask(void *pvParameters)
{
  pinMode(BLUE, OUTPUT);
  while (1)
  {
    Serial.print("This is BLUE");
  }
}

void yellowLedControllerTask(void *pvParameters)
{
  pinMode(YELLOW, OUTPUT);
  while (1)
  {
    Serial.println("This is YELLOW");
  }
}

void greenLedControllerTask(void *pvParameters)
{
  pinMode(GREEN, OUTPUT);
  while (1)
  {
    Serial.println("This is GREEN");
  }
}

void loop()
{
}
