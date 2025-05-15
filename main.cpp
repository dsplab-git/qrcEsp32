// OLED 출력 코드.
#include <Arduino.h>
#include <Adafruit_MPU6050.h> // 주석표시는 다 추가 필요.
#include <Wire.h> //
#include <U8g2lib.h> //
#include <SPI.h> 

Adafruit_MPU6050 mpu; // IMU
float x, y, z;

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);


void setup(void)
{
  Serial.begin(115200);
  while(!Serial)
  {
    delay(10);
  }

  // 디스플레이 초기화
  u8g2.begin();
  u8g2.clear();
  u8g2.setFont(u8g2_font_profont22_tr);
  u8g2.setCursor(0, u8g2.getDisplayHeight() / 2);

  // IMU 센서 초기화
  while(!mpu.begin())
  {
    Serial.println("IMU sensor init failed");
    delay(100);
  }
  Serial.println("IMU sensor init succeed");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_1000_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_94_HZ);

}

void oledPrn()
{
  byte fontHeight = 14, whiteSpace = 3;
  byte cx = 0, cy = fontHeight;
  u8g2.clear();
  u8g2.setCursor(cx, cy);

  u8g2.printf("X: %.2f", x);
  cy += fontHeight + whiteSpace;
  u8g2.setCursor(cx, cy);

  u8g2.printf("Y: %.2f", y);
  cy += fontHeight + whiteSpace;
  u8g2.setCursor(cx, cy);

  u8g2.printf("Z: %.2f", z);

  u8g2.sendBuffer();
}

void loop()
{
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  x = a.acceleration.x;
  y = a.acceleration.y;
  z = a.acceleration.z;

  // Serial.printf("%f \n%f \n%f\n", x, y, z);

  oledPrn();

  delay(1000);
}
