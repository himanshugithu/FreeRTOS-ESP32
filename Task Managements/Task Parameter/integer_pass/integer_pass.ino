const int RED = 2;
const int BLUE = 4;
const int GREEN = 5;

void setup()
{
  Serial.begin(9600);
  xTaskCreate(ledController,"led",1024,(void*)&RED,1,NULL);
  xTaskCreate(ledController,"led",1024,(void*)&BLUE,1,NULL);
  xTaskCreate(ledController,"led",1024,(void*)&GREEN,1,NULL);
}

void ledController(void* pv)
{
  int pin = *((int*)pv);
  while(1)
  {
    Serial.println(pin);
  }
}

void loop(){}