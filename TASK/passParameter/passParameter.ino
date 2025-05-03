#define RED 16
#define YELLOW 4
#define GREEN 2
#define BLUE 15

const uint16_t* redled = (uint16_t*)RED;
const uint16_t* yellowled = (uint16_t*)YELLOW;
const uint16_t* greenled = (uint16_t*)GREEN;
const uint16_t* blueled = (uint16_t*)BLUE;
// Serial.println((uint32_t)blueled);  
void setup()
{
  Serial.begin(115200);
  xTaskCreate(ledController,"LED",1024,(void*)redled,1,NULL);
  xTaskCreate(ledController,"LED2",1024,(void*)yellowled,1,NULL);
  xTaskCreate(ledController,"LED3",1024,(void*)greenled,1,NULL);
  xTaskCreate(ledController,"LED4",1024,(void*)blueled,1,NULL);
}

void ledController(void* pv)
{
  int pin = (int)pv;
  pinMode(pin,OUTPUT);
  while(1)
  {
    digitalWrite(pin,!digitalRead(pin));
    // vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void loop(){}