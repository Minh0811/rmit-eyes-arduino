//src: https://surtrtech.com/2019/05/04/arduino-contactless-thermometer-with-mlx90614-oled-lcd/
//Read the temperature value from the sensor every 0.5 seconds
//correct range around 25cm

#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();



void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

Serial.println("Adafruit MLX90614 test");

mlx.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC());
Serial.print("*C\tOject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF());
Serial.print("F\tOject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");

Serial.println();
delay(500);
}