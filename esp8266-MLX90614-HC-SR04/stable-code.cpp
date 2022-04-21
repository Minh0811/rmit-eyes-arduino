#include <Servo.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Adafruit_MLX90614.h>

//HC-SR-04
#define trigPin D6
#define echoPin D5

#define SOUND_VELOCITY 0.034

long duration;
float distance;

//MLX90614
float temperature, temp;
float sum;
int i=0;

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

//ESP8266
const char *ssid = "Meomeo"; //Enter your WIFI ssid
const char *password = "ahihidongok"; //Enter your WIFI password
WiFiClient client;

//server
const char* serverName = "http://localhost:3000/";


unsigned long lastTime = 0;

// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

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
   Serial.print("IP address:\t");
   Serial.println(WiFi.softAPIP()); 
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
}

void httpPost(){
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
      
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);

      // Specify content-type header
      http.addHeader("Content-Type", "text/plain");
      // Data to send with HTTP POST
         
      // Send HTTP POST request
      int httpResponseCode = http.POST("Hello, World!");
      
      // If you need an HTTP request with a content type: application/json, use the following:
      //http.addHeader("Content-Type", "application/json");
      //int httpResponseCode = http.POST("{\"api_key\":\"tPmAT5Ab3j7F9\",\"sensor\":\"BME280\",\"value1\":\"24.25\",\"value2\":\"49.54\",\"value3\":\"1005.14\"}");

      // If you need an HTTP request with a content type: text/plain
      //http.addHeader("Content-Type", "text/plain");
      //int httpResponseCode = http.POST("Hello, World!");
     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }



void loop(){
ultraSonic();
printTemp();
httpPost();
Serial.println();
delay(500);
}
