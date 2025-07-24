#include<LiquidCrystal.h>

const int rs = 7;
const int en = 8;
const int d4 = 9;
const int d5 = 10;
const int d6 = 11;
const int d7 = 12;

const int buzzPin = 3;
const int buttonPin = 4;

int dt;
int buzzStart;
int buttonPressed;
int score;
int highScore = 32767;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // creates lcd object that represents how our LCD is wired

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2); // 16 columns, 2 rows
  pinMode(buzzPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  randomSeed(analogRead(A0));
  lcd.setCursor(0,0);
  lcd.print("Time: N/A");
  lcd.setCursor(0,1);
  lcd.print("Best: N/A");

}

void loop() {
  // put your main code here, to run repeatedly:
  dt = random(2000,7000); // random integer between 2000 and 7000 (includes 2000 excludes 7000);

  delay(dt);
  analogWrite(buzzPin, 50);
  buzzStart = millis();
  while(digitalRead(buttonPin) == 1){}
  digitalWrite(buzzPin, LOW);
  buttonPressed = millis();
  score = buttonPressed - buzzStart;
  setScores();
  
}

void setScores(){
  if(score == 0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Don't cheat bud");
    return;
  }
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Time: ");
  lcd.print(score);
  lcd.print("ms");

  if(score < highScore) highScore = score;  

  lcd.setCursor(0,1);
  lcd.print("Best: ");
  lcd.print(highScore);
  lcd.print("ms");
  
}
