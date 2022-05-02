#include <Wire.h>
#include <Servo.h>
#include <Adafruit_MLX90614.h>

//Motor
int btn = 4;
int servo = 9;
int motorAngle = 0;
int MotorSpeed = 1;
Servo myservo;

//MLX90614
float temperature, temp;
float sum;
int i=0;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

//HC-SR04
#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
#define SOUND_VELOCITY 0.034

void setup() {
  Serial.begin(9600);
  //Motor
  myservo.attach(servo);
  myservo.write (0);
  pinMode(btn, INPUT_PULLUP);
  //MLX90614
  mlx.begin();
  //HC-SR04
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
}

void controlMotor()
{
  int btnState = digitalRead(btn);
  //Serial.print("State of the button: ");
  //Serial.println(btnState);
  //Serial.println(motorAngle);
  if (btnState == 0)  
  {
    for(int i = 0; i < 120; i++){
      myservo.write(motorAngle += MotorSpeed); 
      if(motorAngle > 120)
      {
        motorAngle = 120;
      }  
      delay(5);  
    }
  }
  else
  {
      for(int i = 0; i < 120; i++){
      myservo.write(motorAngle -= MotorSpeed); 
      if(motorAngle < 0)
      {
        motorAngle = 0;
      }  
      delay(5);  
    };
  } 
}

void ultraSonic() {
  digitalWrite(trigPin, LOW);// Clears the trigPin
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);// Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);// Reads the echoPin, returns the sound wave travel time in microseconds
  
  distance = duration * SOUND_VELOCITY/2;// Calculate the distance
}

void printTemp(){
  if (distance >= 11 && distance <= 17){
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
  }

void loop() {
ultraSonic();
printTemp();
controlMotor();
delay(200);
}