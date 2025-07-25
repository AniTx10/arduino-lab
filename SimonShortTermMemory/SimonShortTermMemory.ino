#include<LiquidCrystal.h>

const int rs = 7;
const int en = 8;
const int d4 = 5;
const int d5 = 10;
const int d6 = 11;
const int d7 = 12;

const int buzzPin = 3;

const int redLED = 13;
const int blueLED = A1;
const int greenLED = A2;
const int yellowLED = A3;

const int redButton = A4;
const int blueButton = A5;
const int greenButton = 2;
const int yellowButton = 4;

int redRead = 1;
int blueRead = 1;
int greenRead = 1;
int yellowRead = 1;

int dt = 1000 ;
int smallDt = 100;
int smediumDt = 350;
int mediumDt = 500;
int debounceDelay = 100;

String nextColor[4] = {"red", "blue", "green", "yellow"};
const int maxSize = 100;
String sequence[maxSize];

int randomInt;
String randomColor;
int sequenceLength = 0;
int highScore = 0;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // creates lcd object that represents how our LCD is wired

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2); // 16 columns, 2 rows
  pinMode(buzzPin, OUTPUT);
  pinMode(redButton, INPUT_PULLUP);
  pinMode(blueButton, INPUT_PULLUP);
  pinMode(greenButton, INPUT_PULLUP);
  pinMode(yellowButton, INPUT_PULLUP);
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  randomSeed(analogRead(A0));

  for(int i = 0; i < maxSize; i++) sequence[i] = "none";

}

void loop() {
  // put your main code here, to run repeatedly:

  addColor();
  playSequence();
  checkUser();
  delay(mediumDt);
  
}

void addColor(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Score: ");
  lcd.print(sequenceLength);
  lcd.setCursor(0,1);
  lcd.print("Best: ");
  lcd.print(highScore);
  randomInt = random(0, 4); // generates random integer between 0 and 3, inclusive
  randomColor = nextColor[randomInt];
  sequence[sequenceLength] = randomColor;
  sequenceLength ++;
}

void playSequence(){
  for(int i = 0; i < sequenceLength; i++){
    if(sequence[i] == "red"){
      digitalWrite(redLED, HIGH);
      tone(buzzPin, 252);
      delay(dt);
      noTone(buzzPin);
      digitalWrite(redLED, LOW);
    }

    if(sequence[i] == "blue"){
      digitalWrite(blueLED, HIGH);
      tone(buzzPin, 415);
      delay(dt);
      noTone(buzzPin);
      digitalWrite(blueLED, LOW);
    }

    if(sequence[i] == "green"){
      digitalWrite(greenLED, HIGH);
      tone(buzzPin, 209);
      delay(dt);
      noTone(buzzPin);
      digitalWrite(greenLED, LOW);
    }

    if(sequence[i] == "yellow"){
      digitalWrite(yellowLED, HIGH);
      tone(buzzPin, 310);
      delay(dt);
      noTone(buzzPin);
      digitalWrite(yellowLED, LOW);
    }

    delay(smallDt);
  }

  
}

void checkUser() {
  for (int i = 0; i < sequenceLength; i++) {
    bool inputReceived = false;
    while (!inputReceived) {
      redRead = digitalRead(redButton);
      blueRead = digitalRead(blueButton);
      greenRead = digitalRead(greenButton);
      yellowRead = digitalRead(yellowButton);

      if (redRead == 0 && blueRead == 1 && greenRead == 1 && yellowRead == 1) {
        inputReceived = true;
        if (sequence[i] == "red") {
          digitalWrite(redLED, HIGH);
          tone(buzzPin, 252);
          delay(smediumDt);
          noTone(buzzPin);
          digitalWrite(redLED, LOW);
        } else {
          resetGame();
          return;
        }
      }

      else if (blueRead == 0 && redRead == 1 && greenRead == 1 && yellowRead == 1) {
        inputReceived = true;
        if (sequence[i] == "blue") {
          digitalWrite(blueLED, HIGH);
          tone(buzzPin, 415);
          delay(smediumDt);
          noTone(buzzPin);
          digitalWrite(blueLED, LOW);
        } else {
          resetGame();
          return;
        }
      }

      else if (greenRead == 0 && redRead == 1 && blueRead == 1 && yellowRead == 1) {
        inputReceived = true;
        if (sequence[i] == "green") {
          digitalWrite(greenLED, HIGH);
          tone(buzzPin, 209);
          delay(smediumDt);
          noTone(buzzPin);
          digitalWrite(greenLED, LOW);
        } else {
          resetGame();
          return;
        }
      }

      else if (yellowRead == 0 && redRead == 1 && blueRead == 1 && greenRead == 1) {
        inputReceived = true;
        if (sequence[i] == "yellow") {
          digitalWrite(yellowLED, HIGH);
          tone(buzzPin, 310);
          delay(smediumDt);
          noTone(buzzPin);
          digitalWrite(yellowLED, LOW);
        } else {
          resetGame();
          return;
        }
      }

      delay(debounceDelay); // debounce protection
    }
  }

  // If they get through the loop without failing
  if (sequenceLength > highScore) {
    highScore = sequenceLength;
  }
}


void resetGame(){
  sequenceLength = 0;
  for(int i = 0; i < maxSize; i++) sequence[i] = "none";
}
