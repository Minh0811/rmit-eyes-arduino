//src: https://miliohm.com/mlx90614-distance-range-text-and-distance-extension/
//the code below allow you to read temperature much more stable and accurate


#include <Wire.h>
#include <Adafruit_MLX90614.h>
float temperature, temp;
float sum;
int i=0;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
void setup() {
  Serial.begin(9600);
  Serial.println("MLX90614 smoothing test");
  mlx.begin();
}
void loop() {
  while (i < 30) {
    temp= mlx.readObjectTempC();
    sum += temp;
    i++;
    delay(1);
  }
  temperature = sum/30.0;
  sum = 0;
  i = 0;
  Serial.println(temperature);
  delay(50);
}