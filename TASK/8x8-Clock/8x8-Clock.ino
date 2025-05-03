#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <MD_MAX72xx.h>

// WiFi credentials
const char* ssid = "myssid";
const char* password = "password";

// Display settings
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CLK_PIN 18
#define DATA_PIN 23
#define CS_PIN   15
#define BUZZER_PIN 2

bool beepedThisMinute = false;

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// NTP client setup for India (UTC +5:30)
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 19800, 60000);  // 19800s = 5.5h offset, update every 60s

bool showColon = true;  // Toggle for blinking colon

void setup() {
  Serial.begin(115200);
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 5);  // Set brightness
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  WiFi.begin(ssid, password);

  // Keep showing spinner until Wi-Fi connects
  while (WiFi.status() != WL_CONNECTED) {
    spinnerAnimation();
  }

  Serial.println("WiFi connected.");
  mx.clear();

  timeClient.begin();
  timeClient.update();  // First sync
}

void loop() {
  timeClient.update();

  int hours = timeClient.getHours();
  int minutes = timeClient.getMinutes();
  int seconds = timeClient.getSeconds();

  // Beep three times at the start of every minute
  if (seconds == 0 && !beepedThisMinute) {
    for (int i = 0; i < 3; i++) {
      digitalWrite(BUZZER_PIN, HIGH);
      delay(1000);
      digitalWrite(BUZZER_PIN, LOW);
      delay(1000);
      Serial.println("beeping");
    }
    beepedThisMinute = true;
  }

  if (seconds != 0) {
    beepedThisMinute = false;
  }

  // Display logic
  char timeStr[9];
  snprintf(timeStr, sizeof(timeStr), showColon ? " %02d:%02d" : " %02d %02d", hours, minutes);
  Serial.println(timeStr);

  displayTime(timeStr);
  showColon = !showColon;
  delay(980);
}

// Spinner animation shown until Wi-Fi connects
void spinnerAnimation() {
  static const uint8_t frames[] = {0x18, 0x3C, 0x7E, 0xFF, 0x7E, 0x3C, 0x18};
  static int frame = 0;

  mx.clear();
  for (uint8_t col = 0; col < mx.getColumnCount(); col++) {
    mx.setColumn(col, frames[(frame + col) % 7]);
  }
  frame = (frame + 1) % 7;
  delay(100);
}

void displayTime(const char* timeStr) {
  uint8_t cBuf[8];
  mx.clear();
  int col = mx.getColumnCount() - 2;

  for (uint8_t i = 0; i < strlen(timeStr); i++) {
    uint8_t width = mx.getChar(timeStr[i], sizeof(cBuf), cBuf);

    for (uint8_t j = 0; j < width; j++) {
      col--;
      if (col < 0) return;
      mx.setColumn(col, cBuf[j]);
    }

    col--;
    if (col < 0) return;
    mx.setColumn(col, 0);
  }
}
