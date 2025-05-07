String str1 = "HELLOW";
String str2 = "WORLD";

void setup()
{
  Serial.begin(115200);
  xTaskCreate(printString,"String 1",1024,&str1,1,NULL);
  xTaskCreate(printString,"String 2",1024,&str2,1,NULL);
}

void printString(void* pv)
{
  String* data = (String*)pv;
  while (1)
  {
    Serial.println(*data);
    vTaskDelay(100 / portTICK_PERIOD_MS); // har 1 second me print
  }
}

void loop(){}