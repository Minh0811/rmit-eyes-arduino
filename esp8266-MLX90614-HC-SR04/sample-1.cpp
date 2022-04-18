#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Adafruit_MLX90614.h>

#define trigPin D6
#define echoPin D5

#define SOUND_VELOCITY 0.034

long duration;
float distance;

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

const char *ssid = "Meomeo"; //Enter your WIFI ssid
const char *password = "ahihidongok"; //Enter your WIFI password
WiFiClient client;


void setup() {
   delay(3000);
   Serial.begin(115200);
   Serial.println("Adafruit MLX90614 and esp8266 test");

   pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
   pinMode(echoPin, INPUT); // Sets the echoPin as an Input

   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
   }
   Serial.println("WiFi connected");
   delay(1000);
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
    
  Serial.print("Distance (cm): "); // Prints the distance on the Serial Monitor
  Serial.println(distance);
}

void printTemp(){

if (distance <= 20){
Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC());   
Serial.print("*C\tOject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
}

}

void loop(){
ultraSonic()
printTemp()
Serial.println();
delay(500);
}



