#include <Wire.h>
#include <Adafruit_MLX90614.h>

float temperature, temp;
float sum;
int i=0;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04

long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

#define SOUND_VELOCITY 0.034

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  mlx.begin();
}

void ultraSonic() {
  digitalWrite(trigPin, LOW);// Clears the trigPin
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);// Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);// Reads the echoPin, returns the sound wave travel time in microseconds
  distance = duration * SOUND_VELOCITY/2;// Calculate the distance
  //Serial.print("distance = ");Serial.println(distance);
}

void printTemp(){
  if (distance >= 10 && distance <= 13){
  while (i < 30) {
    temp= mlx.readObjectTempC();
    sum += temp;
    i++;
    delay(1);
  }
  temperature = sum/30.0;
  sum = 0;
  i = 0;
  if(temperature > 35 && temperature < 41) {
  Serial.println(temperature);
  delay(50);
    }
   }
  }

void loop() {
ultraSonic();
printTemp();
delay(100);
}