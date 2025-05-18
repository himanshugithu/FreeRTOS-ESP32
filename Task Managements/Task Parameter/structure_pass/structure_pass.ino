struct basicLedConfig
{
  uint16_t pin;
  uint16_t delayMS;
};

basicLedConfig redConfig = {2,100};
basicLedConfig blueConfig = {4,100};

void setup()
{
  Serial.begin(115200);
  xTaskCreate(ledController,"led Control",1024,&redConfig,1,NULL);
  xTaskCreate(ledController,"led control",1024,&blueConfig,1,NULL);
}

void ledController(void* pv)
{
  basicLedConfig* config = (basicLedConfig*)pv;
  pinMode(config->pin,OUTPUT);
  while(1)
  {
    // digitalWrite(config->pin,!digitalRead(config->pin));
    Serial.println(config->pin);
    vTaskDelay(config->delayMS / portTICK_PERIOD_MS);
  }
}

void loop() {}
