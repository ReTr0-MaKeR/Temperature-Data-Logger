#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BMP_SDA 21
#define BMP_SCL 22
#define LDR_PIN 4

Adafruit_BMP280 bmp; // I2C
Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
  Serial.begin(9600);
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void loop() {
  float temperature = bmp.readTemperature();
  int lightLevel = digitalRead(LDR_PIN);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  int16_t x = (display.width() - 19 * 6) / 2; 
  int16_t y = (display.width() - 10 * 6) / 2; 
  int16_t z = (display.width() - 19 * 6) / 2;
  int16_t w = (display.width() - 11 * 6) / 2;
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(x, 2);
  display.println("Temparature & Light");
  display.setCursor(y, 13);
  display.println("Datalogger");
  display.setCursor(z, 23);
  display.println("--------***--------");
  

  display.setCursor(0, 35);
  display.print("Temperature: ");
  display.print(temperature);
  display.print((char)247);
  display.println("C");

  display.setCursor(w, 50);
  if (lightLevel == HIGH) {
    display.println("It's dark.");
  } else {
    display.println("It's light.");
  }
  display.display();
  
  delay(500);
}
