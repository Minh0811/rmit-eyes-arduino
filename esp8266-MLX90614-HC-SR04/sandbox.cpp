#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Adafruit_MLX90614.h>

#define trigPin D6 //
#define echoPin D5

#define SOUND_VELOCITY 0.034

long duration;
float distance;

float temperature, temp;
float sum;
int i=0;

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

const char *ssid = "Meomeo"; //Enter your WIFI ssid
const char *password = "ahihidongok"; //Enter your WIFI password
WiFiClient client;


void setup() {
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


void loop(){
ultraSonic();
printTemp();
Serial.println();
delay(50);
}



void printTemp(){
for (int i = 0; i < 10; i++) {
  temp= mlx.readObjectTempC();
  Serial.print("record temps = ");Serial.println(mlx.readObjectTempC());
  sum += temp;
  delay(500);
}
delay(500);
Serial.print("Before  sum = ");Serial.println(temperature);
temperature = sum/10;
delay(500);
sum = 0;
Serial.print("sum = ");Serial.println(temperature);
delay(50);
}

void printTemp(){
for (int i = 0; i < 30; i++) {
  temp= mlx.readObjectTempC();
  Serial.print("temps = ");Serial.println(temp);
  if (temp != 1037.55){
  
  sum += temp;
  Serial.print("sum = "); Serial.println(sum);
    }
  delay(500);
}

 if (sum < 150000){
  temperature = sum/30.0;
  Serial.print("avg temperature = "); Serial.println(temperature);

  Serial.println(temperature);
  delay(2000);
  }
  sum = 0;
  i = 0;
}


temp = mlx.readObjectTempC();
if (distance <= 30 && distance > 10){
  Serial.print("temps = ");Serial.println(temp);
}