#include <LiquidCrystal.h>

const int rs = 7;
const int en = 8;
const int d4 = 9;
const int d5 = 10;
const int d6 = 11;
const int d7 = 12;

int dt = 1000;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // creates lcd object

const int trig = 5;
const int echo = 6;
float duration;
float distance;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  lcd.begin(16,2); // 16 columns, 2 rows *why is columns first LOL*
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
  float x = getSpeed();
  plot("speed", x, false);

  lcd.setCursor(0,0);
  lcd.print("speed: ");
  lcd.print(x);
  lcd.print("cm/s");
  lcd.print("    "); // to erase old digits if new number is shorter
  
  if(x > 30){
    lcd.setCursor(0,1);
    lcd.print("Dangerous");
  }

  else if(x > 15){
    lcd.setCursor(0,1);
    lcd.print("Fast     ");
  }

  else{
    lcd.setCursor(0,1);
    lcd.print("Safe     ");
  }

  delay(200);
  

}

float getDistance(){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  //amount of time trigger needs to stay on to release ultrasonic wave is 10 microseconds
  delayMicroseconds(10);

  digitalWrite(trig, LOW);

  //measures the amount of time the echoPin stays high (time from when the ultrasonic wave was emitted, to when echo hits receiver), if no signal is received in 30000 ms call is cancelled
  duration = pulseIn(echo, HIGH, 30000);


  //sound = 0.034 centimeters per microsecond. sound multiplied by duration in microseconds gives distance in centimeters from sensor to object x2
  distance = duration * .034/2;

  return distance;
}

float getSpeed(){

  float distance1 = getDistance();
  plot("distance", distance1, true);
  delay(100);
  float distance2 = getDistance();

  float distance = abs(distance2 - distance1);

  float s = distance/0.1;

  return s;
  
}

void plot(String label, float value, bool last){
  Serial.print(label);
  if(label != "") Serial.print(":");
  Serial.print(value);
  if(last == false) Serial.print(",");
  else Serial.println();
}
